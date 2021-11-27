#include <iostream>
#include <vector>
#include <functional>

using namespace std;

//快速排序基本思想：通过一趟排序将待排序记录分割成独立的两部分，其中一部分的关键字均比另一部分的关键字小，则可对这两部分记录继续进行排序，以达到整个序列有序的目的
//时间复杂度与pivot选取有关，最优情况下为O(nlogn)。最坏情况下退化成一个链表为O(n^2)，平均时间复杂度为O(nlogn)
//关键字的比较是跳跃进行的，因此快速排序是不稳定的算法

void MyQuickSort0(vector<int>& arr,int low,int high){
    if(low>=high){
        return;
    }
    int pivot=arr[low];
    //选取左边为枢轴，需要从右边开始比较
    int left=low,right=high;
    while(left<right){
        while(left<right&&arr[right]>=pivot){
            right--;
        }
        if(left<right){
            //比pivot小的换到前面
            swap(arr[left],arr[right]);
        }
        while(left<right&&arr[left]<=pivot){
            left++;
        }
        if(left<right){
            //比pivot大的换到后面
            swap(arr[left],arr[right]);
        }
    }
    MyQuickSort0(arr,low,left-1);
    MyQuickSort0(arr,left+1,high);
}

void QuickSort0(vector<int>& arr) {
    return MyQuickSort0(arr,0,arr.size()-1);
}

//快速排序优化,选取枢轴
//三数取中法，即取三个关键字先进行排序，将中间数作为枢轴，一般是取左端，右端和中间三个数，也可以随机选取，保证该pivot不是最小或者最大的数
//同时优化不必要的交换
void MyQuickSort1(vector<int>& arr,int low,int high){
    if(low>=high){
        return;
    }
    int mid=(low+high-low>>1);
    if(arr[low]>arr[high]){
        //交换左端与右端数据，保证左端较小
        swap(arr[low],arr[high]);
    }
    if(arr[mid]>arr[high]){
        //交换中间与右端数据，保证中间较小
        swap(arr[mid],arr[high]);
    }
    if(arr[low]<arr[mid]){
        //交换左端与中间数据，保证左端是中间数
    }
    int pivot=arr[low];
    //选取左边为枢轴，需要从右边开始比较
    int left=low,right=high;
    while(left<right){
        while(left<right&&arr[right]>=pivot){
            right--;
        }
        if(left<right){
            //比pivot小的换到前面
            // swap(arr[left],arr[right]);
            arr[left]=arr[right];
        }
        while(left<right&&arr[left]<=pivot){
            left++;
        }
        if(left<right){
            //比pivot大的换到后面
            // swap(arr[left],arr[right]);
            arr[right]=arr[left];
        }
    }
    arr[left]=pivot;
    MyQuickSort1(arr,low,left-1);
    MyQuickSort1(arr,left+1,high);
}

void QuickSort1(vector<int>& arr) {
    return MyQuickSort1(arr,0,arr.size()-1);
}

int main()
{
    vector<int> arr{9, 1, 5, 8, 3, 7, 4, 6, 2, 3, 5, 7, 3, 8, 1, 5, 6};
    //QuickSort0(arr);
    QuickSort1(arr);
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}