#include <iostream>
#include <cstdio>
using namespace std;
template<typename TYPE>
inline int ReadNum(TYPE& x) {
    static char c, neg;
    static long long y;
    while((c = getchar()) < '-') {if(c == EOF)return EOF;}
    neg = (c == '-') ? -1 : 1;
    if(c != '.') {
        y = (neg == 1) ? c-'0' : 0;
        while((c = getchar()) >= '0')
            y = (y<<3) + (y<<1) + c-'0';
        x = y;
    }
    if(c == '.') {
        static double t;
        t = 1;
        while((c = getchar()) >= '0')
            t = t/10, x += (c-'0')*t;
    }
    x *= neg;
    return 1;
}
int main() {
    double Double;
    int Int;
    ReadNum(Double);
    ReadNum(Int);
    cout << Double << endl;
    cout << Int << endl;
    return 0;
}
