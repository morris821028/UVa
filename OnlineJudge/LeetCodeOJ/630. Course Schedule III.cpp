class Solution {
public:
    int scheduleCourse(vector<vector<int>>& C) {
        int n = C.size();
        vector<pair<int, int>> A(n);
        for (int i = 0; i < n; i++)
            A[i] = make_pair(C[i][1], C[i][0]);
        sort(A.begin(), A.end());
        int time = 0;
        priority_queue<int, vector<int>, less<int>> P;
        for (int i = 0; i < n; i++) {
            int d = A[i].first, t = A[i].second;
            if (time + t <= d) {
                time += t;
                P.push(t);
            } else {
                if (!P.empty() && P.top() > t) {
                    time -= P.top() - t;
                    P.pop();
                    P.push(t);
                }
            }
        }
        return P.size();
    }
};
