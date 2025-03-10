#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool search(int target, vector<vector<int>>& vec) {
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

    bool hasFound(int target, vector<int>& vec) {
        if (vec.empty()) return false;  // 添加空数组检查
        int start = 0, end = vec.size() - 1;
        while (start <= end) {  // 修正循环条件
            int mid = start + (end - start) / 2;  // 修正中间值计算
            if (vec[mid] == target) return true;
            else if (vec[mid] > target) end = mid - 1;  // 修正边界
            else start = mid + 1;
        }
        return false;
    }

    bool findNumIn2DMatrix(int target, vector<vector<int>>& vec) {
        if (vec.empty() || vec[0].empty()) return false;
        for (int i = 0; i < vec.size(); i++) {
            if (hasFound(target, vec[i])) return true;
        }
        return false;
    }
};

void testSearch(int target, vector<vector<int>> vec, bool expected) {
    Solution sol;
    bool result = sol.search(target, vec);
    if (result == expected) {
        cout << "Test search passed!" << endl;
    } else {
        cout << "Test search failed!" << endl;
    }
}

void testHasFound(int target, vector<int> vec, bool expected) {
    Solution sol;
    bool result = sol.hasFound(target, vec);
    if (result == expected) {
        cout << "Test hasFound passed!" << endl;
    } else {
        cout << "Test hasFound failed!" << endl;
    }
}

void testFindNumIn2DMatrix(int target, vector<vector<int>> vec, bool expected) {
    Solution sol;
    bool result = sol.findNumIn2DMatrix(target, vec);
    if (result == expected) {
        cout << "Test findNumIn2DMatrix passed!" << endl;
    } else {
        cout << "Test findNumIn2DMatrix failed!" << endl;
    }
}

int main() {
    // Test cases for search
    testSearch(5, {}, false);  // 空矩阵
    testSearch(3, {{1, 2, 3, 4}}, true);  // 单行矩阵
    testSearch(3, {{1}, {2}, {3}, {4}}, true);  // 单列矩阵
    testSearch(7, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, true);  // 目标值在矩阵中
    testSearch(10, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, false);  // 目标值不在矩阵中
    testSearch(5, {{5}}, true);  // 矩阵只有一行一列
    testSearch(5, {{}, {}}, false);  // 空行矩阵
    testSearch(3, {{1, 2, 3}, {3, 3, 4}, {5, 6, 7}}, true);  // 矩阵有重复值

    // Test cases for hasFound
    testHasFound(3, {1, 2, 3, 4}, true);  // 目标值在数组中
    testHasFound(5, {1, 2, 3, 4}, false);  // 目标值不在数组中
    testHasFound(1, {1}, true);  // 数组只有一个元素
    testHasFound(2, {}, false);  // 空数组

    // Test cases for findNumIn2DMatrix
    testFindNumIn2DMatrix(5, {}, false);  // 空矩阵
    testFindNumIn2DMatrix(3, {{1, 2, 3, 4}}, true);  // 单行矩阵
    testFindNumIn2DMatrix(3, {{1}, {2}, {3}, {4}}, true);  // 单列矩阵
    testFindNumIn2DMatrix(7, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, true);  // 目标值在矩阵中
    testFindNumIn2DMatrix(10, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, false);  // 目标值不在矩阵中
    testFindNumIn2DMatrix(5, {{5}}, true);  // 矩阵只有一行一列
    testFindNumIn2DMatrix(5, {{}, {}}, false);  // 空行矩阵
    testFindNumIn2DMatrix(3, {{1, 2, 3}, {3, 3, 4}, {5, 6, 7}}, true);  // 矩阵有重复值

    return 0;
}