class Solution {
    public boolean hasAlternatingBits(int n) {
        int m = n%2;
        n /= 2;
        while (n != 0) {
            int o = n%2;
            if (o == m)
                return false;
            m = o;
            n /= 2;
        }
        return true;
    }
}
