#include <iostream>
#include <string>
#include <vector>

using namespace std;

//KMP算法,关键在于求next数组
vector<int> KMP(string t,string p){
    int lent=t.length(),lenp=p.length();
    vector<int> next(lenp);
    auto get_next=[&]()->void{
        int j=0;
        for(int i=1;i<lenp;++i){
            while(j>0&&p[i]!=p[j]){
                j=next[j-1];
            }
            if(p[i]==p[j]){
                ++j;
            }
            next[i]=j;
        }
    };
    get_next();
    vector<int> res;
    int j=0;
    for(int i=0;i<lent;++i){
        while(j>0&&t[i]!=p[j]){
            j=next[j-1];
        }
        if(t[i]==p[j]){
            ++j;
        }
        if(j==lenp){
            res.push_back(i-j+1);
        }
    }
    return res;
}

int main(){
    string t("aabaacaabaafaacaabaaf");
    string p("aabaaf");
    vector<int> res=KMP(t,p);
    system("pause");
    return 0;
}