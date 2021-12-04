//BellmanFord算法可以解决负权回路的问题,但是图中不能有负圈(圈中弧或者边的权值之和小于0)
//因为需要统计边的数量,所以需要邻接表
//首次迭代结果，即与源点直连的边的权值,若无直连,则为无穷大
//每次迭代都是与上一次迭代结果相比较。迭代次数即与源点之间的边数。迭代结果即min(上次迭代结果,边数增加后的权值之和)

#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        int E=times.size();
        vector<int> distance(n+1,INF);
        vector<bool> visited(n+1,false);
        vector<int> pre(n+1,-1);
        for(auto& info:times){
            if(info[0]==k){
                distance[info[1]]=info[2];
                pre[info[1]]=info[0];
            }
        }
        distance[k]=0;
        for(int i=1;i<n;++i){
            for(int j=0;j<E;++j){
                if(distance[times[j][1]]>distance[times[j][0]]+times[j][2]){
                    distance[times[j][1]]=distance[times[j][0]]+times[j][2];
                    pre[times[j][1]]=times[j][0];
                }
            }
        }
        bool flag=true;
        //判断是否有负权回路
        for(int i=0;i<E;++i){
            if(distance[times[i][1]]>distance[times[i][0]]+times[i][2]){
                flag=false;
                break;
            }
        }
    }
};