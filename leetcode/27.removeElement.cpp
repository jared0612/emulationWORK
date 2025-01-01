#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
//在原数组移除元素，也就是在原数组上移动数据，
//双指针，front、end；end指向最后一个不是val；
//如果front指向val，则判断end是够是val，如果是则end--；直到不是val，交换front与end位置
//如果front不是则往后移动，直到front=end；end
int removeElement(vector<int> &nums, int val) 
{
    int len = nums.size();
    if(len == 0) return;
    int front = 0;
    int end = len - 1;
    int ans = 0;
    while(front < end) {
        if(nums[front] == val) 
        {
            while (nums[end] == val) end--;
            nums[front++] = nums[end--];
            ans++;
        }
    }

    return  ans;

}

int main() {
    srand(NULL);
    std::vector<int> nums;

    for(int i = 0; i< 10; i++) {
        nums.push_back(rand()%100);
    }

    for(auto c: nums) {
        std::cout << c << std::endl;
    }
    return 0;
}