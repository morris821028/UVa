#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

int main() {
    int t;
    char in[50];
    scanf("%d", &t);
    gets(in);
    while(t--) {
        set<string> Q;
        while(gets(in)) {
            if(in[0] == '-')    break;
            Q.insert(in);
        }
        printf("%d\n", Q.size());
    }
    return 0;
}
