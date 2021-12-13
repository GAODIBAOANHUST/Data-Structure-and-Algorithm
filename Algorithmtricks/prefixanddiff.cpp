//ǰ׺����������
#include <iostream>
#include <vector>

using namespace std;

//ǰ׺�͵���Ҫʹ�ó�����ԭʼ���鲻�ᱻ�޸ĵ�����£�Ƶ����ѯĳ��������ۼӺ�
class Prefix{
public:
    Prefix(vector<int>& arr){
        presum.resize(arr.size()+1);
        for(int i=0;i<arr.size();++i){
            presum[i+1]=presum[i]+arr[i];
        }
    }

    //��ѯ������[i...j]���ۼӺ�
    int query(int i,int j){
        return presum[j+1]-presum[i];
    }

private:
    vector<int> presum;
};

//�������,������ǰ׺������,��Ҫ���ó�����Ƶ����ԭʼ�����ĳ������Ԫ�ؽ�������
//����������diff,����diff[i]����nums[i]��nums[i-1]�Ĳ�ֵ
//diff[i]+=val����arr[i...]+=val,diff[j+1]-=val����arr[j+1...]-=val,���arr[i...j]+=val;
class Difference{
public:
    Difference(vector<int>& arr){
        diff.resize(arr.size());
        diff[0]=arr[0];
        for(int i=1;i<arr.size();++i){
            diff[i]=arr[i]-arr[i-1];
        }
    }
    //��arr[i...j]����val(����Ϊ����)
    void increment(int i,int j,int val){
        diff[i]+=val;
        if(j+1<diff.size()){
            diff[j+1]-=val;
        }
    }
    //���ؽ������
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

//leetcode 995 K����λ����С��ת���� ��������+�������
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n=nums.size();
        int curr_reverse_cnt=0;//��¼��ǰ�ķ�ת����
        int res=0;
        vector<int> reverse_vec(n);
        for(int i=0;i<n;++i){
            curr_reverse_cnt+=reverse_vec[i];
            //�жϵ�ǰ�Ƿ�Ϊ0,��Ҫ��ת,ע��һ��ʼ�ǲ���Ҫ��ת��
            if((nums[i]+curr_reverse_cnt)%2==0){
                //��������߽磬�޷����
                if(i+k>n){
                    return -1;
                }
                curr_reverse_cnt++;
                //������[i...i+k-1]ȫ����ת
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