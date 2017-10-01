class Solution {
public:
    int64_t str2int(string n) {
        stringstream sin(n);
        int64_t x;
        sin >> x;
        return x;
    }
    string int2str(int64_t x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    string smallestGoodBase(string str_n) {
        /*
            1 + k + k^2 + ... + k^(m-1) = n, k >= 2
            n = (k^m-1) / (k-1), m <= log2(n+1)
        */
        int64_t n = str2int(str_n);
        for (int m = log(n+1)/log(2); m >= 2; m--) {
            int64_t l = 2, r = pow(n, 1.f / (m-1)), mid;
            while (l <= r) {
                mid = l + (r-l)/2;
                int64_t sum = 0;
                for (int i = 0; i < m; i++)
                    sum = sum*mid + 1;
                if (sum == n)
                    return int2str(mid);
                if (sum < n)
                    l = mid+1;
                else
                    r = mid-1;
            }
        }
        return int2str(n-1);
    }
};
