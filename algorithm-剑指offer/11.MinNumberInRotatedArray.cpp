/**
 * 剑指Offer 11. 旋转数组的最小数字
 * 
 * 题目描述：
 * 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
 * 给你一个可能存在重复元素值的数组 numbers，它原来是一个升序排列的数组，并按上述情形进行了一次旋转。
 * 请返回旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一次旋转，该数组的最小值为 1。
 * 
 * 示例 1：
 * 输入：numbers = [3,4,5,1,2]
 * 输出：1
 * 
 * 示例 2：
 * 输入：numbers = [2,2,2,0,1]
 * 输出：0
 * 
 * 提示：
 * n == numbers.length
 * 1 <= n <= 5000
 * -5000 <= numbers[i] <= 5000
 * numbers 原来是一个升序排序的数组，并进行了 1 至 n 次旋转
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /**
     * 解法思路：二分查找
     * 1. 旋转数组可以看作是两个有序数组，最小值是第二个有序数组的第一个元素
     * 2. 使用二分查找，通过比较中间元素与右边界元素的关系来缩小查找范围
     * 3. 需要特别处理数组中有重复元素的情况
     * 
     * 时间复杂度：平均O(log n)，最坏O(n)（当数组中绝大多数元素都相同时）
     * 空间复杂度：O(1)，只使用了常数级别的额外空间
     */
    int minArray(vector<int>& numbers) {
        int left = 0;
        int right = numbers.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (numbers[mid] < numbers[right]) {
                // 中间元素小于右边界元素，说明最小值在左半部分（包括mid）
                right = mid;
            } else if (numbers[mid] > numbers[right]) {
                // 中间元素大于右边界元素，说明最小值在右半部分
                left = mid + 1;
            } else {
                // 中间元素等于右边界元素，无法确定最小值在哪一部分
                // 只能将右边界左移一位
                right--;
            }
        }
        
        return numbers[left];
    }
};

int main() {
    Solution solution;
    
    // 测试用例1：标准的旋转数组
    vector<int> test1 = {3, 4, 5, 1, 2};
    cout << "输入：[3,4,5,1,2]" << endl;
    cout << "输出：" << solution.minArray(test1) << endl;
    
    // 测试用例2：包含重复元素的旋转数组
    vector<int> test2 = {2, 2, 2, 0, 1};
    cout << "\n输入：[2,2,2,0,1]" << endl;
    cout << "输出：" << solution.minArray(test2) << endl;
    
    // 测试用例3：原数组（没有旋转）
    vector<int> test3 = {1, 2, 3, 4, 5};
    cout << "\n输入：[1,2,3,4,5]" << endl;
    cout << "输出：" << solution.minArray(test3) << endl;
    
    // 测试用例4：只有一个元素的数组
    vector<int> test4 = {1};
    cout << "\n输入：[1]" << endl;
    cout << "输出：" << solution.minArray(test4) << endl;
    
    return 0;
}