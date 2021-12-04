//Dijkstra算法
//朴素Dijkstra算法和堆优化的Dijkstra算法

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

void printvec(vector<int>& vec){
    for(int i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
}

//假设传入参数有各个节点的连接图以及各个边的权值,节点数n,源节点k(即从节点k出发)
//节点编号为1-n
//时间复杂度O(n^2),如果要求出每个点到其他点的最短路径,需要再循环一次,时间复杂度
class Solution1 {
public:
    void networkDelayTime(vector<vector<int>>& graph, int n, int k) {
        //传入的graph为邻接矩阵形式
        //记录最短距离
        vector<int> distance(n+1,INF);
        //更新节点是否访问过
        vector<int> visited(n+1,0);
        //记录每个节点路径的前驱结点,初始均为-1;
        vector<int> pre(n+1,-1);
        //根据源节点k初始化
        //假定k的前驱结点也为k
        // for(int i=1;i<=n;++i){
        //     if(graph[k][i]!=INF){
        //         distance[i]=graph[k][i];
        //         pre[i]=k;
        //     }
        // }
        // visited[k]=true;
        distance[k]=0;
        //从节点k开始松弛节点，每次循环松弛一个，最多需要循环n-1次
        for(int i=1;i<=n;++i){
            int dis_temp=INF;
            //此次需要松弛的节点标识
            int index=-1;
            for(int i=1;i<=n;++i){
                if(!visited[i]&&distance[i]<dis_temp){
                    index=i;
                    dis_temp=distance[i];
                }
            }
            //有的节点是无法到达的,直接退出,在该例中不考虑此情况
            if(index==-1){
                break;
            }
            //标记该节点已访问过
            visited[index]=1;
            //以该节点为中心继续松弛
            for(int i=1;i<=n;++i){
                if(!visited[i]&&distance[index]+graph[index][i]<distance[i]){
                    //找到了更短的路径，更新
                    distance[i]=distance[index]+graph[index][i];
                    pre[i]=index;
                }
            }
        }
        //把distance,visited,pre都打印出来
        printvec(distance);
        printvec(visited);
        printvec(pre);
    }
};

//堆优化的Dijkstra算法
class Solution2 {
    using PII = pair<int,int>;
public:
    void networkDelayTime(vector<vector<int>>& graph, int n, int k) {
        //初始化
        //记录最短距离
        vector<int> distance(n+1,INF);
        //更新节点是否访问过
        vector<int> visited(n+1,0);
        //记录每个节点路径的前驱结点,初始均为-1;
        vector<int> pre(n+1,-1);
        //根据源节点k初始化
        //假定k的前驱结点也为k
        //first表示距离,second表示节点号
        distance[k]=0;
        priority_queue<PII,vector<PII>,greater<PII>> pq;
        pq.emplace(0,k);
        while(!pq.empty()){
            int curr_index=pq.top().second;
            pq.pop();
            if(visited[curr_index]){
                continue;
            }
            //从该节点开始拓展
            visited[curr_index]=true;
            for(int i=1;i<=n;++i){
                if(!visited[i]&&distance[i]>distance[curr_index]+graph[curr_index][i]){
                    distance[i]=distance[curr_index]+graph[curr_index][i];
                    pre[i]=curr_index;
                    pq.emplace(distance[i],i);
                }
            }
        }
        printvec(distance);
        printvec(visited);
        printvec(pre);
    }
};

int main(){
    vector<vector<int>> graph{  {0,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                                {INF,0,1,5,INF,INF,INF,INF,INF,INF},
                                {INF,1,0,3,7,5,INF,INF,INF,INF},
                                {INF,5,3,0,INF,1,7,INF,INF,INF},
                                {INF,INF,7,INF,0,2,INF,3,INF,INF},
                                {INF,INF,5,1,2,0,3,6,9,INF},
                                {INF,INF,INF,7,INF,3,0,INF,5,INF},
                                {INF,INF,INF,INF,3,6,INF,0,2,7},
                                {INF,INF,INF,INF,INF,9,5,2,0,4},
                                {INF,INF,INF,INF,INF,INF,INF,7,4,0}};
    Solution1().networkDelayTime(graph,9,1);
    // Solution2().networkDelayTime(graph,9,1);
    system("pause");
    return 0;
}