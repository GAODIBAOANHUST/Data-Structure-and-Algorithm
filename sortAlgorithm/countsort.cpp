#include <iostream>
#include <vector>

using namespace std;

//计数排序是一个非基于比较的排序算法，元素从未排序状态变为已排序状态的过程，是由额外空间的辅助和元素本身的值决定的。
//它的优势在于在对一定范围内的整数排序时，它的复杂度为Ο(n+k)（其中k是整数的范围），快于任何比较排序算法。
//当然这是一种牺牲空间换取时间的做法，而且当 O(k)>O(nlogn) 的时候其效率反而不如基于比较的排序，因为基于比较的排序的时间复杂度在理论上的下限是 O(nlogn)
//要求均为整数
void CountSort(vector<int>& arr){
    int n=arr.size();
    int max_value=INT_MIN;
    int min_value=INT_MAX;
    for(int i:arr){
        max_value=max(max_value,i);
        min_value=min(min_value,i);
    }
    vector<int> cnt(max_value-min_value+1);
    for(int i:arr){
        cnt[i-min_value]++;
    }
    int index=0;
    for(int i=0;i<=max_value-min_value;++i){
        for(int j=0;j<cnt[i];++j){
            arr[index++]=(i+min_value);
        }
    }
}

int main()
{
    vector<int> arr{9, 1, 5, 8, 3, 7, 4, 6, 2, 3, 5, 7, 3, 8, 1, 5, 6};
    CountSort(arr);
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}