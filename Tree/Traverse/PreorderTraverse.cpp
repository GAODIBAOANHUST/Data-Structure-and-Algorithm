//二叉树的前序遍历,假设最后需要按照前序遍历的方式输出
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
    vector<int> Preorder_Recursion(TreeNode* root){
        //出口条件
        if(!root){
            return res;
        }
        //遍历到就直接输出
        res.push_back(root->val);
        Preorder_Recursion(root->left);
        Preorder_Recursion(root->right);
    }
};

//迭代方式
//弹出就打印
//如果有右子节点，右子节点压栈
//如果有左子节点，左子节点压栈
class Solution_Iteration{
public:
    vector<int> Preorder_Iteration(TreeNode* root){
        vector<int> res;
        if(!root){
            return res;
        }
        stack<TreeNode*> S;
        S.push(root);
        while(!S.empty()){
            auto curr=S.top();
            S.pop();
            res.push_back(curr->val);
            if(curr->right)
                S.push(curr->right);
            if(curr->left)
                S.push(curr->left);
        }
        return res;
    }
};

int main(){
    system("pause");
    return 0;
}