//最小生成树算法,基于贪心的思想
//将图中所有边放到列表之中,并将边按照权值大小由小到大排列
//将每条边回贴，每次都需要判断图中是否存在环,如果没有形成环,该边就可以成为最小生成树的一条边
//使用优先队列+并查集来实现，每次从优先队列中取出一条边用并查集判断是否成环

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

class UF{
public:
    UF(int n):n(n),rank(n,1),parent(n){
        iota(parent.begin(),parent.end(),0);
    }

    void Union(int x,int y){
        int rootX=find(x),rootY=find(y);
        if(rootX==rootY){
            return;
        }
        //小树接到大树下面会更平衡
        if(rank[rootX]<rank[rootY]){
            parent[rootX]=rootY;
            rank[rootY]+=rank[rootX];
        }else{
            parent[rootY]=rootX;
            rank[rootX]+=rank[rootY];
        }
    }

    bool isConnected(int x,int y){
        return find(x)==find(y);
    }

private:
    int n;
    vector<int> parent;
    vector<int> rank;

    int find(int x){
        // while(x!=parent[x]){
        //     parent[x]=parent[parent[x]];
        //     x=parent[x];
        // }
        // return x;
        return x==parent[x]?x:parent[x]=find(parent[x]);
    }
};

struct Result{
    vector<vector<int>> res;
    int cost;
    Result(vector<vector<int>>& edges,int cost):res(edges),cost(cost) {}
};

class Solution{
public:
    //默认任意顶点均可以通过某条路径到达其他节点
    //如果不满足，可以先使用并查集判断是否都已经连通
    //总共有n个顶点,graph[i][0],graph[i][1]表示每条边的两个顶点,graph[i][2]表示每条边的权值大小
    Result Kruskal(vector<vector<int>>& graph,int n){
        //将每条边按照权值大小排序
        auto comp=[&](const vector<int>& a,const vector<int>& b){
            return a[2]>b[2];
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(comp)> pq(comp);
        //将图中边入队
        for(const vector<int>& edge:graph){
            pq.push(edge);
        }
        //总共使用n-1条边连接
        //存储每条边的结果
        vector<vector<int>> res;
        UF uf(n);
        //最多需要n-1条边
        while(res.size()<n-1){
            //!!!不能随手用引用,优先队列顶部删除之后会变化
            auto edge=pq.top();
            pq.pop();
            int point1=edge[0],point2=edge[1];
            if(uf.isConnected(point1,point2)){
                continue;
            }
            uf.Union(point1,point2);
            res.push_back(edge);
        }
        int cost=0;
        for(const vector<int>& edges:res){
            cost+=edges[2];
        }
        return Result(res,cost);
    }
};

int main(){
    vector<vector<int>> graph{{0,1,10},{0,5,11},{1,2,18},{1,6,16},{1,8,12},{2,3,22},{2,8,8},{3,4,20},{3,6,24},{3,7,16},{3,8,21},{4,5,26},{4,7,7},{5,6,17},{6,7,19}};
    Result Res=Solution().Kruskal(graph,9);
    cout<<"总花费:"<<Res.cost<<endl;
    cout<<"每一条边-------------------------------------"<<endl;
    for(const vector<int>& edge:Res.res){
        cout<<edge[0]<<"<-->"<<edge[1]<<" 权值:"<<edge[2]<<endl;
    }
    system("pause");
    return 0;
}