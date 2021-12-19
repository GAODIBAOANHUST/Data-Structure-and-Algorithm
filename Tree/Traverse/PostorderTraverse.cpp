//二叉树的后序遍历,假设最后需要按照前序遍历的方式输出
//也可以按照中右左的顺序压栈,再逆序
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

//递归方式
class Solution_Recursion{
private:
    vector<int> res;
public:
    vector<int> Postorder_Recursion(TreeNode* root){
        //出口条件
        if(!root){
            return res;
        }
        Postorder_Recursion(root->left);
        Postorder_Recursion(root->right);
        res.push_back(root->val);
    }
};

//迭代方式
//pre指向上次处理过的节点,curr指向当前的节点,只有在处理过一个节点之后pre才有含义
//先处理左树,再处理右树,最后处理节点
//参考左程云算法
class Solution_Iteration{
public:
    vector<int> Postorder_Iteration(TreeNode* root){
        vector<int> res;
        if(!root)
            return res;
        stack<TreeNode*> S;
        S.push(root);
        TreeNode* pre=root;
        TreeNode* curr=nullptr;
        while(!S.empty()){
            curr=S.top();//不弹出
            if(curr->left&&pre!=curr->left&&pre!=curr->right){
                //左子节点压栈
                S.push(curr->left);
            }else if(curr->right&&pre!=curr->right){
                //右子节点压栈
                S.push(curr->right);
            }else{
                //左右子树都处理完了
                res.push_back(curr->val);
                S.pop();
                pre=curr;//pre来到上次处理过的节点
            }
        }
        return res;
    }
};

int main(){
    system("pause");
    return 0;
}