#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Node {
    int v[800], vn;
    int inv_label;
    Node *next;
    Node() {
        vn = 0;
        inv_label = 0;
        next = NULL;
    }
};
int p_size;
void printList(Node *head) {
    Node *idx = head;
    int i, j = 0;
    while(idx != NULL) {
        printf("%d : ", ++j);
        for(i = 0; i < idx->vn; i++)
            printf("%d ", idx->v[i]);
        puts("");
        idx = idx->next;
    }
    puts("====");
}
void freeList(Node *head) {
    Node *idx = head, *pre = NULL;
    while(idx != NULL) {
        pre = idx, idx = idx->next;
        delete pre;
    }
}
void printAns(Node *head) {
    Node *idx = head;
    int i, j = 0;
    while(idx != NULL) {
        if(idx->inv_label == 0)
            for(i = 0; i < idx->vn; i++)
                printf("%d\n", idx->v[i]);
        else
            for(i = idx->vn-1; i >= 0; i--)
                printf("%d\n", idx->v[i]);
        idx = idx->next;
    }
    freeList(head);
}
void invNode(Node *node) {
    static int i, j;
    for(i = 0, j = node->vn-1; i < j; i++, j--)
        swap(node->v[i], node->v[j]);
    node->inv_label = 0;
}
void maintainList(Node *head) {
    Node *idx, *p;
    int i, j;
    idx = head;
    while(idx != NULL && idx->next != NULL) {
        if(idx->vn + idx->next->vn <= 2*p_size) { // merge
            p = idx->next;
            if(idx->inv_label)
                invNode(idx);
            if(p->inv_label)
                invNode(p);
            for(i = idx->vn, j = 0; j < p->vn; i++, j++)
                idx->v[i] = p->v[j];
            idx->vn += p->vn;
            idx->next = p->next;
            delete p;
        }
        idx = idx->next;
    }
}
Node* split(Node *node, int v) { // length(left) = v
    static int i, j;
    if(node->inv_label)
        invNode(node);
    Node *tmp = new Node();
    tmp->next = node->next;
    node->next = tmp;
    tmp->vn = node->vn - v;
    for(i = v, j = 0; i < node->vn; i++, j++)
        tmp->v[j] = node->v[i];
    node->vn = v;
}
Node *stk[10000];
Node* inverseArray(Node *head, int l, int r) {
    static Node *lptr, *rptr, *idx, *pre;
    static Node *lpre, *rnext;
    idx = head;
    int sum_element = 0; // element items
    pre = NULL;
    while(idx != NULL) {//Array[sum_element+1, sum_element+idx->vn]
        if(sum_element+1 < l && l <= sum_element + idx->vn) { // split
            split(idx, l-(sum_element+1)); // left[...l-1], right[l...]
            lptr = idx->next, lpre = idx;
        }
        if(sum_element+1 == l)
            lptr = idx, lpre = pre;
        if(sum_element+1 <= r && r < sum_element + idx->vn) { // split
            split(idx, r-sum_element); // left[...r], right[r+1...]
            rptr = idx->next;
        }
        if(sum_element+idx->vn == r)
            rptr = idx;
        sum_element += idx->vn;
        pre = idx, idx = idx->next;
    }
    //printList(head);
    rnext = rptr->next;
    int stkIdx = 0;
    idx = lptr;
    while(idx != rnext) {
        stk[stkIdx++] = idx;
        idx->inv_label = !idx->inv_label;
        idx = idx->next;
    }
    stkIdx--;
    if(lpre == NULL && rnext == NULL) { //[{ZZZ}]
        head = stk[stkIdx];
        idx = head;
        stkIdx--;
        while(stkIdx >= 0) {
            idx->next = stk[stkIdx--];
            idx = idx->next;
        }
        idx->next = NULL;
    } else if(lpre == NULL && rnext != NULL) {//[{ZZZ}XXX]
        head = rnext;
        idx = rnext;
        while(idx->next != NULL)
            idx = idx->next;
        while(stkIdx >= 0) {
            idx->next = stk[stkIdx--];
            idx = idx->next;
        }
        idx->next = NULL;
    } else if(lpre != NULL && rnext == NULL) {//[XXX{ZZZ}]
        idx = lpre;
        while(stkIdx >= 0) {
            idx->next = stk[stkIdx--];
            idx = idx->next;
        }
        idx->next = NULL;
    } else { //[XXX{ZZZ}XXX]
        lpre->next = rnext;
        idx = rnext;
        while(idx->next != NULL)
            idx = idx->next;
        while(stkIdx >= 0) {
            idx->next = stk[stkIdx--];
            idx = idx->next;
        }
        idx->next = NULL;
    }
    maintainList(head);
    //printList(head);
    return head;
}
int main() {
    int n, m, l, r;
    int i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        //<init>
        p_size = (int)sqrt(n);
        Node *head = new Node(), *pre = NULL, *idx = head;
        for(i = 1; i <= n; i++) {
            if(idx->vn < p_size) {
                idx->v[idx->vn++] = i;
            } else {
                idx->next = new Node();
                pre = idx, idx = idx->next;
                i--;
            }
        }
        //</init>
        while(m--) {
            scanf("%d %d", &l, &r);
            head = inverseArray(head, l, r);
        }
        printAns(head);
    }
    return 0;
}
