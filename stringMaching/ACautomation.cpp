//AC自动机
//字典树，BFS
//应用场景,给定字符串组words和模式串t,找出在t中可以找到的words中出现的字符串
//假设字符串和字符串数组均为小写字母
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

//build表示构建一个带fail指针的字典树:按照之前的insert函数将所有word插入到字典树之后，采用BFS遍历,query表示查询words中的word是否在模式串t中出现
//一个节点的fail指针表示i->fail=j,即word[j]是word[i]的最长后缀
//step1: 把words中每一个word插入到字典树中
//step2: BFS建立fail指针,首先插入第一层的节点，令其节点的fail指针指向root。之后再遍历后面层
//step3: 实现查询函数query
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
        //先将第一层进入队列，令其fail指向root
        for(int i=0;i<26;++i){
            if(root->next[i]){
                Q.push(root->next[i]);
                root->next[i]->fail=root;
            }
        } 
        while(!Q.empty()){
            auto curr=Q.front();
            Q.pop();
            //处理curr的子节点的fail指针
            for(int i=0;i<26;++i){
                if(curr->next[i]){
                    ACTrie* child=curr->next[i];
                    //fafail表示curr的fail指针
                    ACTrie* fafail=curr->fail;
                    //fafail沿着fail指针不停的追溯，直到找到或者fail为空
                    while(fafail&&fafail->next[i]==nullptr){
                        fafail=fafail->fail;
                    }
                    //退出循环的情况讨论
                    if(fafail==nullptr){
                        child->fail=root;
                    }else{
                        child->fail=fafail->next[i];
                    }
                    //更新exist信息
                    if(!child->fail->exit.empty()){
                        //把fail节点的exist信息更新到该节点来
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
                //顺着fail指针去寻找
                root=root->fail;
            }
            //退出循环情况讨论
            if(root->next[curr]){
                root=root->next[curr];
            }else{
                //到根节点了
                continue;
            }
            if(!root->exit.empty()){
                //依次读取长度
                for(int j=0;j<root->exit.size();++j){
                    int len=root->exit[j];
                    //找到一个p串的单词
                    //输出,具体按照题目要求
                    int start=i-len+1;
                    cout<<"找到字符串为:"<<t.substr(start,len)<<"在模式串t中的起点为:"<<start<<endl;
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