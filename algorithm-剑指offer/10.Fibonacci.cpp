/**
 * 剑指Offer 10- I. 斐波那契数列
 * 
 * 题目描述：
 * 写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：
 * F(0) = 0,   F(1) = 1
 * F(N) = F(N - 1) + F(N - 2), 其中 N > 1
 * 
 * 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 * 
 * 示例 1：
 * 输入：n = 2
 * 输出：1
 * 
 * 示例 2：
 * 输入：n = 5
 * 输出：5
 * 
 * 提示：
 * 0 <= n <= 100
 */

#include <iostream>
using namespace std;

class Solution {
public:
    /**
     * 解法思路：动态规划（迭代法）
     * 1. 使用两个变量存储前两个数，迭代计算下一个数
     * 2. 注意处理大数，每次计算后都需要取模
     * 
     * 时间复杂度：O(n)，需要迭代n次
     * 空间复杂度：O(1)，只使用了常数级别的额外空间
     */
    int fib(int n) {
        if (n < 2) {
            return n;
        }
        
        const int MOD = 1000000007;
        int prev = 0;    // f(n-2)
        int curr = 1;    // f(n-1)
        int result = 0;  // f(n)
        
        for (int i = 2; i <= n; i++) {
            result = (prev + curr) % MOD;
            prev = curr;
            curr = result;
        }
        
        return result;
    }
    
    /**
     * 解法二：矩阵快速幂（可选，效率更高）
     * 利用矩阵乘法的性质，可以将时间复杂度降低到O(log n)
     * 
     * 时间复杂度：O(log n)
     * 空间复杂度：O(1)
     */
    int fibMatrix(int n) {
        if (n < 2) {
            return n;
        }
        
        const int MOD = 1000000007;
        
        // 定义2x2矩阵结构
        struct Matrix {
            long long a[2][2];
            Matrix() {
                a[0][0] = a[0][1] = a[1][0] = 1;
                a[1][1] = 0;
            }
        };
        
        // 矩阵乘法
        auto multiply = [MOD](const Matrix& A, const Matrix& B) {
            Matrix C;
            C.a[0][0] = (A.a[0][0] * B.a[0][0] + A.a[0][1] * B.a[1][0]) % MOD;
            C.a[0][1] = (A.a[0][0] * B.a[0][1] + A.a[0][1] * B.a[1][1]) % MOD;
            C.a[1][0] = (A.a[1][0] * B.a[0][0] + A.a[1][1] * B.a[1][0]) % MOD;
            C.a[1][1] = (A.a[1][0] * B.a[0][1] + A.a[1][1] * B.a[1][1]) % MOD;
            return C;
        };
        
        // 矩阵快速幂
        auto matrixPow = [&multiply](Matrix A, int n) {
            Matrix result;
            result.a[0][0] = result.a[1][1] = 1;
            result.a[0][1] = result.a[1][0] = 0;
            
            while (n > 0) {
                if (n & 1) {
                    result = multiply(result, A);
                }
                A = multiply(A, A);
                n >>= 1;
            }
            
            return result;
        };
        
        Matrix base;
        Matrix result = matrixPow(base, n - 1);
        return result.a[0][0];
    }
};

int main() {
    Solution solution;
    
    // 测试用例1：小数
    cout << "n = 2: " << solution.fib(2) << endl;  // 应输出1
    cout << "n = 5: " << solution.fib(5) << endl;  // 应输出5
    
    // 测试用例2：边界值
    cout << "n = 0: " << solution.fib(0) << endl;  // 应输出0
    cout << "n = 1: " << solution.fib(1) << endl;  // 应输出1
    
    // 测试用例3：大数（使用矩阵快速幂）
    cout << "n = 45 (普通方法): " << solution.fib(45) << endl;
    cout << "n = 45 (矩阵快速幂): " << solution.fibMatrix(45) << endl;
    
    return 0;
}