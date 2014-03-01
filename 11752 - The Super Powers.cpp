#include <stdio.h>
#include <math.h>
#include <set>
#define LLU unsigned long long
using namespace std;
int mark[500] = {}; //32768 65536
void sieve() {
    int i, j;
    mark[1] =  1;
    for(i = 2; i < 500; i++) {
        if(mark[i] == 0) {
            for(j = i+i; j < 500; j += i)
                mark[j] = 1;
        }
    }
}
LLU mpow(LLU x, LLU y) {
    if(y == 0)   return 1;
    if(y&1)
        return x*mpow(x*x, y>>1);
    return mpow(x*x, y>>1);
}
int main() {
    sieve();
    int i, j;
    set<LLU> s;
    s.insert(1);
    for(i = 2; i <= 65536; i++) {
        for(j = 2; j < 500; j++) {
            if(mark[j] == 1) {
                if(j*log2(i) < 64)
                    s.insert(mpow(i, j));
                else    break;
            }
        }
    }
    for(set<LLU>::iterator it = s.begin();
        it != s.end(); it++)
        printf("%llu\n", *it);
    return 0;
}
