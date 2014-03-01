#include <stdio.h>
#include <iostream>
#include <map>
#include <string.h>
#include <algorithm>
using namespace std;
struct team {
    char name[105];
    int pt, win, lose, tie, score, invscore;
    void init() {
        pt = win = lose = tie = 0;
        score = invscore = 0;
    }
    void record(int a, int b) {
        if(a > b)   win++, pt += 3;
        else if(a < b)  lose++;
        else    tie++, pt++;
        score += a, invscore += b;
    }
};
bool cmp(team a, team b) {
    if(a.pt != b.pt)    return a.pt > b.pt;
    if(a.win != b.win)  return a.win > b.win;
    if(a.score-a.invscore != b.score-b.invscore)
        return a.score-a.invscore > b.score-b.invscore;
    if(a.score != b.score)
        return a.score > b.score;
    if(a.win+a.lose+a.tie != b.win+b.lose+b.tie)
        return a.win+a.lose+a.tie < b.win+b.lose+b.tie;
    return strcasecmp(a.name, b.name) < 0;
}
int main() {
    scanf("%*d ");
    int n, m, cases = 0, i;
    char name[105], buf[105];
    while(gets(name)) {
        scanf("%d", &n);
        getchar();
        map<string, int> R;
        if(cases++) puts("");
        puts(name);
        team A[50];
        for(i = 0; i < n; i++) {
            gets(A[i].name);
            A[i].init();
            R[A[i].name] = i;
        }
        scanf("%d", &m);
        getchar();
        while(m--) {
            gets(buf);
            char name1[50], name2[50];
            int num1, num2;
            sscanf(buf, "%[^#]#%d@%d#%[^\n]", name1, &num1, &num2, name2);
            A[R[name1]].record(num1, num2);
            A[R[name2]].record(num2, num1);
        }
        sort(A, A+n, cmp);
        for(i = 0; i < n; i++)
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                    i+1, A[i].name, A[i].pt, A[i].win+A[i].lose+A[i].tie,
                    A[i].win, A[i].tie, A[i].lose, A[i].score-A[i].invscore,
                    A[i].score, A[i].invscore);
    }
    return 0;
}
