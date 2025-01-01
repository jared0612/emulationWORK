#include<iostream>
#include<vector>

using namespace std;

int removeDuplicates(vector<int> &nums) {
    //不让使用额外数组那就是需要使用指针；双指针要分情况处理；
    if(nums.size() == 0) return 0;

        int slow = 0, fast = 0;
        int count = 0;
        while(fast < nums.size()) {
            if(nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            } else if(slow < fast && count < 2) {
                slow++;
                nums[slow] = nums[fast];
            }
            fast++;
            count++;
            if(fast<nums.size() && nums[fast] != nums[fast - 1]) {
                count = 0;
            }
        }
        return slow + 1;

}

int main() {
    return 0;
}