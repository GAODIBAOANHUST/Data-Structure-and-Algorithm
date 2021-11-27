#include <iostream>
#include <vector>

using namespace std;

//插入排序基本思想是将一个记录插入到已经排好序的有序表中，从而得到一个新的、记录数增加1的有序表
//时间复杂度O(n^2)
void InsertSort(vector<int>& arr){
    int n=arr.size();
    for(int i=1;i<n;++i){
        int j=i;
        while(j>0){
            if(arr[j]<arr[j-1]){
                swap(arr[j],arr[j-1]);
            }
            --j;
        }
    }
}

int main(){
    vector<int> arr{9,1,5,8,3,7,4,6,2,3};
    InsertSort(arr);
    for(int i:arr){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}