/**
 * 剑指Offer 08. 二叉树的下一个节点
 * 
 * 题目描述：
 * 给定一个二叉树和其中的一个节点，请找出中序遍历顺序的下一个节点并且返回。
 * 注意，树中的节点不仅包含左右子指针，同时包含指向父节点的指针。
 * 
 * 示例：
 * 二叉树结构如下：
 *      a
 *     / \
 *    b   c
 *   / \
 *  d   e
 * 
 * 中序遍历顺序是：d, b, e, a, c
 * 如果给定节点b，则其下一个节点是e
 * 如果给定节点e，则其下一个节点是a
 */

#include <iostream>
using namespace std;

// 定义二叉树节点结构
struct TreeLinkNode {
    int val;
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *parent;
    TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Solution {
public:
    /**
     * 解法思路：分情况讨论
     * 1. 如果当前节点有右子树，则下一个节点是右子树中的最左节点
     * 2. 如果当前节点没有右子树：
     *    a) 如果当前节点是其父节点的左子节点，则下一个节点是其父节点
     *    b) 如果当前节点是其父节点的右子节点，则沿着父节点向上遍历，
     *       直到找到一个节点是其父节点的左子节点，则这个节点的父节点就是下一个节点
     * 
     * 时间复杂度：O(h)，其中h为树的高度
     * 空间复杂度：O(1)，只使用了常数级别的额外空间
     */
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if (pNode == nullptr) {
            return nullptr;
        }
        
        TreeLinkNode* next = nullptr;
        
        // 情况1：有右子树，则下一个节点是右子树中的最左节点
        if (pNode->right != nullptr) {
            TreeLinkNode* right = pNode->right;
            while (right->left != nullptr) {
                right = right->left;
            }
            next = right;
        }
        // 情况2：没有右子树
        else if (pNode->parent != nullptr) {
            TreeLinkNode* current = pNode;
            TreeLinkNode* parent = pNode->parent;
            
            // 向上遍历直到找到一个节点是其父节点的左子节点
            while (parent != nullptr && current == parent->right) {
                current = parent;
                parent = parent->parent;
            }
            next = parent;
        }
        
        return next;
    }
};

// 辅助函数：创建测试用的二叉树
TreeLinkNode* createTree() {
    TreeLinkNode* a = new TreeLinkNode('a');
    TreeLinkNode* b = new TreeLinkNode('b');
    TreeLinkNode* c = new TreeLinkNode('c');
    TreeLinkNode* d = new TreeLinkNode('d');
    TreeLinkNode* e = new TreeLinkNode('e');
    
    // 构建树的结构
    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    
    // 设置父节点指针
    b->parent = a;
    c->parent = a;
    d->parent = b;
    e->parent = b;
    
    return a;
}

// 辅助函数：释放二叉树内存
void deleteTree(TreeLinkNode* root) {
    if (root == nullptr) {
        return;
    }
    
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Solution solution;
    
    // 创建测试用的二叉树
    TreeLinkNode* root = createTree();
    
    // 测试用例1：节点有右子树
    TreeLinkNode* test1 = root->left;  // 节点b
    TreeLinkNode* next1 = solution.GetNext(test1);
    cout << "节点b的下一个节点是：" << (char)next1->val << endl;
    
    // 测试用例2：节点没有右子树，且是父节点的左子节点
    TreeLinkNode* test2 = root->left->left;  // 节点d
    TreeLinkNode* next2 = solution.GetNext(test2);
    cout << "节点d的下一个节点是：" << (char)next2->val << endl;
    
    // 测试用例3：节点没有右子树，且是父节点的右子节点
    TreeLinkNode* test3 = root->left->right;  // 节点e
    TreeLinkNode* next3 = solution.GetNext(test3);
    cout << "节点e的下一个节点是：" << (char)next3->val << endl;
    
    // 测试用例4：节点是最后一个节点
    TreeLinkNode* test4 = root->right;  // 节点c
    TreeLinkNode* next4 = solution.GetNext(test4);
    cout << "节点c的下一个节点是：" << (next4 == nullptr ? "nullptr" : string(1, (char)next4->val)) << endl;
    
    // 释放内存
    deleteTree(root);
    
    return 0;
}