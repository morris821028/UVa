#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define hashR 2000000

int hash[hashR], size;
struct Node {
    int v, t, next;
} Node[16000000];
void addHash(int v) {
    int m = abs(v)%hashR;
    int head, prev;
    prev = 0;
    head = hash[m];
    while(head != 0) {
        if(Node[head].v == v) {
            Node[head].t++;
            return;
        } else if(Node[head].v < v) {
            prev = head;
            head = Node[head].next;
        } else
            break;
    }
    ++size;
    if(!prev)
        hash[m] = size;
    else
        Node[prev].next = size;
    Node[size].v = v, Node[size].t = 1;
    Node[size].next = head;
}
int getHash(int v) {
    int m = abs(v)%hashR;
    int head, prev;
    prev = 0;
    head = hash[m];
    while(head != 0) {
        if(Node[head].v == v) {
            return Node[head].t;
        } else if(Node[head].v < v) {
            prev = head;
            head = Node[head].next;
        } else
            return 0;
    }
}
int main() {
    int t, n, A[4000], B[4000], C[4000], D[4000];
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(hash, 0, sizeof(hash));
        size = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                addHash(A[i]+B[j]);
            }
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                ans += getHash(-C[i]-D[j]);
            }
        }
        printf("%d\n", ans);
        if(t)
            puts("");
    }
    return 0;
}
