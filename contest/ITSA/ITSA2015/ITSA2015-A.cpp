#include <stdio.h>
#include <vector>
using namespace std;

int A[1024][512];
char s[16];
int main() {
    int testcase;
    int n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%s", s);
                A[i][j] = s[0] == 'Y';
            }
        }
        
        vector<int> p;
        for (int i = 0; i < n; i++)
            p.push_back(i);
        for (int i = 0; i < m; i++) {
            int Y = 0;
            for (int j = 0; j < p.size(); j++)
                Y += A[p[j]][i] == 1;
            if (Y == p.size() - Y || Y == 0 || Y == p.size())
                continue;
            vector<int> np;
            for (int  j = 0; j < p.size(); j++) {
                if (Y < p.size() - Y) {
                    if (A[p[j]][i] == 1)
                        np.push_back(p[j]);
                } else {
                    if (A[p[j]][i] == 0)
                        np.push_back(p[j]);
                }
            }
            p = np;
        }
        
        for (int i = 0; i < p.size(); i++) {
            printf("%d%c", p[i]+1, i == p.size()-1 ? '\n' : ' ');
        }
    }
    return 0;
}