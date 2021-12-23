//Manacher算法,从左到右遍历
//记录以下变量:回文直径,回文半径,最远回文右边界R,取得最远回文右边界时的中心点C
//case1:当遍历到某个点,如果该点不在最远回文右边界,则以该点为中心暴力扩展
//case2:当遍历到某个点,如果该点在最远回文右边界内(假设当前点的坐标为i),作i点关于中心点C的左对称点iL
//      以C为中心的回文范围[L...R]
//      当iL的回文左边界大于L,则i的回文直径与iL的回文直径相等
//      当iL的回文左边界小于L,则i的回文右边界为R
//      当iL的回文左边界等于L,则i的回文右边界至少为R,并且需要从R开始向右看能否扩展 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution{
public:
    //求出字符串s中的最大回文子串
    string Manacher(const string& s){
        //预处理字符串,在首尾以及每一个字符之间都加上"#",同时保证字符串长度一定为奇数
        //"#"仅为一个示例,任何字符都可以,包括原串中出现的字符
        string str("#");
        for(char ch:s){
            str+=ch;
            str+='#';
        }
        //回文半径数组
        int lens=str.length();
        vector<int> pArr(lens);//记录每个点的回文半径数组
        int C=-1;//中心
        int R=-1;//最远回文右边界再往右的一个位置,最右的有效区是R-1位置
        int max_len_index=0;//更新最长回文串的中心
        int max_len=0;//更新最长回文串的长度
        //自左向右遍历
        for(int i=0;i<lens;++i){
            //四种情况综合考虑
            //考虑一定是回文串的区域
            pArr[i]=R>i?min(pArr[2*C-i],R-i):1;
            //考虑是否可以扩展
            while(i+pArr[i]<lens&&i-pArr[i]>-1){
                if(str[i+pArr[i]]!=str[i+pArr[i]]){
                    //失败直接退出,已经无法构成回文串
                    break;
                }
                //扩大回文半径
                pArr[i]++;
            }
            //回文字符串是否扩展到了更远的位置
            if(i+pArr[i]>R){
                R=i+pArr[i];
                C=i;
            }
            //更新最长回文串长度以及中心的下标
            if(pArr[i]>max_len){
                max_len=pArr[i];
                max_len_index=i;
            }
        }
        //对应到s中的最长回文子串
        return s.substr(max_len_index-(max_len-2)>>1,max_len-1);
    }
};

int main(){
    string s("babad");
    string res=Solution().Manacher(s);
    system("pause");
    return 0;
}