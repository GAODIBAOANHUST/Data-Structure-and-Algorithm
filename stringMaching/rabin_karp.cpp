#include <iostream>
#include <string> 
#include <cmath>

using namespace std;

//rabin_karp算法利用哈希的思想进行快速匹配
//假设字符串t,p。如果字符串t和字符串p的哈希值相同，则t可能包含p(可能产生哈希冲突),之后再采用普通的字符串匹配算法
//假设字符串t长度为m，字符串p长度为n，时间和空间复杂度均为O(m+n)
//返回字符串t包含字符串p的起始位置，如果不包含则返回-1
int rabin_karp(string& t,string& p){
    int m=t.length(),n=p.length();
    long long tval=0,pval=0,h=1;
    const int r=13331;
    const long long mod=1e11+7;
    for(int i=0;i<n-1;++i){
        h=(h*r)%mod;
    }
    //计算pval的值，pval的值在整个计算过程中不再变化
    for(int i=0;i<n;++i){
        pval=(pval*r+p[i])%mod;
        tval=(tval*r+t[i])%mod;
    }
    int pos=-1;
    for(int i=0;i<=m-n;++i){
        if(tval==pval){
            //哈希值相同，匹配字符串
            int j=0;
            for(;j<n;++j){
                if(t[i+j]!=p[j]){
                    break;
                }
            }
            if(j==n){
                pos=i;
                break;
            }
        }
        if(i==m-n){
            //匹配失败
            break;
        }
        //更新t的哈希值
        tval=((tval-t[i]*h)*r+t[i+n])%mod;
        if(tval<0){
            tval+=mod;
        }
    }
    return pos;
}

int main(){
    system("pause");
    return 0;
}