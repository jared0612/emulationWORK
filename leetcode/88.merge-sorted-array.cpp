//合并两个有序数组，函数无返回值，排序好的数组存放在num1中。
//假设nums1数组有m个数，nums2有n个数字，nums1空间大小是m+n；要求O(m+n)时间复杂度
//解决思路：考虑所有的数组都是排序好的，且nums1空间m+n肯定可以存储所有的数；
//从每个数组的最后有数的位置开始遍历，比较大小，较大的存放在nums最后位置，并且更新为前一位置
//依次向前遍历，直到存放的位置走到0；
#include<vector>
#include<iostream>
class Solution{
public:

    void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n) {
        int k = m + n - 1;
        int i = m - 1;
        int j = n - 1;

        while(i && j) {
            nums1[k] = nums1[i]>nums2[j]?nums1[i--] : nums2[j--]; 
        }
        if (i == 0 && j == 0) return ;
        if (i == 0) 
        {
            for (; j>=0;--j) nums1[j] = nums2[j];
        }
    }
};


int main() {
    //Solution s;
    std::vector<int> nums1 = {1,2,3,4,5,0,0,0,0,0};
    std::vector<int> nums2 = {4,5,6,7,8};
    //s.merge(nums1, 5, nums2, 5);
    for (auto c : nums1) {
        std::cout << c <<std::endl;
    }
    return 0;

}
