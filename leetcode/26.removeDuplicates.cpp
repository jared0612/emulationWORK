#include<iostream>
#include<vector>
using namespace std;

int removeDupliacates(vector<int> &nums) {
    if(nums.empty()) return 0;

    int maxInt = nums.back();
    vector<int> tmp(maxInt + 1, 0);
    for (auto c : nums) {
        tmp[c]++;
    }
    nums.clear();
    int i = 0;
    while(i <= maxInt) {
        if(tmp[i] > 0) nums.push_back(i); 
    }
    return nums.size();
}

int main() {
    vector<int> nums = {1,1,2,3,4,5,6};
    int k = removeDupliacates(nums);
    cout << k << endl;
    return 0;
}