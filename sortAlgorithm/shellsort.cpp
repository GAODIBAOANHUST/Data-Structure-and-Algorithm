#include <iostream>
#include <vector>

using namespace std;

//希尔排序是插入排序的一种又称“缩小增量排序”,是直接插入排序算法的一种更高效的改进版本
//希尔排序把记录按下标的一定增量分组，对每组进行插入排序算法
//算法思路:先取一个小于n的整数d1作为第一个增量，把文件全部记录分组。所有距离为d1的倍数的记录放在同一组中。先在各组内进行直接插入排序；然后，取第二个增量d2<d1重复上述的分组和排序，直至增量为1，即所有记录放在同一组中进行插入排序
//时间复杂度与增量序列相关，平均O(nlogn)
//算法是不稳定的
void ShellSort(vector<int>& arr){
    int n=arr.size();
    int gap=1;
    while(gap<n/3){
        gap=gap*3+1;
    }
    // while(gap>=1){
    //     for(int i=gap;i<n;++i){
    //         //对arr[i],arr[i-gap],arr[i-2*gap]...进行插入排序
    //         int temp=arr[i];
    //         int j=i-gap;
    //         while(j>=0&&arr[j]>temp){
    //             arr[j+gap]=arr[j];
    //             j-=gap;
    //         }
    //         arr[j+gap]=temp;
    //     }
    //     gap/=3;
    // }
    while(gap>=1){
        //对每一组进行插入排序
        for(int i=0;i<gap;++i){
            //对arr[i],arr[i+gap],arr[i+2*gap]进行插入排序
            int j=i+gap;
            while(j<n){
                for(int temp=j;temp>=gap;temp-=gap){
                    if(arr[temp-gap]>arr[temp]){
                        swap(arr[temp-gap],arr[temp]);
                    }
                }
                j+=gap;
            }
        }
        gap/=3;
    }
}

int main(){
    vector<int> arr{9,1,5,8,3,7,4,6,2,3,5,7,3,8,1,5,6};
    ShellSort(arr);
    for(int i:arr){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}