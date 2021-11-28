#include <iostream>
#include <vector>

using namespace std;

//基数排序属于分配式排序，按照比较顺序的不同，将其分为LSD和MSD，这里采用LSD方法(最低位优先排序)
//基数排序的思想就是先排好个位，然后排好个位的基础上排十位，以此类推，直到遍历最高位次，排序结束。
//基数排序不是比较排序，而是通过分配和收集的过程来实现排序。初始化 10 个固定的桶，桶下标为 0-9。
//时间复杂度O(k*n),k表示最大元素的位数,空间复杂度O(n+k)
void RadixSort(vector<int>& arr){
    int n=arr.size();
    //统计最大位数
    auto maxbit=[&]()->int{
        int d=1,p=10;
        for(int i:arr){
            if(i>=p){
                ++d;
                p*=10;
            }
        }
        return d;
    };
    int d=maxbit();
    vector<vector<int>> temp;
    int radix=1;
    for(int i=1;i<=d;++i){
        temp.clear();
        temp.resize(10,vector<int>());
        //按位存入桶并计数
        for(int num:arr){
            int x=(num/radix)%10;
            temp[x].push_back(num);
        }
        //取出放回原数组
        int pos=0;
        //遍历10个桶
        for(int i=0;i<10;++i){
            for(int j:temp[i]){
                arr[pos++]=j;
            }
        }
        radix*=10;
    }
}

int main(){
    vector<int> arr{2,5,20,5,976,678,128,123};
    RadixSort(arr);
    for(int i:arr){
        cout<<i<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}