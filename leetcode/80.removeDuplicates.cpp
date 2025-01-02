#include<iostream>
#include<vector>
using namespace std;

/**
 * @brief removeDuplicates函数用于去除给定整数向量中重复次数不超过2次的元素，并返回去重后元素的个数。
 * 
 * 该函数采用快慢指针的技巧，通过对向量进行原地操作来实现去重逻辑，维护一个有效区间 [0, slow]，确保该区间内元素符合去重要求。
 * 
 * @param nums 一个整数类型的引用向量，在原向量上进行去重操作，会修改该向量的内容。
 * @return int 返回去重后向量中元素的个数。
 */
int removeDuplicates(vector<int> &nums) {
    // 如果输入向量为空，直接返回0，因为没有元素需要进行去重操作
    if (nums.size() == 0) return 0;

    int slow = 0, fast = 0;
    int count = 0;
    // 通过while循环遍历整个向量，只要fast指针未超出向量范围，就持续进行去重相关的逻辑判断和操作
    while (fast < nums.size()) {
        // 当fast指针指向的元素和slow指针指向的元素不相等时，意味着遇到了新元素或者重复次数已达上限的元素
        if (nums[fast]!= nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        } 
        // 当slow指针小于fast指针且当前元素重复次数小于2次时，也将该元素移动到slow指针指向的位置（允许重复一次）
        else if (slow < fast && count < 2) {
            slow++;
            nums[slow] = nums[fast];
        }
        fast++;
        count++;
        // 当fast指针未超出向量范围且当前元素与前一个元素不相等时，说明重复次数统计可以重置，将count重置为0
        if (fast < nums.size() && nums[fast]!= nums[fast - 1]) {
            count = 0;
        }
    }
    // 返回去重后向量实际包含的元素个数，由于slow指针最终停留在去重后向量的最后一个元素的位置（索引），元素个数需要在索引基础上加1
    return slow + 1;
}

/**
 * @brief removeAllDulicates函数用于去除给定整数向量中的所有重复元素，并返回去重后元素的个数。
 * 
 * 此函数同样运用快慢指针的方法，在原向量上进行原地去重操作，让fast指针快速遍历向量，slow指针标记去重后元素的存放位置。
 * 
 * @param nums 一个整数类型的引用向量，会直接修改该向量以实现去重效果。
 * @return int 返回去重后向量中元素的个数。
 */
//使用快慢指针进行去重
int removeAllDulicates(vector<int> &nums) {
    // 处理边界情况，若向量为空，则直接返回0，因为不存在元素去重的情况
    if (nums.size() == 0) return 0;

    int fast = 0, slow = 0; 
    // 通过while循环，只要fast指针未超出向量范围，就持续进行去重操作
    while (fast < nums.size()) {
        // 当fast指针指向的元素和slow指针指向的元素不相等时，说明遇到了新元素，将slow指针后移一位，并把新元素赋值到slow指针位置
        if (nums[fast]!= nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
        fast++;
    }

    // 返回去重后向量实际包含的元素个数，因为slow指针最终停留在去重后向量的最后一个元素位置（索引），所以元素个数是slow + 1
    return slow + 1;
}

int main() {
    // 测试removeDuplicates函数
    vector<int> testNums1 = {1, 1, 1, 2, 2, 3};
    int result1 = removeDuplicates(testNums1);
    cout << "removeDuplicates result for {1, 1, 1, 2, 2, 3}: " << result1 << endl;
    for (int num : testNums1) {
        cout << num << " ";
    }
    cout << endl;

    // 测试removeAllDulicates函数
    vector<int> testNums2 = {1, 1, 2, 2, 3, 3};
    int result2 = removeAllDulicates(testNums2);
    cout << "removeAllDulicates result for {1, 1, 2, 2, 3, 3}: " << result2 << endl;
    for (int num : testNums2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
/*执行结果：
removeDuplicates result for {1, 1, 1, 2, 2, 3}: 4
1 1 2 3 
removeAllDulicates result for {1, 1, 2, 2, 3, 3}: 3
1 2 3 
*/