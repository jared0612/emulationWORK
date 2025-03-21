/**
 * 剑指Offer 05. 替换空格
 * 
 * 题目描述：
 * 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
 * 
 * 示例 1：
 * 输入：s = "We are happy."
 * 输出："We%20are%20happy."
 * 
 * 限制：
 * 0 <= s 的长度 <= 10000
 */

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    /**
     * 解法思路：双指针法
     * 1. 首先遍历一遍字符串，统计空格的数量
     * 2. 根据空格数量计算新字符串的长度
     * 3. 从后向前遍历，用双指针法填充新字符串
     * 
     * 时间复杂度：O(n)，其中n为字符串的长度
     * 空间复杂度：O(1)，只使用了常数级别的额外空间
     */
    string replaceSpace(string s) {
        int spaceCount = 0;
        int originalLength = s.length();
        
        // 统计空格数量
        for (char c : s) {
            if (c == ' ') {
                spaceCount++;
            }
        }
        
        // 计算新字符串的长度
        int newLength = originalLength + spaceCount * 2;
        s.resize(newLength);
        
        // 从后向前填充
        int i = originalLength - 1;  // 原字符串的末尾
        int j = newLength - 1;       // 新字符串的末尾
        
        while (i >= 0) {
            if (s[i] == ' ') {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
            } else {
                s[j--] = s[i];
            }
            i--;
        }
        
        return s;
    }
};

int main() {
    Solution solution;
    
    // 测试用例
    string test1 = "We are happy.";
    cout << "输入：" << test1 << endl;
    cout << "输出：" << solution.replaceSpace(test1) << endl;
    
    // 测试空字符串
    string test2 = "";
    cout << "\n输入：空字符串" << endl;
    cout << "输出：" << solution.replaceSpace(test2) << endl;
    
    // 测试连续空格
    string test3 = "   ";
    cout << "\n输入：" << test3 << endl;
    cout << "输出：" << solution.replaceSpace(test3) << endl;
    
    return 0;
}