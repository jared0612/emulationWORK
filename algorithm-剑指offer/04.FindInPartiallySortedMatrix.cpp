/**
 * 剑指Offer 04. 二维数组中的查找
 * 
 * 题目描述：
 * 在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，
 * 每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，
 * 输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 * 
 * 示例:
 * 现有矩阵 matrix 如下：
 * [
 *   [1,   4,  7, 11, 15],
 *   [2,   5,  8, 12, 19],
 *   [3,   6,  9, 16, 22],
 *   [10, 13, 14, 17, 24],
 *   [18, 21, 23, 26, 30]
 * ]
 * 给定 target = 5，返回 true。
 * 给定 target = 20，返回 false。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /**
     * 解法思路：
     * 从右上角开始查找（也可以从左下角开始）：
     * 1. 如果当前元素等于目标值，返回true
     * 2. 如果当前元素大于目标值，说明当前元素所在列的所有元素都大于目标值，向左移动一列
     * 3. 如果当前元素小于目标值，说明当前元素所在行的所有元素都小于目标值，向下移动一行
     * 
     * 时间复杂度：O(n+m)，最坏情况下，需要遍历n行和m列
     * 空间复杂度：O(1)，只需要常数级别的额外空间
     */
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        // 特殊情况处理：空矩阵
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        // 从右上角开始查找
        int row = 0;
        int col = cols - 1;
        
        while (row < rows && col >= 0) {
            if (matrix[row][col] == target) {
                // 找到目标值
                return true;
            } else if (matrix[row][col] > target) {
                // 当前值大于目标值，向左移动一列
                col--;
            } else {
                // 当前值小于目标值，向下移动一行
                row++;
            }
        }
        
        // 未找到目标值
        return false;
    }
};

int main() {
    // 测试用例
    vector<vector<int>> matrix = {
        {1,  4,  7,  11, 15},
        {2,  5,  8,  12, 19},
        {3,  6,  9,  16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    
    Solution solution;
    
    // 测试存在的值
    cout << "查找数字5: " << (solution.findNumberIn2DArray(matrix, 5) ? "找到了" : "未找到") << endl;
    
    // 测试不存在的值
    cout << "查找数字20: " << (solution.findNumberIn2DArray(matrix, 20) ? "找到了" : "未找到") << endl;
    
    return 0;
}