#include <iostream>
#include <vector>
using namespace std;

// 定义Solution类，用于封装相关的操作函数
class Solution {
public:
    /**
     * @brief moveZeroes函数用于将输入整数向量nums中的所有0元素移动到向量末尾，同时保持非零元素的相对顺序不变。
     * 这里提供了两种实现方式，一种基于快慢指针，另一种基于类似“雪球”的计数和交换思想。
     *
     * @param nums 一个整数类型的引用向量，在原向量上进行操作，会修改该向量的内容。
     * @param method 选择使用的方法，1表示快慢指针方法，2表示“雪球”方法，默认使用快慢指针方法（值为1）。
     */
    void moveZeroes(vector<int>& nums, int method = 1) {
        if (method == 1) {
            // 快慢指针方法实现移动零元素到末尾
            int fast = 0, slow = 0;
            // 通过while循环，只要fast指针没有超出向量的范围，就持续进行移动零元素的操作
            while (fast < nums.size()) {
                // 当fast指针指向的元素不为0时，说明遇到了非零元素
                if (nums[fast]!= 0) {
                    // 将fast指针指向的非零元素赋值到slow指针位置，实现把非零元素往前移
                    nums[slow] = nums[fast];
                    // slow指针向后移动一位，为下一个非零元素腾出位置
                    slow++;
                }
                // 无论当前元素是否为0，fast指针都向后移动一位，以持续遍历整个向量
                fast++;
            }

            // 循环将从slow位置到向量末尾的元素都赋值为0，即将所有剩余位置填充为0元素，完成零元素移动到末尾的操作
            for (int i = slow; i < nums.size(); i++) {
                nums[i] = 0;
            }
        } else if (method == 2) {
            // “雪球”方法实现移动零元素到末尾
            int snowball = 0;
            // 遍历整个向量nums
            for (int i = 0; i < nums.size(); ++i) {
                // 当遇到元素为0时，“雪球”（即零元素的计数）增加
                if (nums[i] == 0) {
                    snowball++;
                } else if (snowball > 0) {
                    // 当遇到非零元素且之前有零元素（雪球大小大于0）时，进行元素交换
                    int t = nums[i];
                    nums[i] = nums[i - snowball];
                    nums[i - snowball] = t;
                }
            }
        }
    }
};

int main() {
    Solution solution;
    // 定义一个示例向量，包含一些零元素和非零元素，用于测试moveZeroes函数
    vector<int> nums = {0, 1, 0, 3, 12};

    // 使用快慢指针方法调用moveZeroes函数，并输出结果
    vector<int> nums_copy1 = nums;
    solution.moveZeroes(nums_copy1, 1);
    cout << "Using fast-slow pointer method: ";
    for (int num : nums_copy1) {
        cout << num << " ";
    }
    cout << endl;

    // 使用“雪球”方法调用moveZeroes函数，并输出结果
    vector<int> nums_copy2 = nums;
    solution.moveZeroes(nums_copy2, 2);
    cout << "Using snowball method: ";
    for (int num : nums_copy2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}