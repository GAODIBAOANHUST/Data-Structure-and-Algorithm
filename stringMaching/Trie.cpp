//字典树
//Trie，又称前缀树或字典树，是一棵有根树，其每个节点包含以下字段：
//指向子节点的指针数组children。对于本题而言，数组长度为 26，即小写英文字母的数量。此时children[0]对应小写字母a，children[1] 对应小写字母b,children[25] 对应小写字母z。
//布尔字段isEnd，表示该节点是否为字符串的结尾。
//插入字符串
//我们从字典树的根开始，插入字符串。对于当前字符对应的子节点，有两种情况：
//子节点存在。沿着指针移动到子节点，继续处理下一个字符。
//子节点不存在。创建一个新的子节点，记录在children 数组的对应位置上，然后沿着指针移动到子节点，继续搜索下一个字符。
//重复以上步骤，直到处理字符串的最后一个字符，然后将当前节点标记为字符串的结尾。
//查找前缀
//我们从字典树的根开始，查找前缀。对于当前字符对应的子节点，有两种情况：
//子节点存在。沿着指针移动到子节点，继续搜索下一个字符。
//子节点不存在。说明字典树中不包含该前缀，返回空指针。
//重复以上步骤，直到返回空指针或搜索完前缀的最后一个字符。
//若搜索到了前缀的末尾，就说明字典树中存在该前缀。此外,若前缀末尾对应节点的isEnd为真，则说明字典树中存在该字符串。

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//字典树框架实现
class Trie_template{
public:
    Trie_template():children(26,nullptr),isEnd(false),word("") {}

    //插入字符串
    void insert(const string str){
        Trie_template* root=this;
        for(char ch:str){
            if(root->children[ch-'a']==nullptr)
                root->children[ch-'a']=new Trie_template();
            root=root->children[ch-'a'];
        }
        root->isEnd=true;
        root->word=str;
    }

    //查找字符串
    bool search(const string& str){
        Trie_template* root=this;
        for(char ch:str){
            if(root->children[ch-'a']==nullptr)
                return false;
            root=root->children[ch-'a'];
        }
        return true;
    }
private:
    vector<Trie_template*> children;
    bool isEnd;
    string word;
};

//字典树的应用题型有很多,以下整理部分
//leetcode 472 连接词
class Solution472 {
private:
    struct Trie{
        vector<Trie*> children;
        bool isEnd;
        Trie():children(26,nullptr),isEnd(true) {}
    };

    Trie* root;

    void insert(const string& str){
        Trie* node=root;
        for(char ch:str){
            if(node->children[ch-'a']==nullptr)
                node->children[ch-'a']=new Trie();
            node=node->children[ch-'a'];
        }
        node->isEnd=true;
    }

    bool DFS(const string& str,int index){
        if(index==str.length())
            return true;
        Trie* curr=root;
        for(int i=index;i<str.length();++i){
            char ch=str[i];
            if(curr->children[ch-'a']==nullptr)
                return false;
            curr=curr->children[ch-'a'];
            if(curr->isEnd&&DFS(str,i+1))
                return true;
        }
        return false;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        //现将字符串数组按照长度由小到大排序
        sort(words.begin(),words.end(),[](const string& s1,const string& s2){
            return s1.length()<s2.length();
        });
        root=new Trie();
        vector<string> res;
        for(const string& str:words){
            if(str.empty())
                continue;
            if(DFS(str,0)){
                res.push_back(str);
            }else{
                insert(str);
            }
        }
        return res;
    }
};

//