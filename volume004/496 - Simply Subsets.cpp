#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

int main() {
    stringstream sin;
    string line;
    while(getline(cin, line)) {
        int A[100], B[100];
        int At = 0, Bt = 0, num, i, j;
        sin.clear();
        sin << line;
        while(sin >> num)
            A[At++] = num;
        getline(cin, line);
        sin.clear();
        sin << line;
        while(sin >> num)
            B[Bt++] = num;
        int Act = 0, Bct = 0;
        for(i = 0; i < At; i++) {
            for(j = 0; j < Bt; j++) {
                if(A[i] == B[j]) {
                    Act++;
                    break;
                }
            }
        }
        for(i = 0; i < Bt; i++) {
            for(j = 0; j < At; j++) {
                if(B[i] == A[j]) {
                    Bct++;
                    break;
                }
            }
        }
        if(At == Act && At < Bt)
            puts("A is a proper subset of B");
        else if(Bt == Bct && Bt < At)
            puts("B is a proper subset of A");
        else if(At == Bt && Act == At && Bct == Bt)
            puts("A equals B");
        else if(Act == 0 && Bct == 0)
            puts("A and B are disjoint");
        else
            puts("I'm confused!");
    }
    return 0;
}
