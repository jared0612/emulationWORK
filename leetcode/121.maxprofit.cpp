#include<iostream>
#include<vector>
#include<algorithm>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        //首先做一个判空判断，边界判断；
        if(prices.empty()) {
            return 0;
        }
        int inf = 1e9;
        int minprice = inf, maxprofit = 0;
        for (int price : prices) {
            //一直计算最大的差值并做更新，
            //往后计算过程中一直更新最小值，每个阶段的最大利润都是减去区域最小值得到的。
            maxprofit = std::max(maxprofit, price - minprice);
            minprice = std::min(price, minprice);
        }
        return maxprofit;
    }
};

int main() {
    Solution s;
    std::vector<int> prices1 = {7,1,5,3,6,4};
    std::vector<int> prices2 = {7,6,4,3,1};
    std::vector<int> prices3 = {1,2,3,4,5};

    // 测试用例 1：应该得到 5 的利润
    int result1 = s.maxProfit(prices1);
    std::cout << "Max profit for prices1: " << result1 << std::endl;

    // 测试用例 2：应该得到 0 的利润
    int result2 = s.maxProfit(prices2);
    std::cout << "Max profit for prices2: " << result2 << std::endl;

    // 测试用例 3：应该得到 4 的利润
    int result3 = s.maxProfit(prices3);
    std::cout << "Max profit for prices3: " << result3 << std::endl;
}