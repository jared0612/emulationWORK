#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool Search(int target, vector<vector<int>> vec) {
        if (vec.empty() || vec[0].empty()) return false;
        int rows = vec.size() - 1;
        int cols = 0;

        while (rows >= 0 && cols < vec[0].size()) {
            if (target == vec[rows][cols]) return true;
            else if (target > vec[rows][cols]) cols++;
            else rows--;
        }
        return false;
    }
};

void test(int target, vector<vector<int>> vec, bool expected) {
    Solution sol;
    bool result = sol.Search(target, vec);
    if (result == expected) {
        cout << "Test passed!" << endl;
    } else {
        cout << "Test failed!" << endl;
    }
}

int main() {
    // Test cases
    test(5, {}, false);  // 空矩阵
    test(3, {{1, 2, 3, 4}}, true);  // 单行矩阵
    test(3, {{1}, {2}, {3}, {4}}, true);  // 单列矩阵
    test(7, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, true);  // 目标值在矩阵中
    test(10, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, false);  // 目标值不在矩阵中
    test(5, {{5}}, true);  // 矩阵只有一行一列
    test(5, {{}, {}}, false);  // 空行矩阵
    test(3, {{1, 2, 3}, {3, 3, 4}, {5, 6, 7}}, true);  // 矩阵有重复值

    return 0;
}