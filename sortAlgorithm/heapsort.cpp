#include <iostream>
#include <vector>

using namespace std;

//用数组模拟堆,假设为大根堆,大根堆表示父节点的值大于两个子节点的值
//将待排序的序列构成一个大顶堆。此时根节点的值是整个对中最大的，将其与数组末尾交换，重复此过程
//时间复杂度O(nlogn),是不稳定的算法
//小根堆类比
void Heapsort(vector<int>& arr){
    int n=arr.size();
    auto max_heapify=[&](int start,int end)->void{
        int dad=start;
        int son=dad*2+1;
        while(son<=end){
            if(son+1<=end&&arr[son]<arr[son+1]){
                son++;
            }
            if(arr[dad]>=arr[son]){
                return;
            }else{
                swap(arr[son],arr[dad]);
                dad=son;
                son=2*dad+1;
            }
        }
    };
    //从最后一个非叶子节点开始调整
    //调整成父节点均比两个子节点大的情况
    for(int i=n/2-1;i>=0;--i){
        max_heapify(i,n-1);
    }
    for(int i=n-1;i>0;--i){
        swap(arr[0],arr[i]);
        max_heapify(0,i-1);
    }
}

int main(){
    vector<int> arr{9,1,5,8,3,7,4,6,2,3,5,7,2,1,9,6};
    Heapsort(arr);
    for(int i:arr){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}