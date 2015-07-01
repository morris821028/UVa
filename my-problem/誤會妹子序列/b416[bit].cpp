//#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
const int MAXQ = 1000005;
struct Event {
    int y, qid, qtype;
    Event(int a = 0, int b = 0, int c = 0):
    y(a), qid(b), qtype(c) {}
};
class BIT {
public:
    int v[MAXN], N;
    void init(int N) {
        this->N = N;
        for (int i = 0; i <= N; i++)
            v[i] = 0;
    }
    void add(int x, int val) {
        while (x <= N) {
            v[x] += val;
            x += x&(-x);
        }
    }
    int query(int x) {
        int sum = 0;
        while (x) {
            sum += v[x];
            x -= x&(-x);
        }
        return sum;
    }
} bit;
namespace mLocalStream {
    inline int readchar() {
        const int N = 1048576;
        static char buf[N];
        static char *p = buf, *end = buf;
        if(p == end) {
            if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
            p = buf;
        }
        return *p++;
    }
    inline int ReadInt(int *x) {
        static char c, neg;
        while((c = readchar()) < '-')    {if(c == EOF) return 0;}
        neg = (c == '-') ? -1 : 1;
        *x = (neg == 1) ? c-'0' : 0;
        while((c = readchar()) >= '0')
            *x = (*x << 3) + (*x << 1) + c-'0';
        *x *= neg;
        return 1;
    }
    class Print {
    public:
        static const int N = 1048576;
        char buf[N], *p, *end;
        Print() {
            p = buf, end = buf + N - 1;
        }
        void printInt(int x) {
            static char stk[16];
            int idx = 0;
            stk[idx++] = '\n';
            if (!x)
                stk[idx++] = '0';
            while (x)
                stk[idx++] = x%10 + '0', x /= 10;
            while (idx) {
                if (p == end) {
                    *p = '\0';
                    printf("%s", buf), p = buf;
                }
                *p = stk[--idx], p++;
            }
        }
        ~Print() {
            *p = '\0';
            printf("%s", buf);
        }		
    } bprint;
}

int n, m, A[MAXN], ret[MAXQ];
vector<Event> event[MAXN]; // event[pos]
int main() {
    while (mLocalStream::ReadInt(&n)) {
        mLocalStream::ReadInt(&m);
        for (int i = 1; i <= n; i++)
            mLocalStream::ReadInt(A+i), event[i].clear();
        for (int i = 0; i < m; i++) {
            int l, r, a, b;
            mLocalStream::ReadInt(&l);
            mLocalStream::ReadInt(&r);
            mLocalStream::ReadInt(&a);
            mLocalStream::ReadInt(&b);
            // area [l, a] - [r, b] = [r, b] - [l-1, b] - [r, a-1] + [l-1, a-1]
            event[r].push_back(Event(b, i, 1));
            event[l-1].push_back(Event(b, i, -1));
            event[r].push_back(Event(a-1, i, -1));
            event[l-1].push_back(Event(a-1, i, 1));
            ret[i] = 0;
        }
        
        bit.init(n);
        for (int i = 1; i <= n; i++) {
            bit.add(A[i], 1);
            for (auto &e: event[i]) {
                int val = bit.query(e.y);
                ret[e.qid] += e.qtype * val;
            }
        }
        
        for (int i = 0; i < m; i++)
            printf("%d\n", ret[i]);
    }
    return 0;
}
