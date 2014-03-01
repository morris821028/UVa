#include<stdio.h>
#include<stdlib.h>
#define Mod 10
struct list {
    int tag;
    short t;
    struct list *next;
}*HASH[Mod], *curr, *prev, *temp;
void InsHash(int n) {
    int m = (n%Mod + Mod)%Mod;
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
int Find(int v) {
    curr = HASH[(v%Mod + Mod)%Mod];
    while(curr != NULL) {
        if(curr->tag == v)	return curr->t;
    	curr = curr->next;
	}
	return 0;
}

main() {
	int n, a, b, c, A[100];
	while(scanf("%d", &n) == 1) {
		for(a = 0; a < n; a++)
			scanf("%d", &A[a]);
		FreeAll();
		for(a = 0; a < n; a++)
			for(b = 0; b < n; b++)
				for(c = 0; c < n; c++) {
					InsHash(A[a]*A[b]+A[c]);
				}
		int Ans = 0;
		for(a = 0; a < n; a++) {
			if(A[a] != 0)
			for(b = 0; b < n; b++)
				for(c = 0; c < n; c++) {
					Ans += Find(A[a]*(A[b]+A[c]));
				}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
