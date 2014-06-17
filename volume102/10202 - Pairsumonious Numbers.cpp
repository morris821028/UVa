#include <stdio.h>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int main() {
    int n, m, A[10], sum[50];
    int i, j, k;
    while(scanf("%d", &n) == 1) {
        m = n*(n-1)/2;
        for(i = 0; i < m; i++)
            scanf("%d", &sum[i]);
        sort(sum, sum+m);
        map<int, vector<int> > R;
        for(i = 0; i < m; i++)
            R[sum[i]].push_back(i);

        long long used;
        int tmp, idx, flag = 0;
        for(i = 2; i < m; i++) { // A[1]+A[2] = sum[i]
            if((sum[0]+sum[1]+sum[i])%2)
                continue;
            tmp = (sum[0]+sum[1]+sum[i])/2;
            A[0] = tmp - sum[i];
            A[1] = tmp - sum[1];
            A[2] = tmp - sum[0];
            used = 1LL<<i, idx = 2;
            used |= 1, used |= 2;
            for(j = 3; j < n; j++) {
                while((used>>idx)&1)
                    idx++;
                A[j] = sum[idx] - A[0];
                for(k = 0; k < j; k++) { // delete A[j]+A[0-(j-1)]
                    tmp = A[j] + A[k];
                    map<int, vector<int> >::iterator it = R.find(tmp);
                    if(it == R.end())   break;
                    int ok = 0;
                    for(vector<int>::iterator jt = it->second.begin();
                        jt != it->second.end(); jt++) {
                        if(!((used>>(*jt))&1)) {
                            used |= 1LL<<(*jt);
                            ok = 1;
                            break;
                        }
                    }
                    if(!ok) break;
                }
                if(k != j)// fail
                    break;
            }
            if(j == n) {// output ans
                flag = 1;
                printf("%d", A[0]);
                for(j = 1; j < n; j++)
                    printf(" %d", A[j]);
                puts("");
                break;
            }
        }
        if(!flag)
            puts("Impossible");
    }
    return 0;
}
