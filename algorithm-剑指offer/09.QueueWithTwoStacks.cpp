/**
 * 剑指Offer 09. 用两个栈实现队列
 * 
 * 题目描述：
 * 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead，
 * 分别完成在队列尾部插入整数和在队列头部删除整数的功能。
 * 若队列中没有元素，deleteHead 操作返回 -1。
 * 
 * 示例 1：
 * 输入：
 * ["CQueue","appendTail","deleteHead","deleteHead"]
 * [[],[3],[],[]]
 * 输出：[null,null,3,-1]
 * 
 * 示例 2：
 * 输入：
 * ["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
 * [[],[],[5],[2],[],[]]
 * 输出：[null,-1,null,null,5,2]
 */

#include <iostream>
#include <stack>
using namespace std;

class CQueue {
private:
    stack<int> stack1; // 用于入队操作
    stack<int> stack2; // 用于出队操作
    
    /**
     * 将stack1中的所有元素移动到stack2中
     * 只有当stack2为空时才需要移动，这样可以保证元素的顺序
     */
    void moveStack1ToStack2() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
    }
    
public:
    /**
     * 构造函数
     * 初始化两个空栈
     */
    CQueue() {
    }
    
    /**
     * 在队列尾部插入整数
     * 直接将元素压入stack1即可
     * 
     * 时间复杂度：O(1)
     * 空间复杂度：O(1)
     */
    void appendTail(int value) {
        stack1.push(value);
    }
    
    /**
     * 从队列头部删除整数
     * 1. 如果stack2为空，将stack1中的所有元素移动到stack2中
     * 2. 如果stack2仍为空，说明队列为空，返回-1
     * 3. 否则，返回stack2的栈顶元素
     * 
     * 时间复杂度：均摊O(1)，最坏情况O(n)
     * 空间复杂度：O(1)
     */
    int deleteHead() {
        moveStack1ToStack2();
        
        if (stack2.empty()) {
            return -1;
        }
        
        int value = stack2.top();
        stack2.pop();
        return value;
    }
};

int main() {
    // 测试用例1
    cout << "测试用例1：" << endl;
    CQueue queue1;
    queue1.appendTail(3);
    cout << queue1.deleteHead() << endl;  // 应输出3
    cout << queue1.deleteHead() << endl;  // 应输出-1
    
    // 测试用例2
    cout << "\n测试用例2：" << endl;
    CQueue queue2;
    cout << queue2.deleteHead() << endl;  // 应输出-1
    queue2.appendTail(5);
    queue2.appendTail(2);
    cout << queue2.deleteHead() << endl;  // 应输出5
    cout << queue2.deleteHead() << endl;  // 应输出2
    
    return 0;
}