#include <iostream>
#include <vector>

using namespace std;

//ð��������һ�ֽ����������Ļ���˼���ǣ������Ƚ����ڼ�¼�Ĺؼ��֣���������򽻻���ֱ��û�з���ļ�¼Ϊֹ
//��ʼ����
//ÿѭ��һ����������Сֵ����������ǰ��
//ʱ�临�Ӷ�O(n^2)
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

//ð�������Ż�
//��������{2,1,3,4,5,6,7,8,9}���ڵ�һ��ѭ��֮�󽻻���1��2�Ѿ����򣬵����ڵ�һ���������Ȼ����һЩ���õıȽϲ���
//����һ�����λflag
void BubbleSort1(vector<int>& arr){
    int n=arr.size();
    bool flag=true;
    for(int i=1;i<n&&flag;++i){
        flag=false;
        for(int j=n-1;j>=i;--j){
            if(arr[j-1]>arr[j]){
                //�����ݽ�����֤����������״̬
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