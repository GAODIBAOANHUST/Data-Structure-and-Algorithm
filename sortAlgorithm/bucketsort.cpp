#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//桶排序是将待排序集合中处于同一个值域的元素存入同一个桶中，也就是根据元素值特性将集合拆分为多个区域，则拆分后形成的多个桶，
//从值域上看是处于有序状态的。对每个桶中元素进行排序，则所有桶中元素构成的集合是已排序的。
//桶排序也是采用分治的思想
//关键在于根据元素值域申请桶的个数，以及每个桶里面的排序算法的选择
//时间复杂度O(n+k),最坏情况是O(n^2),稳定性取决于对桶内元素的排序算法
void BucketSort(vector<int>& arr){
    int n=arr.size();
    int max_value=INT_MIN;
    int min_value=INT_MAX;
    for(int i:arr){
        max_value=max(max_value,i);
        min_value=min(min_value,i);
    }
    //桶的数量
    int buckets=(max_value-min_value)/n+1;
    vector<vector<int>> bucketArr(buckets,vector<int>());
    //将元素入桶
    for(int i:arr){
        int num=(i-min_value)/n;
        bucketArr[num].push_back(i);
    }
    //对每个桶进行排序,在这里直接使用STL的sort函数
    for(int i=0;i<buckets;++i){
        sort(bucketArr[i].begin(),bucketArr[i].end());
    }
    //写回到原数组
    int index=0;
    for(int i=0;i<buckets;++i){
        for(int j=0;j<bucketArr[i].size();++j){
            arr[index++]=bucketArr[i][j];
        }
    }
}

int main()
{
    vector<int> arr{9, 1, 5, 8, 3, 7, 4, 6, 2, 3, 5, 7, 3, 8, 1, 5, 6};
    //QuickSort0(arr);
    BucketSort(arr);
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}