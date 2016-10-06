// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        long long l = 1, r = n, mid;
        while (l <= r) {
            mid = (l + r)/2;
            int tmp = guess(mid);
            if (tmp == 0)
                return mid;
            if (tmp > 0)
                l = mid+1;
            else
                r = mid-1;
        }
        return mid;
    }
};
