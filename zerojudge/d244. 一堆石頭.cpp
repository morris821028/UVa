#include<stdio.h>
#include<stdlib.h>
#define Mod 123
struct list {
    int tag;
    short t;
    struct list *next;
}*HASH[Mod], *curr, *prev, *temp;
void InsHash(int n) {
    int m = n%Mod;
    if(HASH[m] == NULL) {
        curr = (struct list *)malloc(sizeof(struct list));
        curr->tag = n, curr->next = NULL, curr->t = 1;
        HASH[m] = curr;return;
    }
    temp = HASH[m], prev = NULL;
    while(temp->tag <= n) {
        if(temp->tag == n) {temp->t++;return;}
        if(temp->next != NULL)
            prev = temp, temp = temp->next;
        else {
            curr = (struct list *)malloc(sizeof(struct list));
            curr->tag = n, curr->next = NULL, curr->t = 1;
            temp->next = curr; return;
        }
    }
    if(prev != NULL) {
        curr = (struct list *)malloc(sizeof(struct list));
        curr->tag = n, curr->t = 1;
        prev->next = curr, curr->next = temp;
    }
    else {
        curr = (struct list *)malloc(sizeof(struct list));
        curr->tag = n, curr->t = 1;
        HASH[m] = curr, curr->next = temp;
    }
    return;
}
void FreeAll() {
    int a;
    for(a = 0; a < Mod; a++) {
        curr = HASH[a], prev = NULL;
        while(curr != NULL) {
            prev = curr, curr = curr->next;
            free(prev);
        }
        HASH[a] = NULL;
    }
}
void Find() {
    int a;
    for(a = 0; a < Mod; a++) {
        curr = HASH[a];
        while(curr != NULL) {
            if(curr->t == 2) {
            	printf("%d\n", curr->tag);
            	return ;
			}
            curr = curr->next;
        }
    }
}
int Input() { 
    char cha; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n' || cha == EOF) break; 
    if(cha == EOF) return -1;
    x = cha-48; 
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x; 
}
main() {
    int n;
	FreeAll();
    while(1) {
		n = Input();
		if(n == -1)	break;
		InsHash(n);
    }
    Find(),	FreeAll();
    return 0;
}
