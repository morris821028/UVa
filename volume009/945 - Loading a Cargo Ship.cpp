#include <stdio.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
struct Container {
    int cap, use, id;
    int carry;
    Container(int a = 0, int b = 0, int c = 0, int d = 0):
    cap(a), use(b), carry(c), id(d) {}
    bool operator<(const Container &a) const {
        if (carry != a.carry)
            return carry < a.carry;
        if (cap - use != a.cap - a.use)
            return cap - use > a.cap - a.use;
        return id < a.id;
    }
};
int main() {
    int N, M, A[MAXN], C[MAXN];
    int cases = 0;
    while (scanf("%d", &N) == 1) {
        int cargo_w = 0, cap_w = 0, load_w = 0;
        for (int i = 0; i < N; i++)
            scanf("%d", &C[i]);
        scanf("%d", &M);
        for (int i = 0; i < M; i++)
            scanf("%d", &A[i]), load_w += A[i];
        
        set<Container> pQ;
        vector<int> ret[MAXN];
        for (int i = 0; i < N; i++) {
            pQ.insert(Container(C[i], 0, 0, i));
            cap_w += C[i];
        }
        for (int i = 0; i < M; i++) {
            Container u = *pQ.begin();
            if (u.use + A[i] > u.cap)
                break;
            u.use += A[i], u.carry += 1;
            cargo_w += A[i], ret[u.id].push_back(A[i]);
            pQ.erase(pQ.begin());
            pQ.insert(u);
        }
        
        int mx_carry = 0;
        for (int i = 0; i < N; i++)
            mx_carry = max(mx_carry, (int) ret[i].size());
        
        if (cases++)    puts("");
        for (int i = mx_carry - 1; i >= 0; i--) {
            for (int j = 0; j < N; j++) {
                if (i < ret[j].size()) {
                    printf("%d", ret[j][i]);
                } else {
                    printf(":");
                }
                printf("%c", j == N-1 ? '\n' : ' ');
            }
        }
        for (int i = 0; i < N; i++)
            printf("=%c", i == N-1 ? '\n' : '=');
        for (int i = 0; i < N; i++)
            printf("%d%c", i+1, i == N-1 ? '\n' : ' ');
        puts("");
        printf("cargo weight: %d\n", cargo_w);
        printf("unused weight: %d\n", cap_w - cargo_w);
        printf("unloaded weight: %d\n", load_w - cargo_w);
    }
    return 0;
}

/*
 3
 5
 10
 5
 
 8
 4
 3
 2
 1
 1
 2
 3
 4
*/