//前缀和与差分数组
#include <iostream>
#include <vector>

using namespace std;

//前缀和的主要使用场景是原始数组不会被修改的情况下，频繁查询某个区间的累加和
class Prefix{
public:
    Prefix(vector<int>& arr){
        presum.resize(arr.size()+1);
        for(int i=0;i<arr.size();++i){
            presum[i+1]=presum[i]+arr[i];
        }
    }

    //查询闭区间[i...j]的累加和
    int query(int i,int j){
        return presum[j+1]-presum[i];
    }

private:
    vector<int> presum;
};

//差分数组,技巧与前缀和类似,主要适用场景是频繁对原始数组的某个区间元素进行增减
//构造差分数组diff,其中diff[i]就是nums[i]与nums[i-1]的差值
//diff[i]+=val代表arr[i...]+=val,diff[j+1]-=val代表arr[j+1...]-=val,因此arr[i...j]+=val;
class Difference{
public:
    Difference(vector<int>& arr){
        diff.resize(arr.size());
        diff[0]=arr[0];
        for(int i=1;i<arr.size();++i){
            diff[i]=arr[i]-arr[i-1];
        }
    }
    //给arr[i...j]增加val(可以为负数)
    void increment(int i,int j,int val){
        diff[i]+=val;
        if(j+1<diff.size()){
            diff[j+1]-=val;
        }
    }
    //返回结果数组
    vector<int> result(){
        vector<int> res(diff.size());
        res[0]=diff[0];
        for(int i=1;i<diff.size();++i){
            res[i]=res[i-1]+diff[i];
        }
        return res;
    }
private:
    vector<int> diff;
};

//leetcode 995 K连续位的最小反转次数 滑动窗口+差分数组
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n=nums.size();
        int curr_reverse_cnt=0;//记录当前的反转次数
        int res=0;
        vector<int> reverse_vec(n);
        for(int i=0;i<n;++i){
            curr_reverse_cnt+=reverse_vec[i];
            //判断当前是否为0,需要翻转,注意一开始是不需要反转的
            if((nums[i]+curr_reverse_cnt)%2==0){
                //超过区间边界，无法完成
                if(i+k>n){
                    return -1;
                }
                curr_reverse_cnt++;
                //将区间[i...i+k-1]全部反转
                reverse_vec[i]++;
                if(i+k<n)
                    reverse_vec[i+k]--;
                res++;
            }
        }
        return res;
    }
};


int main(){
    vector<int> nums{0,0,0,1,0,1,1,0};
    int res=Solution().minKBitFlips(nums,3);
    system("pause");
    return 0;
}