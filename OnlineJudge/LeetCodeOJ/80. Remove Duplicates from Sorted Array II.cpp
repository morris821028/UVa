class Solution {
public:
    int removeDuplicates(vector<int>& A) {
        int n = A.size(), m = 0;
        for (int i = 0; i < n; ) {
            int cnt = 0, t = A[i];
            while (i < n && A[i] == t)
                i++, cnt++;
            for (int j = 0; j < 2 && cnt > 0; j++, cnt--)
                A[m++] = t;
        }
        return m;
    }
};
