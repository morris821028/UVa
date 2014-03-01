#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
struct E {
    string s;
    E(string c):s(c){}
    bool operator<(const E &a) const {
        if(s.length() != a.s.length())
            return s.length() < a.s.length();
        return s.compare(a.s) < 0;
    }
};
int main() {
    string a, b, c;
    vector<E> buf;
    int i, j, p, q;
    for(i = 1; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            if(i == j)  continue;
            a = "";
            for(p = 1; p <= 100; p++) {
                a += (char)(i+'0');
                b = "";
                for(q = 1; p+q <= 100; q++) {
                    b += (char)(j+'0');
                    buf.push_back(E(a+b));
                }
            }
        }
    }
    sort(buf.begin(), buf.end());
    int n;
    char strbuf[50];
    while(scanf("%d", &n) == 1 && n) {
        printf("%d: ", n);
        sprintf(strbuf, "%d", n);
        E N(strbuf);
        vector<E>::iterator it = upper_bound(buf.begin(), buf.end(), N);
        int found = 0;
        for(; it != buf.end(); it++) {
            int len = it->s.length(), cnt = 0;
            for(i = 0; i < len; i++) {
                cnt = cnt * 10 + (it->s)[i]-'0';
                cnt %= n;
            }
            if(cnt == 0) {
                int s = (it->s)[0], t = (it->s)[len-1];
                int p = 0, q = 0;
                int j = 0, k = len-1;
                while((it->s)[j] == s)  p++, j++;
                while((it->s)[k] == t)  q++, k--;
                printf("%d %c %d %c\n", p, s, q, t);
                found = 1;
                break;
            }
        }
    }
    return 0;
}
