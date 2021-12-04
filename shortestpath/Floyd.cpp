#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Floyd算法,解决所有节点对的最短路径
//时间复杂度O(n^3)
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<int>> dp(n+1,vector<int>(n+1,INT_MAX/2));
        for(int i=1;i<=n;++i)
            dp[i][i]=0;
        for(auto& info:times){
            dp[info[0]][info[1]]=info[2];
        }
        for(int k=1;k<=n;++k){
            for(int i=1;i<=n;++i){
                for(int j=1;j<=n;++j){
                    if(i==j)
                        continue;
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
                }
            }
        }
        int res=*max_element(dp[k].begin()+1,dp[k].end());
        return res==INT_MAX/2?-1:res;
    }
};

int main(){
    system("pause");
    return 0;
}