#include <iostream>

// 定义 Solution 类，用于判断一个整数是否为回文数
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        long tmp = x;
        long turn = 0;
        while(tmp) {
            turn = turn * 10 + tmp % 10;
            tmp /= 10;
        }
        return turn == x;  
    }
};

int main() {
    // 创建 Solution 类的对象
    Solution sol;

    // 单元测试用例 1：正数回文数
    int test1 = 121;
    if (sol.isPalindrome(test1)) {
        std::cout << test1 << " 是回文数，测试通过。" << std::endl;
    } else {
        std::cout << test1 << " 不是回文数，测试失败。" << std::endl;
    }

    // 单元测试用例 2：负数
    int test2 = -121;
    if (!sol.isPalindrome(test2)) {
        std::cout << test2 << " 不是回文数，测试通过。" << std::endl;
    } else {
        std::cout << test2 << " 是回文数，测试失败。" << std::endl;
    }

    // 单元测试用例 3：正数非回文数
    int test3 = 123;
    if (!sol.isPalindrome(test3)) {
        std::cout << test3 << " 不是回文数，测试通过。" << std::endl;
    } else {
        std::cout << test3 << " 是回文数，测试失败。" << std::endl;
    }

    // 单元测试用例 4：数字 0
    int test4 = 0;
    if (sol.isPalindrome(test4)) {
        std::cout << test4 << " 是回文数，测试通过。" << std::endl;
    } else {
        std::cout << test4 << " 不是回文数，测试失败。" << std::endl;
    }

    return 0;
}