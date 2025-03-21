/**
 * 剑指Offer 06. 从尾到头打印链表
 * 
 * 题目描述：
 * 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
 * 
 * 示例 1：
 * 输入：head = [1,3,2]
 * 输出：[2,3,1]
 * 
 * 限制：
 * 0 <= 链表长度 <= 10000
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 定义链表节点结构
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    /**
     * 解法一：使用栈
     * 1. 遍历链表，将每个节点的值压入栈中
     * 2. 依次弹出栈中的元素，添加到结果数组中
     * 
     * 时间复杂度：O(n)，需要遍历链表两次
     * 空间复杂度：O(n)，需要额外的栈空间
     */
    vector<int> reversePrint(ListNode* head) {
        stack<int> st;
        ListNode* current = head;
        
        // 将链表节点值压入栈中
        while (current != nullptr) {
            st.push(current->val);
            current = current->next;
        }
        
        // 将栈中的元素弹出到数组中
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
        
        return result;
    }
    
    /**
     * 解法二：递归法
     * 利用递归的特性，在递归返回时将节点值加入结果数组
     * 
     * 时间复杂度：O(n)，需要遍历链表一次
     * 空间复杂度：O(n)，递归调用栈的深度
     */
    vector<int> reversePrintRecursive(ListNode* head) {
        vector<int> result;
        recursiveHelper(head, result);
        return result;
    }
    
private:
    void recursiveHelper(ListNode* node, vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        
        // 先递归到链表末尾
        recursiveHelper(node->next, result);
        // 在递归返回时将当前节点的值加入结果数组
        result.push_back(node->val);
    }
};

// 辅助函数：创建链表
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) {
        return nullptr;
    }
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

// 辅助函数：释放链表内存
void deleteLinkedList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Solution solution;
    
    // 测试用例1：普通链表
    vector<int> test1 = {1, 3, 2};
    ListNode* head1 = createLinkedList(test1);
    
    cout << "测试用例1：" << endl;
    cout << "输入：[1,3,2]" << endl;
    cout << "使用栈的方法输出：[";
    vector<int> result1 = solution.reversePrint(head1);
    for (size_t i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    cout << "使用递归的方法输出：[";
    vector<int> result2 = solution.reversePrintRecursive(head1);
    for (size_t i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    // 释放内存
    deleteLinkedList(head1);
    
    // 测试用例2：空链表
    cout << "\n测试用例2：" << endl;
    cout << "输入：[]" << endl;
    vector<int> result3 = solution.reversePrint(nullptr);
    cout << "输出：[";
    for (size_t i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    return 0;
}