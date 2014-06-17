#include <stdio.h>
#include <string.h>
char stmt[105][105];
int n, kind[10], table[10][3];
void check() {
    int i;
    char f1[20], f2[20], f3[20], f4[20], who[20];
    //printf("%d %d %d %d %d %d ---\n", kind[0], kind[1], kind[2], kind[3], kind[4], kind[5]);
    for(i = 0; i < n; i++) {
        if(sscanf(stmt[i], "%s %s %s %s %s", who, f1, f2, f3, f4) == 5) {
            // I/X am/is not (divine, human, evil, lying);
            if(f1[0] == 'I' && f1[1] == '\0') {
                if(kind[who[0]-'A'] == 0) {// divine
                    if(f4[0] == 'd') {return;} // I am not divine.
                }
                if(kind[who[0]-'A'] == 1) {// evil
                    if(f4[0] == 'e' || f4[0] == 'l') {} // I am not evil, I am not lying.
                    else
                        return;
                }
                if(kind[who[0]-'A'] == 2) {// human
                    if(kind[5] == 0) {// day
                        if(f4[0] == 'h') {return;} // I am not human
                    } else {// night
                        if(f4[0] == 'h' || f4[0] == 'l') {}// I am not human, I am not lying.
                        else
                            return;
                    }
                }
            } else {
                if(kind[who[0]-'A'] == 0 || (kind[who[0]-'A'] == 2 && kind[5] == 0)) {
                    // [truth fact] X is not
                    if(kind[f1[0]-'A'] == 0 && f4[0] == 'd') // X is not divine
                        return;
                    if(kind[f1[0]-'A'] == 1 && f4[0] == 'e') // X is not evil
                        return;
                    if(kind[f1[0]-'A'] == 2 && f4[0] == 'h') // X is not human
                        return;
                    if(f4[0] == 'l') { // X is not lying. X must be divine, or human in day.
                        if(kind[f1[0]-'A'] == 0 || (kind[f1[0]-'A'] == 2 && kind[5] == 0)) {}
                        else
                            return;
                    }
                } else { //[not truth fact]
                    if(kind[f1[0]-'A'] == 0 && (f4[0] == 'e' || f4[0] == 'h')) // X is not evil. => true stmt => but who say not truth.
                        return;

                    if(kind[f1[0]-'A'] == 1 && (f4[0] == 'd' || f4[0] == 'h'))
                        return;
                    if(kind[f1[0]-'A'] == 2 && (f4[0] == 'd' || f4[0] == 'e'))
                        return;
                    if(f4[0] == 'l') {// !(X is not lying.) X must be evil, or human in night.
                        if(kind[f1[0]-'A'] == 1 || (kind[f1[0]-'A'] == 2 && kind[5] == 1)) {}
                        else
                            return;
                    }
                }
            }
        } else {
            sscanf(stmt[i], "%s %s %s %s", who, f1, f2, f3);
            //printf("%s %s %s %d\n", f3, f2, f1, kind[0]);
            // I/X am/is (divine, human, evil, lying)
            // It is (day, night)
            if(f1[0] == 'I' && f1[1] == 't') {
                if(kind[who[0]-'A'] == 0 || (kind[who[0]-'A'] == 2 && kind[5] == 0)) {
                    if(kind[5] == 0 && f3[0] == 'n')
                        return;
                    if(kind[5] == 1 && f3[0] == 'd')
                        return;
                } else {
                    if(kind[5] == 0 && f3[0] == 'd')
                        return;
                    if(kind[5] == 1 && f3[0] == 'n')
                        return;
                }
            } else if(f1[0] == 'I' && f1[1] == '\0') {
                if(kind[who[0]-'A'] == 0) {// divine
                    if(f3[0] != 'd') {return;} // I am (evil/human/lying).
                }
                if(kind[who[0]-'A'] == 1) {// evil
                    if(f3[0] == 'l' || f3[0] == 'e') {return;} // I am lying. I am evil.
                }
                if(kind[who[0]-'A'] == 2) {// human
                    if(kind[5] == 0) {// day
                        if(f3[0] != 'h') {return;} // I am (lying/evil/divine).
                    } else {// night
                        if(f3[0] == 'h' || f3[0] == 'l') {return;} // I am human.
                    }
                }
            } else {
                if(kind[who[0]-'A'] == 0 || (kind[who[0]-'A'] == 2 && kind[5] == 0)) {
                    // [truth fact]
                    if(kind[f1[0]-'A'] != 0 && f3[0] == 'd') // X is divine.
                        return;
                    if(kind[f1[0]-'A'] != 1 && f3[0] == 'e')
                        return;
                    if(kind[f1[0]-'A'] != 2 && f3[0] == 'h')
                        return;
                    if(f3[0] == 'l') { // X is lying. X must be evil, or human in night.
                        if(kind[f1[0]-'A'] == 1 || (kind[f1[0]-'A'] == 2 && kind[5] == 1)) {}
                        else
                            return;
                    }
                } else { //[not truth fact]
                    if(kind[f1[0]-'A'] == 0 && f3[0] == 'd') // X is divine.
                        return;
                    if(kind[f1[0]-'A'] == 1 && f3[0] == 'e')
                        return;
                    if(kind[f1[0]-'A'] == 2 && f3[0] == 'h')
                        return;
                    if(f3[0] == 'l') {// !(X is lying.) X must be divine, or human in day.
                        if(kind[f1[0]-'A'] == 0 || (kind[f1[0]-'A'] == 2 && kind[5] == 0)) {}
                        else
                            return;
                    }
                }
            }
        }
    }
   // printf("%d %d %d %d %d %d***\n", kind[0], kind[1], kind[2], kind[3], kind[4], kind[5]);
    for(i = 0; i < 6; i++)
        table[i][kind[i]] = 1;
    /*for(i = 0; i < 5; i++) {
        printf("%c %s\n", i+'A', kind[i] == 0 ? "divine" : (kind[i]==1?"evil":"human"));
    }
    if(kind[5] == 0)
        puts("day");
    else
        puts("night");
    puts("++++");*/
}
void dfs(int nd) {
    if(nd == 6) {
        check();
        return ;
    }
    kind[nd] = 0; // divine/day
    dfs(nd+1);
    kind[nd] = 1; // evil/night
    dfs(nd+1);
    if(nd != 5) {
        kind[nd] = 2;// human
        dfs(nd+1);
    }
}
int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);*/
    int i, cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        while(getchar() != '\n');
        for(i = 0; i < n; i++)
            gets(stmt[i]);
        memset(table, 0, sizeof(table));
        dfs(0);
        printf("Conversation #%d\n", ++cases);
        int hasSol = 1, fact = 0, cnt;
        for(i = 0; i < 6; i++) {
            if(i != 5)
                cnt = table[i][0]+table[i][1]+table[i][2];
            else
                cnt = table[i][0]+table[i][1];
            if(cnt == 0)    hasSol = 0;
            if(cnt == 1)    fact = 1;
        }
        if(!hasSol) {
            puts("This is impossible.\n");
            continue;
        }
        if(fact == 0) {
            puts("No facts are deducible.\n");
            continue;
        }
        for(i = 0; i < 6; i++) {
            if(i != 5)
                cnt = table[i][0]+table[i][1]+table[i][2];
            else
                cnt = table[i][0]+table[i][1];
            if(cnt == 1) {
                if(i < 5) {
                    printf("%c is ", i+'A');
                    if(table[i][0])
                        puts("divine.");
                    else if(table[i][1])
                        puts("evil.");
                    else
                        puts("human.");
                } else {
                    if(table[i][0])
                        puts("It is day.");
                    else
                        puts("It is night.");
                }
            }
        }
        puts("");
    }
    return 0;
}
/*
10
C: D is human.
D: C is not evil.
D: E is not human.
D: E is not lying.
A: I am not human.
C: D is not divine.
D: I am not human.
A: E is not evil.
A: B is human.
C: A is not divine.
*/
