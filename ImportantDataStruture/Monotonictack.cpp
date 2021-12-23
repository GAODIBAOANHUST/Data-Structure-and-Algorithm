//单调栈:解决某个下标的数,类似于:左边离他最近的比他大的,右边离他最近的比他大的.
//保证栈底到栈顶是由大到小
//定义数组中累积和与最小值的乘积叫做指标A,给定一个数组,返回子数组中,指标A的最大值
//思路:数组中每个元素考虑以当前值为最小值的子数组中,指标A的最大值
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution{
public:
    int calculateIndexA(vector<int>& nums){
        int n=nums.size();
        vector<int> presum(n+1);
        presum[0]=0;
        for(int i=1;i<=n;++i){
            presum[i]=presum[i-1]+nums[i-1];
        }
        int res=0;
        stack<int> S;
        for(int i=0;i<n;++i){
            while(!S.empty()&&nums[i]<nums[S.top()]){
                //此时S.top()不可能再向右扩展,更新该值
                int curr=S.top();
                S.pop();
                int pre=-1;
                if(!S.empty()){
                    pre=S.top();
                }
                int temp=nums[curr]*(presum[i]-presum[pre+1]);
                res=max(res,temp);
            }
            S.push(i);
        }
        //最后剩余的是一个单增序列,他们左边界下标到上一个值,右边界下标到n-1
        while(!S.empty()){
            int curr=S.top();
            S.pop();
            if(S.empty()){
                //整个数组最小数
                res=max(res,presum[n]*nums[curr]);
                break;
            }else{
                res=max(res,nums[curr]*(presum[n]-presum[S.top()+1]));
            }
        }
        return res;
    }
};

int main(){
    vector<int> nums{5,3,2,1,6,7,8,4};
    int res=Solution().calculateIndexA(nums);
    system("pause");
    return 0;
}