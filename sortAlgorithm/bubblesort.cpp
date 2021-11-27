#include <iostream>
#include <vector>

using namespace std;

//冒泡排序是一种交换排序，它的基本思想是：两两比较相邻记录的关键字，如果反序则交换，直到没有反序的记录为止
//初始代码
//每循环一次数组中最小值就排序到数组前面
//时间复杂度O(n^2)
void BubbleSort0(vector<int>& arr){
    int n=arr.size();
    for(int i=1;i<n;++i){
        for(int j=n-1;j>=i;--j){
            if(arr[j-1]>arr[j]){
                swap(arr[j-1],arr[j]);
            }
        }
    }
}

//冒泡排序优化
//假设数组{2,1,3,4,5,6,7,8,9}，在第一次循环之后交换了1和2已经有序，但是在第一版代码中仍然会做一些无用的比较操作
//增加一个标记位flag
void BubbleSort1(vector<int>& arr){
    int n=arr.size();
    bool flag=true;
    for(int i=1;i<n&&flag;++i){
        flag=false;
        for(int j=n-1;j>=i;--j){
            if(arr[j-1]>arr[j]){
                //有数据交换，证明还是无序状态
                flag=true;
                swap(arr[j],arr[j-1]);
            }
        }
    }
}

int main(){
    vector<int> arr{9,1,5,8,3,7,4,6,2};
    // BubbleSort0(arr);
    BubbleSort1(arr);
    for(int i:arr){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}