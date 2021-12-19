//tarjin强连通分量算法
//连通:无向图中,从任意点i可到达任意点j
//强连通:有向图中,从任意点i可到达任意点j
//弱连通:把有向图看做无向图,......同上

//两种DFS遍历的方式
//1. 先访问当前节点,再递归相邻节点
//2. 先递归相邻节点,再访问当前节点
//tarjin算法使用的遍历方式是DFS2
//对于一个节点x,赋予属性(i,j),其中i表示在DFS中x点被访问的时间点,j表示x通过有向边可回溯到的最早的时间点

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

class Solution1{
private:
    vector<vector<int>> res;
    vector<bool> visited;

    //时间戳
    int curr_time;
    //记录每一次查找强连通分量的时候某个节点是否在栈中
    unordered_set<int> instack;
    stack<int> S;
    vector<int> times;
    vector<int> origin_times;

    void DFS(const vector<vector<int>>& edges,const vector<vector<int>>& next_points,int index){
        visited[index]=true;
        S.push(index);
        instack.insert(index);
        //记录访问到的时间
        origin_times[index]=times[index]=curr_time++;
        //遍历子节点
        for(int next_pnt:next_points[index]){
            if(!visited[next_pnt]){
                DFS(edges,next_points,next_pnt);
                times[index]=min(times[index],times[next_pnt]);
            }else if(instack.find(next_pnt)!=instack.end()){
                //已经遍历并且未出栈
                times[index]=min(times[index],times[next_pnt]);
            }
        }
        //更新强连通分量
        if(origin_times[index]==times[index]){
            int Size=res.size();
            res.push_back(vector<int>());
            while(S.top()!=index){
                res[Size].push_back(S.top());
                instack.erase(S.top());
                S.pop();
            }
            res[Size].push_back(S.top());
            instack.erase(S.top());
            S.pop();
        }
    }

public:
    //输入vector每一项edge表示从edge[0]->edge[1],总共有n个顶点
    vector<vector<int>> targin(vector<vector<int>>& edges,int n){
        vector<vector<int>> next_points(n,vector<int>());
        visited.resize(n);
        origin_times.resize(n);
        times.resize(n);
        curr_time=0;
        for(auto& edge:edges){
            next_points[edge[0]].push_back(edge[1]);
        }
        //可能出现某个点与其余部分未连接的情况
        for(int i=0;i<n;++i){
            if(!visited[i]){
                DFS(edges,next_points,i);
            }
        }
        return res;
    }
};


//tarjin割点算法求割点与桥
//割点:无向连通图中,某点和连接点的边去掉后，图不再连通
//桥:无向连通图中,某条边去掉后，图不再连通 
//如果一个点是割点,满足以下两种情况之一
//case1:x非root节点&&x有子节点&&time[x的子节点]>=original_time[x]
//case2:x为root节点&&x有大于等于2个子节点
//x->y是桥:time[y]>original_time[x]

//返回结果的数据结构
struct PointAndEdge{
    vector<int> points;
    vector<pair<int,int>> edges;
};

class Solution2{
private:
    vector<int> origin_times,times;
    int time;
    //需要记录每一个节点的父亲节点,都初始化为-1表示一开始都没有父节点,DFS时进行更新,从而判断root节点
    vector<int> parent;
    //可能出现重复输出的情况,记录某个点是不是割点
    unordered_set<int> tarjinpnts;
    //存储结果
    vector<pair<int,int>> res_edges;

    void DFS(const vector<vector<int>>& edges,int curr,const int n){
        //遍历到当前节点,更新时间
        origin_times[curr]=times[curr]=time++;
        //记录子节点的数量
        int child=0;
        //遍历与他相邻的节点
        for(int next_pnt=0;next_pnt<n;++next_pnt){
            if(edges[curr][next_pnt]){
                //此时next_pnt可能是curr的子节点,但是也有可能之前就访问过
                if(origin_times[next_pnt]==0){
                    child++;
                    parent[next_pnt]=curr;
                    DFS(edges,next_pnt,n);
                    //判定curr是不是割点,两种case
                    if(parent[curr]==-1&&child>=2){
                        tarjinpnts.insert(curr);
                    }
                    if(parent[curr]!=-1&&times[next_pnt]>origin_times[curr]){
                        tarjinpnts.insert(curr);
                    }
                    //判定curr->next_pnt这条边是不是桥
                    if(times[next_pnt]>origin_times[curr]){
                        res_edges.emplace_back(curr,next_pnt);
                    }
                    //!!!无向图肯定可以回溯,需要更新times[curr]
                    times[curr]=min(times[curr],times[next_pnt]);
                }else if(next_pnt!=parent[curr]){
                    //虽然已经访问过next_pnt,但是next_pnt不是curr的父节点,是curr的祖先节点
                    //更新times
                    times[curr]=min(times[curr],times[next_pnt]);
                }
            }
        }
    }

public:
    //总共n个节点,节点编号为0-n
    //传入的edges为邻接矩阵形式
    PointAndEdge findtargin(vector<vector<int>>& edges,int n){
        origin_times.resize(n,0);
        times.resize(n,0);
        time=1;
        parent.resize(n,-1);
        //其实正常来说图是连通的,只需要遍历第一个节点就可以
        for(int i=0;i<n;++i){
            if(!origin_times[i]){
                DFS(edges,i,n);
            }
        }
        vector<int> res_points(tarjinpnts.begin(),tarjinpnts.end());
        return PointAndEdge{res_points,res_edges};
    }
};

//Solution1测试
// int main(){
//     vector<vector<int>> edges{{0,1},{1,2},{2,3},{2,4},{3,4},{3,1},{0,5},{5,6},{6,0}};
//     vector<vector<int>> res=Solution1().targin(edges,7);
//     for(auto& v:res){
//         cout<<"{"<<" ";
//         for(int x:v){
//             cout<<x<<" ";
//         }
//         cout<<"}\n";
//     }
//     system("pause");
//     return 0;
// }

//Solution2测试
int main(){
    vector<vector<int>> edges{{0,1,1,0,0,0,0,0},
                                {1,0,1,1,0,0,0,0},
                                {1,1,0,1,0,0,0,0},
                                {0,1,1,0,1,0,0,0},
                                {0,0,0,1,0,0,1,1},
                                {0,0,0,0,0,0,0,1},
                                {0,0,0,0,1,0,0,0},
                                {0,0,0,0,1,1,0,0}};
    PointAndEdge res=Solution2().findtargin(edges,8);
    //输出割点
    cout<<"割点如下:"<<endl;
    for(int i:res.points){
        cout<<i<<",";
    }
    cout<<endl;
    cout<<"桥如下:"<<endl;
    for(auto& p:res.edges){
        cout<<p.first<<"--"<<p.second<<endl;
    }
    system("pause");
    return 0;
}