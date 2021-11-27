#include <iostream>
#include <vector>

using namespace std;

//选择排序:通过n-i次关键字的比较，从n-i+1个记录中选出关键字最小的记录，并和第i个记录交换
void SelectSort(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n-1;++i){
        //记录最小下标
        int min_pos=i;
        for(int j=i+1;j<n;++j){
            if(arr[min_pos]>arr[j]){
                min_pos=j;
            }
        }
        //找到最小处，与i位置进行交换
        if(i!=min_pos){
            swap(arr[i],arr[min_pos]);
        }
    }
}

int main(){
    vector<int> arr{9,1,5,8,3,7,4,6,2,3};
    SelectSort(arr);
    for(int i:arr){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}