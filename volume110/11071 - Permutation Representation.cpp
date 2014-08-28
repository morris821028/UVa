#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;
// 11071 - Permutation Representation
#define MAXN 262144
int A[MAXN], B[MAXN], C[MAXN];
struct PILE {
    int v[512], size;
    PILE *next;
    int label;
    static int MAXSIZE, BUFSIZE;
    static PILE *head;
    PILE() {
        size = label = 0;
        next = NULL;
    }
};
int PILE::MAXSIZE = 512, PILE::BUFSIZE = 0;
PILE* PILE::head = NULL;
int mp[MAXN]; // map
PILE* removePileElement(PILE *where, int pos) {
    if (pos == where->size - 1) {
        where->size--;
        return where->next;
    }
    assert(pos < where->size);
    PILE::BUFSIZE++;
    PILE *m = new PILE();
    m->label = PILE::BUFSIZE;
    assert(m->size == 0);
    for (int i = pos + 1; i < where->size; i++) {
        m->v[m->size++] = where->v[i];
        assert(where->v[i] < MAXN);
        mp[where->v[i]] = m->label;
    }
    where->size = pos;
    m->next = where->next;
    where->next = m;
    return m;
}
int shrinkList() {
    for (PILE *i = PILE::head; i->next != PILE::head; ) {
        PILE *next = i->next;
        int prevsize = i->size;
        int nextsize = next->size;
        if (prevsize + nextsize <= PILE::MAXSIZE) {
            for (int j = 0; j < next->size; j++) {
                i->v[i->size++] = next->v[j];
                mp[next->v[j]] = i->label;
            }
            i->next = next->next;
            delete next;
        } else
            i = i->next;
    }
    return 0;
}
void printPile() {
    PILE *i = PILE::head;
    do {
        for (int j = 0; j < i->size; j++) {
            printf("%d -> ", i->v[j] + 1);
        }
        printf(" | ");
        i = i->next;
    } while (i != PILE::head);
    puts("\n====");
}
void solve(int n) {
//    printPile();
    for (int i = n - 1; i >= 0; i--) {
        PILE *where = NULL;
        int pos = -1;
//        printf("%d\n", i);
        for (PILE *j = PILE::head; ; j = j->next) {
            if (j->label == mp[i]) {
                where = j;
                break;
            }
        }
        assert(where != NULL);
        for (int j = 0; j < where->size; j++) {
            if (where->v[j] == i) {
                pos = j;
                break;
            }
        }
        assert(pos >= 0  && pos < where->size);
        int shift = where->size - pos - 1;
//        printf("%d %d %d\n", node[where].size, pos, shift);
        for (PILE *j = where->next; j != PILE::head; j = j->next) {
            shift += j->size;
        }
//        printf("shift %d\n", shift);
        C[i] = shift;
        PILE::head = removePileElement(where, pos);
        shrinkList();
//        printPile();
    }
    for (PILE *i = PILE::head, *j = i->next; j != PILE::head; j = i->next) {
        delete i;
        i = j;
    }
}
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &B[i]);
        }
//        for (int i = 0; i < n; i++) {
//            A[i] = i + 1;
//            B[i] = A[i];
//        }
//        for (int i = 0; i < n; i++) {
//            int x = rand()%n;
//            int y = rand()%n;
//            swap(B[x], B[y]);
//        }
        for (int i = 0; i < n; i++) {
            C[A[i] - 1] = B[i] - 1;
        }
        
        PILE *node = new PILE();
        PILE::MAXSIZE = (int)sqrt(n) + 1;
        PILE::head = node;
        PILE::BUFSIZE = 0;
        PILE::BUFSIZE++;
        node->label = PILE::BUFSIZE, node->next = node;
        for (int i = 0; i < n; i++) {
            node->v[node->size++] = C[i];
            mp[C[i]] = node->label;
            if (node->size == PILE::MAXSIZE) {
                PILE *tmp = new PILE();
                PILE::BUFSIZE++;
                tmp->label = PILE::BUFSIZE;
                tmp->next = node->next;
                node->next = tmp;
                node = node->next;
            }
        }
        
        solve(n);
        
        for (int i = 0; i < n; i++) {
            printf("%d%c", C[i], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
/*
 5
 1 2 3 4 5
 3 2 5 1 4
 4
 1 2 3 4
 3 4 1 2
*/