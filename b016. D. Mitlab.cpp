#include <stdio.h>
#include <sstream>
#include <iostream>
#include <math.h>
using namespace std;
struct M {
    int n, m;
   long long v[50][50];
};
long long det2(M);
void print(M a) {
    puts("======");
    int i, j;
    for(i = 0; i < a.n; i++, puts(""))
        for(j = 0; j < a.m; j++)
            printf("%lld ", a.v[i][j]);
}
M add(M a, M b) {
    M c;
    int i, j;
    if(a.n == b.n && a.m == b.m) {
        c.n = a.n, c.m = a.m;
        for(i = 0; i < a.n; i++)
            for(j = 0; j < a.m; j++)
                c.v[i][j] = a.v[i][j]+b.v[i][j];
    } else
        c.n = c.m = 0;
    return c;
}
M subtract(M a, M b) {
    M c;
    int i, j;
    if(a.n == b.n && a.m == b.m) {
        c.n = a.n, c.m = a.m;
        for(i = 0; i < a.n; i++)
            for(j = 0; j < a.m; j++)
                c.v[i][j] = a.v[i][j]-b.v[i][j];
    } else
        c.n = c.m = 0;
    return c;
}
M multiply(M a, M b) {
    M c;
    int i, j, k;
    if(a.m == b.n) {
        c.n = a.n, c.m = b.m;
        for(i = 0; i < a.n; i++)
            for(j = 0; j < b.m; j++) {
                c.v[i][j] = 0;
                for(k = 0; k < a.m; k++)
                    c.v[i][j] += a.v[i][k]*b.v[k][j];
            }
    } else
        c.n = c.m = 0;
    return c;
}
long long det(M a) {
    if(a.n == 1)    return a.v[0][0];
    if(a.n == 2)    return a.v[0][0]*a.v[1][1]-a.v[0][1]*a.v[1][0];
    long long val = 0;
    M c;
    int i, j;
    c.n = c.m = a.n-1;
    for(i = 1; i < a.n; i++)
        for(j = 1; j < a.n; j++)
            c.v[i-1][j-1] = a.v[i][j];
    for(i = 0; i < a.n; i++) {
        if(i) {
            for(j = 1; j < a.n; j++)
                c.v[j-1][i-1] = a.v[j][i-1];
        }
        val += ((i%2) ? -1 : 1)*det(c)*a.v[0][i];
    }
    return val;
}
M OP1(M a, M b) { // a/b
    M c; // c = adj(b)
    if(b.n != b.m) {
        c.n = c.m = 0;
        return c;
    }
    c.n = b.n, c.m = b.m;
    int i, j, ti, tj;
    for(i = 0; i < b.n; i++) {
        for(j = 0; j < b.n; j++) {
            int cnt = 0;
            M tmp;
            tmp.n = tmp.m = b.n-1;
            for(ti = 0; ti < b.n; ti++) {
                for(tj = 0; tj < b.n; tj++) {
                    if(ti == i || tj == j)
                        continue;
                    tmp.v[cnt/tmp.n][cnt%tmp.n] = b.v[ti][tj];
                    cnt++;
                }
            }
            c.v[j][i] = det(tmp)*((i+j)%2 ? -1 : 1);
        }
    }
    return multiply(a, c);
}
M OP2(M a, M b) { // a\b
    M c; // c = adj(a)
    if(a.n != a.m) {
        c.n = c.m = 0;
        return c;
    }
    c.n = a.n, c.m = a.m;
    int i, j, ti, tj;
    for(i = 0; i < a.n; i++) {
        for(j = 0; j < a.n; j++) {
            int cnt = 0;
            M tmp;
            tmp.n = tmp.m = a.n-1;
            for(ti = 0; ti < a.n; ti++) {
                for(tj = 0; tj < a.n; tj++) {
                    if(ti == i || tj == j)
                        continue;
                    tmp.v[cnt/tmp.n][cnt%tmp.n] = a.v[ti][tj];
                    cnt++;
                }
            }
            c.v[j][i] = det(tmp)*((i+j)%2 ? -1 : 1);
        }
    }
    return multiply(c, b);
}
#define LL long long
#define mod 1000000007LL
LL inverse(LL x, LL p) {
    if(!p)  return 1;
    if(p&1) return x*inverse((x*x)%mod, p>>1)%mod;
    return inverse((x*x)%mod, p>>1);
}
int doubleDet(int n, double A[][35]) {
    int inch = 0, i, j, k;
    double tmp;
    for(i = 0; i < n; i++) {
        int ch = -1;
        for(j = i; j < n; j++) {
            if(fabs(A[j][i]) >= 1e-6) {
                ch = j; break;
            }
        }
        if(ch == -1)
            return 0;
        if(i != ch) {
            for(j = i; j < n; j++)
                tmp = A[i][j], A[i][j] = A[ch][j], A[ch][j] = tmp;
            inch++;
        }
        LL inv, sub;
        for(j = i+1; j < n; j++) {
            if(fabs(A[j][i]) < 1e-6)  continue;
            tmp = A[j][i]/A[i][i];
            for(k = 0; k < n; k++) {
                A[j][k] = A[j][k] - A[i][k]*tmp;
            }
        }
    }
    tmp = 1;
    if(inch&1)  tmp *= -1;
    for(i = 0; i < n; i++)
        tmp *= A[i][i];
    return tmp > 0 ? 1 : -1;
}
long long det2(M a) {
    int inch = 0, n = a.n;
    int i, j, k;
    LL tmp;
    double A[35][35] = {};
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                A[i][j] = a.v[i][j];
    for(i = 0; i < n; i++) {
        int ch = -1;
        for(j = i; j < n; j++) {
            if(a.v[j][i]) {
                ch = j; break;
            }
        }
        if(ch == -1 || !a.v[ch][i]) {
            return 0;
        }
        if(i != ch) {
            for(j = i; j < n; j++)
                tmp = a.v[i][j], a.v[i][j] = a.v[ch][j], a.v[ch][j] = tmp;
            inch++;
        }
        LL inv, sub;
        for(j = i+1; j < n; j++) {
            if(a.v[j][i] == 0)  continue;
            inv = inverse(a.v[i][i], mod-2);
            sub = (a.v[j][i]*inv)%mod;
            for(k = 0; k < n; k++) {
                a.v[j][k] = a.v[j][k] - sub*a.v[i][k]%mod;
                a.v[j][k] = (a.v[j][k]+mod)%mod;
            }
        }
    }
    LL ans = 1;
    for(i = 0; i < n; i++) {
        ans *= a.v[i][i];
        ans %= mod;
    }
    if(inch&1)  ans *= -1;
    ans = (ans+mod)%mod;
    if(ans == 0 || doubleDet(n, A) >= 0)
        return ans;
    else
        return -(mod-ans);
}
M res[26];
int main() {
    char cmd[10000];
    int flag = 1, i, j, k, A, B, C, op, J;
    do {
        for(i = 0; i < 26; i++)
            res[i].n = 0, res[i].m = 0;
        while(1) {
            if(!gets(cmd)) {
                flag = 0;
                break;
            }
            if(cmd[0] == '\0')  break;
            A = cmd[0]-'a';
            J = cmd[4];
            if(J == '[') { // assign
                stringstream sin(cmd+5);
                string token;
                res[A].n = res[A].m = 0;
                int idx = 0, g = 0;
                while(sin >> token) {
                    if(token == ";" || token == "]") {
                        if(g == 1)
                            res[A].n++, res[A].m = idx, idx = 0;
                        g = 0;
                    } else {
                        g = 1;
                        stringstream nin(token);
                        nin >> res[A].v[res[A].n][idx++];
                    }
                }
            } else { // calculate
                B = cmd[4]-'a';
                if(cmd[5] == '\0') {
                    res[A] = res[B];
                    continue;
                }
                op = cmd[6];
                C = cmd[8]-'a';
                if(op == '+')
                    res[A] = add(res[B], res[C]);
                else if(op == '-')
                    res[A] = subtract(res[B], res[C]);
                else if(op == '*')
                    res[A] = multiply(res[B], res[C]);
                else if(op == '/')
                    res[A] = OP1(res[B], res[C]);
                else if(op == '\\')
                    res[A] = OP2(res[B], res[C]);
            }
        }
        for(i = 0; i < 26; i++) {
            printf("[");
            for(j = 0; j < res[i].n; j++) {
                if(j)  printf(" ;");
                for(k = 0; k < res[i].m; k++)
                    printf(" %lld", res[i].v[j][k]);
            }
            printf(" ]\n");
        }
        puts("");
    } while(flag);
    return 0;
}
