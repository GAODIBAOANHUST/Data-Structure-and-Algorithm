//快速幂算法
//基本问题描述:求a^b%mod类型的题目,由于a^b的值可能很大,超过2^63表示范围，因此不可以直接计算
//基于数学公式(a*b)%mod=(a%mod*b%mod)%mod
//例如求3^10
//3^10=9^5,对指数不断除以2,同时底数变为之前的平方.直至找到指数为奇数时
//将指数-1,例如9^5=9^4*9,重复之前的过程
//最后结果可以得到为之前所有的指数为奇数时底数的乘积

#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int mod = 1337;

//求(base^power)%mod
// int fastpow(LL base,LL power){
//     LL res=1;
//     while(power>=1){
//         if(power%2==0){
//             power/=2;
//             base=(base*base)%mod;
//         }else{
//             power--;
//             res=(res*base)%mod;
//             power/=2;
//             base=(base*base)%mod;
//         }
//     }
//     return res;
// }

//上面循环内进行优化
LL fastpow(LL base,LL power){
    LL res=1;
    while(power>=1){
        if(power&1){
            res=(res*base)%mod;
        }
        power>>=1;
        base=(base*base)%mod;
    }
    return res;
}

//leetcode 372 超级次方 递归+快速幂
//例如求a^335:a^335=a^330*a^5,对a^5进行快速幂求结果,a^330=(a^33)^10,令b=a^33,即求b^10,递归
class Solution {
public:
    int superPow(int a, vector<int>& b) {
        if(b.empty()){
            return 1;
        }
        int last=b.back();
        b.pop_back();
        //分治
        int part1=fastpow(a,last);
        int part2=fastpow(superPow(a,b),10);
        return (part1*part2)%mod;
    }
};

int main(){
    system("pause");
    return 0;
}