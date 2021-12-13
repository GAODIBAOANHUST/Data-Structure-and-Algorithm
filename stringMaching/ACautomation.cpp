//AC�Զ���
//�ֵ�����BFS
//Ӧ�ó���,�����ַ�����words��ģʽ��t,�ҳ���t�п����ҵ���words�г��ֵ��ַ���
//�����ַ������ַ��������ΪСд��ĸ
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

//build��ʾ����һ����failָ����ֵ���:����֮ǰ��insert����������word���뵽�ֵ���֮�󣬲���BFS����,query��ʾ��ѯwords�е�word�Ƿ���ģʽ��t�г���
//һ���ڵ��failָ���ʾi->fail=j,��word[j]��word[i]�����׺
//step1: ��words��ÿһ��word���뵽�ֵ�����
//step2: BFS����failָ��,���Ȳ����һ��Ľڵ㣬����ڵ��failָ��ָ��root��֮���ٱ��������
//step3: ʵ�ֲ�ѯ����query
class ACTrie{
public:
    ACTrie():next(26,nullptr),fail(nullptr) {}

    void insert(string& word){
        ACTrie* root=this;
        for(char ch:word){
            if(root->next[ch-'a']==nullptr){
                root->next[ch-'a']=new ACTrie();
            }
            root=root->next[ch-'a'];
        }
        root->exit.push_back(word.length());
    }

    void build(){
        ACTrie* root=this;
        //�Ƚ���һ�������У�����failָ��root
        for(int i=0;i<26;++i){
            if(root->next[i]){
                Q.push(root->next[i]);
                root->next[i]->fail=root;
            }
        } 
        while(!Q.empty()){
            auto curr=Q.front();
            Q.pop();
            //����curr���ӽڵ��failָ��
            for(int i=0;i<26;++i){
                if(curr->next[i]){
                    ACTrie* child=curr->next[i];
                    //fafail��ʾcurr��failָ��
                    ACTrie* fafail=curr->fail;
                    //fafail����failָ�벻ͣ��׷�ݣ�ֱ���ҵ�����failΪ��
                    while(fafail&&fafail->next[i]==nullptr){
                        fafail=fafail->fail;
                    }
                    //�˳�ѭ�����������
                    if(fafail==nullptr){
                        child->fail=root;
                    }else{
                        child->fail=fafail->next[i];
                    }
                    //����exist��Ϣ
                    if(!child->fail->exit.empty()){
                        //��fail�ڵ��exist��Ϣ���µ��ýڵ���
                        for(int i:child->fail->exit){
                            child->exit.push_back(i);
                        }
                    }
                    Q.push(child);
                }
            }
        }
    }

    void query(const string& t){
        ACTrie* root=this;
        for(int i=0;i<t.length();++i){
            int curr=t[i]-'a';
            while(root->next[curr]==nullptr&&root->fail){
                //˳��failָ��ȥѰ��
                root=root->fail;
            }
            //�˳�ѭ���������
            if(root->next[curr]){
                root=root->next[curr];
            }else{
                //�����ڵ���
                continue;
            }
            if(!root->exit.empty()){
                //���ζ�ȡ����
                for(int j=0;j<root->exit.size();++j){
                    int len=root->exit[j];
                    //�ҵ�һ��p���ĵ���
                    //���,���尴����ĿҪ��
                    int start=i-len+1;
                    cout<<"�ҵ��ַ���Ϊ:"<<t.substr(start,len)<<"��ģʽ��t�е����Ϊ:"<<start<<endl;
                }
            }
        }
    }

private:
    vector<ACTrie*> next;
    vector<int> exit;
    ACTrie* fail;
    queue<ACTrie*> Q;
};

int main(){
    vector<string> words{"he","hers","his","she"};
    string t("ahishers");
    ACTrie* trie=new ACTrie();
    for(string& word:words){
        trie->insert(word);
    }
    trie->build();
    trie->query(t);
    system("pause");
    return 0;
}