//Manacher�㷨,�����ұ���
//��¼���±���:����ֱ��,���İ뾶,��Զ�����ұ߽�R,ȡ����Զ�����ұ߽�ʱ�����ĵ�C
//case1:��������ĳ����,����õ㲻����Զ�����ұ߽�,���Ըõ�Ϊ���ı�����չ
//case2:��������ĳ����,����õ�����Զ�����ұ߽���(���赱ǰ�������Ϊi),��i��������ĵ�C����ԳƵ�iL
//      ��CΪ���ĵĻ��ķ�Χ[L...R]
//      ��iL�Ļ�����߽����L,��i�Ļ���ֱ����iL�Ļ���ֱ�����
//      ��iL�Ļ�����߽�С��L,��i�Ļ����ұ߽�ΪR
//      ��iL�Ļ�����߽����L,��i�Ļ����ұ߽�����ΪR,������Ҫ��R��ʼ���ҿ��ܷ���չ 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution{
public:
    //����ַ���s�е��������Ӵ�
    string Manacher(const string& s){
        //Ԥ�����ַ���,����β�Լ�ÿһ���ַ�֮�䶼����"#",ͬʱ��֤�ַ�������һ��Ϊ����
        //"#"��Ϊһ��ʾ��,�κ��ַ�������,����ԭ���г��ֵ��ַ�
        string str("#");
        for(char ch:s){
            str+=ch;
            str+='#';
        }
        //���İ뾶����
        int lens=str.length();
        vector<int> pArr(lens);//��¼ÿ����Ļ��İ뾶����
        int C=-1;//����
        int R=-1;//��Զ�����ұ߽������ҵ�һ��λ��,���ҵ���Ч����R-1λ��
        int max_len_index=0;//��������Ĵ�������
        int max_len=0;//��������Ĵ��ĳ���
        //�������ұ���
        for(int i=0;i<lens;++i){
            //��������ۺϿ���
            //����һ���ǻ��Ĵ�������
            pArr[i]=R>i?min(pArr[2*C-i],R-i):1;
            //�����Ƿ������չ
            while(i+pArr[i]<lens&&i-pArr[i]>-1){
                if(str[i+pArr[i]]!=str[i+pArr[i]]){
                    //ʧ��ֱ���˳�,�Ѿ��޷����ɻ��Ĵ�
                    break;
                }
                //������İ뾶
                pArr[i]++;
            }
            //�����ַ����Ƿ���չ���˸�Զ��λ��
            if(i+pArr[i]>R){
                R=i+pArr[i];
                C=i;
            }
            //��������Ĵ������Լ����ĵ��±�
            if(pArr[i]>max_len){
                max_len=pArr[i];
                max_len_index=i;
            }
        }
        //��Ӧ��s�е�������Ӵ�
        return s.substr(max_len_index-(max_len-2)>>1,max_len-1);
    }
};

int main(){
    string s("babad");
    string res=Solution().Manacher(s);
    system("pause");
    return 0;
}