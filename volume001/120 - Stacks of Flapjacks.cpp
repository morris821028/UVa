#include <iostream>
#include <cstdio>
#include <sstream>
using namespace std;

int main() {
    string line;
    while(getline(cin, line)) {
        stringstream sin(line);
        int A[1000], n = 0;
        int flip[1000], step = 0;
        int i, j, k, tmp;
        while(sin >> A[n])
            n++;

        printf("%d", A[0]);
        for(i = 1; i < n; i++) {
            printf(" %d", A[i]);
        }
        puts("");
        for(i = 0; i < n; i++) {
            int idx = n-i-1;
            for(j = 0; j < n-i; j++) {
                if(A[idx] < A[j])
                    idx = j;
            }
            if(idx == n-i-1)
                continue;
            if(idx) {
                flip[step++] = n-idx;
                for(j = 0, k = idx; j < k; j++, k--)
                    tmp = A[j], A[j] = A[k], A[k] = tmp;
            }
            flip[step++] = i+1;
            for(j = 0, k = n-i-1; j < k; j++, k--)
                tmp = A[j], A[j] = A[k], A[k] = tmp;
        }
        for(i = 0; i < step; i++)
            printf("%d ", flip[i]);
        puts("0");
    }
    return 0;
}
