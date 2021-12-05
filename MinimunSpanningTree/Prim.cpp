//最小生成树算法,基于贪心的思想
//与Kruskal算法不同,该算法基于顶点，优先选择连接两个顶点的所有边集合的最小值
//图中分为已连接的部分和未连接的部分,选择连接两部分的权值最小的边
//Prim算法不断更新三个列表
//列表1:存储已选顶点的信息
//列表2:存储当前时刻已选顶点集合到该顶点的最小权值边的权值大小,初始状态均为INF 
//列表3:存储对应列表2每一项的起点,即说明<列表3[i],i>为MST的一条边,当该位置为0表示该位置已加入MST

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Result{
    vector<int> res;
    int cost;
    Result(vector<int>& edges,int cost):res(edges),cost(cost) {}
};

//任取一个起始点,本例中取0为起始点
//时间复杂度O(n^2)
class Solution{
public:
    Result Prim(vector<vector<int>>& graph,int n){
        //需要构造邻接矩阵
        vector<vector<int>> Graph(n+1,vector<int>(n+1,INF));
        for(int i=0;i<=n;++i){
            Graph[i][i]=0;
        }
        for(const vector<int>& g:graph){
            Graph[g[0]][g[1]]=g[2];
            Graph[g[1]][g[0]]=g[2];
        }
        vector<int> visited(n+1);
        vector<int> lowcost(n+1,INF);
        vector<int> MST(n+1,0);
        lowcost[0]=0;
        for(int i=1;i<n;++i){
            int index=-1;
            int dis_temp=INF;
            for(int i=0;i<=n;++i){
                if(!visited[i]&&lowcost[i]<dis_temp){
                    index=i;
                    dis_temp=lowcost[i];
                }
            }
            if(index==-1){
                break;
            }
            visited[index]=true;
            lowcost[index]=0;
            //每加入一个点需要更新lowcost数组
            for(int i=0;i<=n;++i){
                if(!visited[i]&&Graph[index][i]<lowcost[i]){
                    lowcost[i]=Graph[index][i];
                    MST[i]=index;
                }
            }
        }
        int cost=0;
        for(int i=1;i<=n;++i){
            cost+=Graph[MST[i]][i];
        }
        return {MST,cost};
    }
};

int main(){
    vector<vector<int>> graph{{0,1,10},{0,5,11},{1,2,18},{1,6,16},{1,8,12},{2,3,22},{2,8,8},{3,4,20},{3,6,24},{3,7,16},{3,8,21},{4,5,26},{4,7,7},{5,6,17},{6,7,19}};
    Result Res=Solution().Prim(graph,8);
    cout<<"总花费:"<<Res.cost<<endl;
    cout<<"每一条边-------------------------------------"<<endl;
    for(int i=1;i<=8;++i){
        cout<<"起点:"<<Res.res[i]<<"<-->"<<"终点:"<<i<<endl;
    }
    system("pause");
    return 0;
}