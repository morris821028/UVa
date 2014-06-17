#include <stdio.h>
#include <algorithm>
using namespace std;

struct Node {
    int x, y;
};
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
bool cmp1(Node i, Node j) {
    return i.x < j.x;
}
bool cmp2(Node i, Node j) {
    return i.y < j.y;
}
int main() {
    int N, Q, i, a, b, x, y;
    while(scanf("%d %d", &N, &Q) == 2) {
        int j = 0;
        int *A = new int[N];
        int *ans = new int[Q];
        Node *FA = new Node[Q];
        Node *FB = new Node[Q];
        for(i = 0; i < N; i++) {
            ReadInt(&A[i]);
        }
        for(i = 0; i < Q; i++) {
            ReadInt(&FA[i].x);
            ReadInt(&FB[i].x);
            FA[i].y = i;
            FB[i].y = i;
        }
        sort(A, A+N);
        sort(FA, FA+Q, cmp1);
        sort(FB, FB+Q, cmp1);
        int idx1 = 0, idx2 = 0;
        while(idx1 < N && idx2 < Q) {
            if(A[idx1] < FA[idx2].x)
                idx1++;
            else {
                FA[idx2].x = idx1;
                idx2++;
            }
        }
        while(idx2 < Q) FA[idx2++].x = idx1;

        idx1 = 0, idx2 = 0;
        while(idx1 < N && idx2 < Q) {
            if(A[idx1] <= FB[idx2].x)
                idx1++;
            else {
                FB[idx2].x = idx1;
                idx2++;
            }
        }
        while(idx2 < Q) FB[idx2++].x = idx1;
        for(i = 0; i < Q; i++) {
            ans[FA[i].y] = FA[i].x;
        }
        for(i = 0; i < Q; i++) {
            ans[FB[i].y] = FB[i].x - ans[FB[i].y];
        }
        for(i = 0; i < Q; i++) {
            if(ans[i])
                printf("%d\n", ans[i]);
            else
                puts("The candies are too short");
        }
        delete[] A;
        delete[] FA;
        delete[] FB;
    }
    return 0;
}
