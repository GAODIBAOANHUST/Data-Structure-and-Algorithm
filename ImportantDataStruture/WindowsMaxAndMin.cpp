//实现滑动窗口最大最小值

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_map>

using namespace std;

//仅求得滑动窗口的最大值,最小值同理,使用优先队列和哈希表
class Solution1 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int n=nums.size();
        //大根堆
        priority_queue<int> pq;
        unordered_map<int,int> record;//记录元素以及出现的次数
        //首先将前k个数进入优先队列,并用hashmap记录
        for(int i=0;i<k;++i){
            pq.push(nums[i]);
            record[nums[i]]++;
        }
        //堆顶是当前最大元素
        res.push_back(pq.top());
        //从k开始遍历
        for(int i=k;i<n;++i){
            pq.push(nums[i]);
            record[nums[i]]++;//进入窗口
            record[nums[i-k]]--;//移出窗口
            //如果当前堆顶元素是当前值
            if(pq.top()==nums[i]){
                res.push_back(pq.top());
                continue;
            }else{
                //堆顶元素有可能已经是早就被删除的
                while(record[pq.top()]==0){
                    pq.pop();
                }
                res.push_back(pq.top());
            }
        }
        return res;
    }
};

//使用双端队列
//任何时候窗口的最大值都是双端队列头部所代表的值,双端队列从头到尾保证严格的从大到小顺序
//从队列尾部插入一个新的值,如果队尾的值没有严格大于当前值,就弹出(被弹出的值再也没有可能成为最大值)
//滑动窗口的时候仅需要看双端队列头部的值是否“过期”,如果过期就弹出
//双端队列中存储的信息是:如果right不再向右扩展,left向右收缩时,当前窗口的最大值
//时间复杂度O(N),每个元素会进队列一次,出队列一次
class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int n=nums.size();
        deque<int> dq;//存储的是数组的下标
        for(int i=0;i<n;++i){
            //看双端队列的头部元素是否过期
            if(!dq.empty()&&i-dq.front()==k){
                dq.pop_front();
            }
            //将该元素从队尾插入,如果队尾元素小于等于当前元素则删除
            while(!dq.empty()&&nums[dq.back()]<=nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            if(i>=k-1){
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};

int main(){
    system("pause");
    return 0;
}