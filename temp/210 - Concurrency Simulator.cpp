#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <list>
#include <sstream>
using namespace std;
#define MAXN 1024
#define MAXM 32
#define MAXVAR 26
struct Memory {
    char s[MAXM][MAXM];
    int counter;
    void read() {
        int n = 0;
        while (gets(s[n])) {
            if (s[n][0] == 'e' && s[n][1] == 'n' && s[n][2] == 'd')
                return;
            n++;
        }
    }
} mem[MAXN];
int N, unitTime[5], quantum, locked, var[MAXVAR];
deque<int> readyQ, blockQ;
vector<string> decode(string s) {
    vector<string> ret;
    stringstream sin(s);
    while (sin >> s)
        ret.push_back(s);
    return ret;
}
int toInt(string s) {
    int ret;
    stringstream sin(s);
    sin >> ret;
    return ret;
}
void execute(int pid) {
    int q = quantum;
    while (q > 0) {
        vector<string> args = decode(mem[pid].s[mem[pid].counter]);
        if (args[0].length() == 1) {
            var[args[0][0] - 'a'] = toInt(args[2]);
            q -= unitTime[0];
        } else if (args[0] == "print") {
            printf("%d: %d\n", pid+1, var[args[1][0] - 'a']);
            q -= unitTime[1];
        } else if (args[0] == "lock") {
            if (locked) {
                blockQ.push_back(pid);
                return;
            }
            locked = 1;
            q -= unitTime[2];
        } else if (args[0] == "unlock") {
            locked = 0;
            if (!blockQ.empty()) {
                readyQ.push_front(blockQ.front());
                blockQ.pop_front();
            }
            q -= unitTime[3];
        } else if (args[0] == "end") {
            return ;
        }
        mem[pid].counter++;
    }
    readyQ.push_back(pid);
}
void run(int N) {
    for (int i = 0; i < N; i++)
        readyQ.push_back(i), mem[i].counter = 0;
    for (int i = 0; i < MAXVAR; i++)
        var[i] = 0;
    locked = 0;
    int pid;
    while (!readyQ.empty()) {
        pid = readyQ.front(), readyQ.pop_front();
        execute(pid);
    }
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < 5; i++)
            scanf("%d", &unitTime[i]);
        scanf("%d", &quantum);
        while (getchar() != '\n');
        for (int i = 0; i < N; i++)
            mem[i].read();
        
        run(N);
        
        if (testcase)
            puts("");
    }
    return 0;
}
/*

 */
