#include <iostream>
#include <string> 
#include <vector>

using namespace std;

//horspool算法匹配的方向是从右向左匹配
//skip数组计算
//step 1:skip数组里面所有位置初始化为p.length()
//step 2:计算p中各个字母对应的skip值,skip[i]=字母i到p串末尾字母的最小距离,并且末尾字母不算在内！！！可以用哈希表记录
 
vector<int> horspool(string t,string p){
    int lent=t.length(); 
    int lenp=p.length();
    //假设全部由小写字母构成,skip数组长度可以初始化为256,包含所有字符
    vector<int> skip(26,lenp);
    //计算skip数组
    for(int i=lenp-2;i>=0;--i){
        if(skip[p[i]-'a']!=lenp){
            continue;
        }
        skip[p[i]-'a']=lenp-i-1;
    }
    int start=0;
    vector<int> res;
    while(start<=lent-lenp){
        int j=lenp-1;
        while(j>=0&&p[j]==t[start+j]){
            --j;
        }
        //匹配成功
        if(j==-1){
            res.push_back(start);
        }
        //skip数组跳转
        start+=skip[t[start+lenp-1]-'a'];
    }
    return res;
}

int main(){
    string t("aabaacaabaafaacaabaaf");
    string p("aabaaf");
    vector<int> res=horspool(t,p);
    system("pause");
    return 0;
}