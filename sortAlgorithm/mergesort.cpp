#include <iostream>
#include <vector>

using namespace std;

//归并排序：分治思想
//假设初始序列含有n个记录，可以看成是n个有序的子序列，每个子序列的长度为1，然后两两归并，得到[n/2]([x]表示不小于x的最小整数)
//个长度为2或1的有序子序列，再两两归并...,如此重复，直至得到一个长度为n的有序序列为止,称为2路归并
//时间复杂度O(nlogn),占用内存高(临时数组),稳定性好
void MyMerge(vector<int>& arr,vector<int>& temp,int low,int mid,int high){
    int left=low,right=mid+1;
    int k=low;//操作临时数组
    while(left<=mid&&right<=high){
        if(arr[left]<arr[right]){
            temp[k++]=arr[left++];
        }else{
            temp[k++]=arr[right++];
        }
    }
    while(left<=mid){
        temp[k++]=arr[left++];
    }
    while(right<=high){
        temp[k++]=arr[right++];
    }
    //还原
    for(int i=low;i<=high;++i){
        arr[i]=temp[i];
    }
}

void MyMergeSort(vector<int>& arr,vector<int>& temp,int low,int high){
    if(low>=high){
        return;
    }
    int mid=low+(high-low>>1);
    MyMergeSort(arr,temp,low,mid);
    MyMergeSort(arr,temp,mid+1,high);
    MyMerge(arr,temp,low,mid,high);
}

void MergeSort(vector<int>& arr){
    vector<int> temp(arr.size());
    MyMergeSort(arr,temp,0,arr.size()-1);
}

//实现K路归并？

int main()
{
    vector<int> arr{9, 1, 5, 8, 3, 7, 4, 6, 2, 3, 5, 7, 3, 8, 1, 5, 6};
    //QuickSort0(arr);
    MergeSort(arr);
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}