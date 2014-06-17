#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
int KNOWN[26] = {}, ENCODED[26] = {};
int A[26], B[26];
bool cmp1(int a, int b) {
    if(KNOWN[a] != KNOWN[b])
        return KNOWN[a] > KNOWN[b];
    return a < b;
}
bool cmp2(int a, int b) {
    if(ENCODED[a] != ENCODED[b])
        return ENCODED[a] > ENCODED[b];
    return a < b;
}
string msg[1048576];
int main() {
    int i, j, k, row = 0;
    while(getline(cin, msg[0]) && msg[0][0]) {
        for(i = 0; i < msg[0].length(); i++) {
            if(msg[0][i] >= 'A' && msg[0][i] <= 'Z')
                KNOWN[msg[0][i]-'A']++;
            if(msg[0][i] >= 'a' && msg[0][i] <= 'z')
                KNOWN[msg[0][i]-'a']++;
        }
    }
    while(getline(cin, msg[row])) {
        for(i = 0; i < msg[row].length(); i++) {
            if(msg[row][i] >= 'A' && msg[row][i] <= 'Z')
                ENCODED[msg[row][i]-'A']++;
            if(msg[row][i] >= 'a' && msg[row][i] <= 'z')
                ENCODED[msg[row][i]-'a']++;
        }
        row++;
    }
    for(i = 0; i < 26; i++)
        A[i] = B[i] = i;
    sort(A, A+26, cmp1);
    sort(B, B+26, cmp2);
    int C[26];
    for(i = 0; i < 26; i++)
        C[B[i]] = A[i];
    for(i = 0; i < row; i++) {
        for(j = 0; j < msg[i].length(); j++) {
            if(msg[i][j] >= 'A' && msg[i][j] <= 'Z')
                putchar(C[msg[i][j]-'A']+'A');
            else if(msg[i][j] >= 'a' && msg[i][j] <= 'z')
                putchar(C[msg[i][j]-'a']+'a');
            else
                putchar(msg[i][j]);
        }
        puts("");
    }
    return 0;
}
