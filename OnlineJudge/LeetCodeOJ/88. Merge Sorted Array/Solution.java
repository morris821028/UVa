public class Solution {
    private static int countDigit(long x) {
        int ret = 0;
        while (x > 0) {
            ret ++;
            x /= 10;
        }
        return ret;
    }
    private static long sumDigit(long x) {
        if (x == 0)
            return 0;
        int len = countDigit(x);
        long sum = 0, ten = 1;
        for (int i = 1; i < len; i++) {
            sum += ten * 9 * i;
            ten *= 10;
        }
        sum += (x - ten + 1) * len;
        return sum;
    }
    private static long lowerBoundNumber(long n) {
        long l = 1, r = n, mid, ret = 0;
        while (l <= r) {
            mid = (l + r) / 2;
            long v = sumDigit(mid);
            if (v < n) {
                l = mid + 1;
                ret = mid;
            } else {
                r = mid - 1;
            }
        }
        return ret;
    }
    public int findNthDigit(int n) {
        long d = lowerBoundNumber(n);
        n -= sumDigit(d);
        String p = "" + (d+1);
        return p.charAt(n-1) - '0';
    }
}
