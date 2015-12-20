#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#define NODE_SIZE 100000
struct node *getNode(struct node *head, unsigned int i);
void swap(int *p1, int *p2){
     int tmp;
     tmp = *p1, *p1 = *p2, *p2 = tmp;
}
void shuffle(int next[], int n){
    int i;
    srand(time(NULL));
    for(i = 0; i < n; i++)
          swap(&next[i], &next[rand() % (n - i) + i]);
}
int main(){
    int n;
    struct node array[NODE_SIZE], *head, *ret;
    int next[NODE_SIZE];

    int i;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        next[i] = i;
    shuffle(next, n);
    head = &array[next[0]];
    for(i = 0; i < n - 1; i++)
        array[next[i]].next = &array[next[i + 1]];
    array[next[n - 1]].next = NULL;
    int query[10] = {0, 1, 2, n / 2, n - 1, n, n + 1, n + 2, 2 * n, n * 4 / 5};
    for(i = 0; i < 10; i++){
        ret = getNode(head, query[i]);
        if(query[i] >= n){
            if(ret == NULL)
               printf("PASS\n");
            else
               printf("FAIL\n");
        }else{
            if(ret == &array[next[n - 1 - query[i]]])
               printf("PASS\n");
            else
               printf("FAIL\n");
        }
    }
    return 0;
}
