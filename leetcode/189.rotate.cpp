#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;
//写了半天使用了一个不完备的程序，只能ac一部分用例；
//正确解决思路有三种：
//1、使用辅助数组，先将原数组[len - k,len-1]拷贝到数组前[0, k-1];
//再将原数组的[0，len - k - 1]拷贝到辅助数组[k, len - 1]，
//最后将辅助数组数据拷贝到原数组；
//2、反转数组；将整体数组反转；再分别反转[0, k - 1], [k, len - 1];原地反转；
//实现使用双指针实现数组的反转；可以利用数组的随即索引特性。
//3、我的实现方式，根据数组的拷贝后的索引特性来进行实现；但是不完备，下面会给出参考的代码;

class Solution1 {
public:
    void rotate(vector<int> &nums, int k) {
    int len = nums.size();
    int val = k % len;
    if (val == 0 || nums.size() == 0 || nums.size() == 1) return;
    if(nums.size() == 2 && val == 1) return swap(nums[1], nums[0]);
    if(nums.size() == 3 && val == 1) {swap(nums[1], nums[0]); swap(nums[2], nums[0]); return;}
    if(nums.size() == 3 && val == 2) {swap(nums[1], nums[0]); swap(nums[2], nums[1]); return;}

    for(int i = 0; i < len - 1; ++i) {
        if (i < k)  swap(nums[i], nums[(len - val + i) % len]);
        else {
            int index = (len - val + i) % len;
            swap(nums[i], nums[(len - val + index) % len]);
        }
    }

}

};
class Solution2 {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        int count = std::gcd(k, n);
        for (int start = 0; start < count; ++start) {
            int current = start;
            int prev = nums[start];
            do {
                int next = (current + k) % n;
                swap(nums[next], prev);
                current = next;
            } while (start != current);
        }
    }
};
//作者：力扣官方题解
//链接：https://leetcode.cn/problems/rotate-array/solutions/551039/xuan-zhuan-shu-zu-by-leetcode-solution-nipk/

int main() {
    Solution2 solution;

    // 测试用例1：常规数组，旋转步数小于数组长度
    vector<int> nums1 = {1, 2, 3, 4, 5};
    int k1 = 2;
    solution.rotate(nums1, k1);
    std::cout << "Test case 1: ";
    for (int num : nums1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 测试用例2：空数组
    vector<int> nums2;
    int k2 = 3;
    solution.rotate(nums2, k2);
    std::cout << "Test case 2: ";
    for (int num : nums2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 测试用例3：只有一个元素的数组
    vector<int> nums3 = {1};
    int k3 = 5;
    solution.rotate(nums3, k3);
    std::cout << "Test case 3: ";
    for (int num : nums3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 测试用例4：数组长度和旋转步数相等
    vector<int> nums4 = {1, 2, 3, 4};
    int k4 = 4;
    solution.rotate(nums4, k4);
    std::cout << "Test case 4: ";
    for (int num : nums4) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 测试用例5：较大数组的旋转
    vector<int> nums5 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k5 = 7;
    solution.rotate(nums5, k5);
    std::cout << "Test case 5: ";
    for (int num : nums5) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}