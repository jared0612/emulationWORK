//一种简单的思路；
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        long tmp = x;
        long turn = 0;
        while(tmp) {
            turn = turn * 10 + tmp % 10;
            tmp /= 10;
        }
        return turn == x;  
    }
};