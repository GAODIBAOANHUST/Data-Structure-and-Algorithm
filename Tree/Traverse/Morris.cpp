//Morris遍历二叉树
//不占用额外空间,通过叶子节点的空闲指针回溯到当前节点
//Morris遍历的规律,只要一个节点有左子节点,访问两次(根据左子节点的最右节点的右指针指向判断是第一次还是第二次访问);没有左子树的节点,访问一次
//假设来到当前节点curr,开始时curr来到头结点的位置
//case1:如果curr没有左子节点,curr向右移动(curr=curr->right)
//case2:如果curr有左子节点,找到左子树上最右的节点mostright
//      (1)如果mostright的右指针指向空,则让其指向curr,之后curr左移(curr=curr->left)
//      (2)如果mostright的右指针指向curr,则让其指向nullptr,然后curr向右移动
//curr为空时停止遍历
//时间复杂度O(n),空间复杂度O(1)
//可以通过Morris改为先序遍历、中序遍历、后序遍历

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;
    TreeNode(int x):val(x),left(nullptr),right(nullptr) {}
};

//Morris遍历二叉树并输出
class Solution{
public:
    void MorrisTraverse(TreeNode* root){
        if(!root)
            return;
        TreeNode* curr=root;
        TreeNode* mostright=nullptr;
        while(curr){
            mostright=curr->left;
            if(mostright){
                while(mostright->right&&mostright->right!=curr){
                    mostright=mostright->right;
                }
                //退出循环的情况分析
                if(mostright->right==nullptr){
                    mostright->right=curr;
                    curr=curr->left;
                    continue;
                }else{
                    mostright->right=nullptr;
                }
            }
            curr=curr->right;
        }
    }
};

//Morris遍历改二叉树先序遍历
//当访问到节点时直接打印,若再次访问到则跳过
class Solution_Iteration1{
public:
    vector<int> MorrisPreTraverse(TreeNode* root){
        vector<int> res;
        if(!root)
            return res;
        TreeNode* curr=root;
        TreeNode* mostright=nullptr;
        while(curr){
            mostright=curr->left;
            if(mostright){
                while(mostright->right&&mostright->right!=curr){
                    mostright=mostright->right;
                }
                //退出循环的情况分析
                if(mostright->right==nullptr){
                    mostright->right=curr;
                    res.push_back(curr->val);
                    curr=curr->left;
                    continue;
                }else{
                    mostright->right=nullptr;
                }
            }else{
                res.push_back(curr->val);
            }
            curr=curr->right;
        }
        return res;
    }
};

//Morris遍历改二叉树中序遍历
//只能访问一次的节点直接打印,访问两次的节点第二次打印
class Solution_Iteration2{
public:
    vector<int> MorrisInTraverse(TreeNode* root){
        vector<int> res;
        if(!root)
            return res;
        TreeNode* curr=root;
        TreeNode* mostright=nullptr;
        while(curr){
            mostright=curr->left;
            if(mostright){
                while(mostright->right&&mostright->right!=curr){
                    mostright=mostright->right;
                }
                //退出循环的情况分析
                if(mostright->right==nullptr){
                    mostright->right=curr;
                    curr=curr->left;
                    continue;
                }else{
                    mostright->right=nullptr;
                }
            }
            res.push_back(curr->val);
            curr=curr->right;
        }
    }
};

//Morris遍历改二叉树后序遍历
//对于只能访问一次的节点,第一次访问之后什么也不做,第二次访问时逆序打印该节点左子树的右边界
//最后打印整个二叉树的右边界
class Solution_Iteration3{
private:
    vector<int> res;

    TreeNode* Reverse(TreeNode* node){
        TreeNode* pre=nullptr;
        while(node){
            TreeNode* Right=node->right;
            node->right=pre;
            pre=node;
            node=Right;
        }
        return pre;
    }

    void PrintEdge(TreeNode* node){
        //反转节点并接收
        TreeNode* tail=Reverse(node);
        TreeNode* curr=tail;
        while(curr){
            res.push_back(curr->val);
            curr=curr->right;
        }
        Reverse(tail);
    }

public:
    vector<int> MorrisPostTraverse(TreeNode* root){
        if(!root)
            return res;
        TreeNode* mostright=nullptr;
        TreeNode* curr=root;
        while(curr){
            mostright=curr->left;
            if(mostright){
                while(mostright->right&&mostright->right!=curr){
                    mostright=mostright->right;
                }
                //退出情况
                if(mostright->right==nullptr){
                    mostright->right=curr;
                    curr=curr->left;
                    continue;
                }else{
                    //第二次来到该节点
                    mostright->right=nullptr;
                    //逆序打印左边界
                    PrintEdge(curr->left);
                }
            }
            curr=curr->right;
        }
        PrintEdge(root);
        return res;
    }
};

int main(){
    system("pause");
    return 0;
}