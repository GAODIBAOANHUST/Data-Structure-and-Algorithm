//二叉树的中序遍历,假设最后需要按照前序遍历的方式输出
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
    vector<int> Inorder_Recursion(TreeNode* root){
        //出口条件
        if(!root){
            return res;
        }
        //先遍历左子节点
        Inorder_Recursion(root->left);
        res.push_back(root->val);
        Inorder_Recursion(root->right);
    }
};

//迭代方式
//整条树的左边界依次入栈
//当上述条件无法满足,弹出栈顶元素并打印,来到栈顶元素的右子节点
class Solution_Iteration{
public:
    vector<int> Inorder_Iteration(TreeNode* root){
        vector<int> res;
        TreeNode* curr=root;
        stack<TreeNode*> S;
        while(!S.empty()||curr){
            //将树的左边界全部依次压入栈中
            while(curr){
                S.push(curr);
                curr=curr->left;
            }
            //curr为空,此时S的顶端是最左节点
            curr=S.top();
            S.pop();
            res.push_back(curr->val);
            curr=curr->right;
        }
        return res;
    }
};

int main(){
    system("pause");
    return 0;
}