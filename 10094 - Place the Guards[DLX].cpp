#include <stdio.h>
#include <algorithm>
using namespace std;
struct DancingLinks {
    int left, right, up, down, ch;
    int rh; // 額外的 data
} DL[4000000 + 10001];
int s[10001], o[10001], head, size;
int n; // this problem need n for output process.
void remove(int c) {
    DL[DL[c].right].left = DL[c].left;
    DL[DL[c].left].right = DL[c].right;
    int i, j;
    for(i = DL[c].down; i != c; i = DL[i].down) {
        for(j = DL[i].right; j != i; j = DL[j].right) {
            DL[DL[j].down].up = DL[j].up;
            DL[DL[j].up].down = DL[j].down;
            s[DL[j].ch]--;
        }
    }
}
void resume(int c) {
    int i, j;
    for(i = DL[c].down; i != c; i = DL[i].down) {
        for(j = DL[i].left; j != i; j = DL[j].left) {
            DL[DL[j].down].up = j;
            DL[DL[j].up].down = j;
            s[DL[j].ch]++;
        }
    }
    DL[DL[c].right].left = c;
    DL[DL[c].left].right = c;
}
int found;
void print() {
    int i;
    int ans[1000];
    for(i = 0; i < n; i++) {
        ans[DL[o[i]].rh/n] = DL[o[i]].rh%n;
        //printf("(%d, %d)", DL[o[i]].rh/n+1, DL[o[i]].rh%n+1);
    }
    //puts("");
    printf("%d", ans[0]+1);
    for(i = 1; i < n; i++)
        printf(" %d", ans[i]+1);
    puts("");
}
void dfs(int dep) {
    if(found)   return;
    if(dep == n) { // just match for row&column
        found = 1;
        print();
        return;
    }
    int tmp = 0xffff, c, i, j;
    for(i = DL[head].right; i != head; i = DL[i].right) {
        if(i > 2*n)
            break;
        if(s[i] <= tmp)
            tmp = s[i], c = i;
    }
    remove(c);
    for(i = DL[c].down; i != c; i = DL[i].down) {
        o[dep] = i;
        for(j = DL[i].right; j != i; j = DL[j].right)
            remove(DL[j].ch);
        dfs(dep+1);
        if(found)   return;
        for(j = DL[i].left; j != i; j = DL[j].left)
            resume(DL[j].ch);
    }
    resume(c);
}
int getnode(int u, int d, int l, int r) {
    DL[size].up = u, DL[size].down = d;
    DL[size].left = l, DL[size].right = r;
    DL[u].down = DL[d].up = DL[l].right = DL[r].left = size;
    return size++;
}
void newrow(int r[], int rn, int rh) {
    int i, j, h;
    for(i = 0; i < rn; i++) {
        DL[size].ch = r[i], s[r[i]]++;
        DL[size].rh = rh; // 額外的 data
        if(i) {
            j = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, DL[h].left, h);
        } else {
            h = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, size, size);
        }
    }
}
void init(int c) {// total column
    size = 0;
    head = getnode(0,0,0,0);
    int i;
    for(i = 1; i <= c; i++) {
        getnode(i, i, DL[head].left, head);
        DL[i].ch = i, s[i] = 0;
    }
}
int main() {
    int i, j, k;
    int P[2005];
    srand(514);
    while(scanf("%d", &n) == 1) {
        found = 0;
        int column = n+n+2*(2*n-1); //row + cloumn + two diagonal
        init(column);
        int row[10], rn;
        srand(rand());
        for(i = 1; i <= 2*n; i++)
            P[i] = i;
        int times = rand()%5140+5140;
        for(i = 1; i <= times; i++) {
            j = rand()%(2*n)+1;
            k = rand()%(2*n)+1;
            swap(P[j], P[k]);
        }
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                rn = 0;
                //row[rn++] = i;     // row
                //row[rn++] = n+j;   // column
                row[rn++] = P[i];
                row[rn++] = P[n+j];
                if(i >= j) {
                    row[rn++] = i-j+1+(2*n);//left diagonal
                } else {
                    row[rn++] = j-i+n+(2*n);//left diagonal
                }
                int tx = i, ty = n-j+1;
                if(tx >= ty) {
                    row[rn++] = tx-ty+1+(2*n+2*n-1);//right diagonal
                } else {
                    row[rn++] = ty-tx+n+(2*n+2*n-1);//right diagonal
                }
                //printf("(%d %d) %d %d %d %d\n", i, j, row[0], row[1], row[2], row[3]);
                newrow(row, rn, (i-1)*n+j-1);
            }
        }
        dfs(0);
        if(!found)
            puts("Impossible");
    }
    return 0;
}

