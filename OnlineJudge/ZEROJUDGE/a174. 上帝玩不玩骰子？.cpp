#include<stdio.h>
#include<stdlib.h>
int Mod;
struct list {
	int tag;
	struct list *next;
}*HASH[200], *curr, *prev, *temp;
void InsHash(int n) {
	int m = n%Mod;
	if(HASH[m] == NULL) {
		curr = (struct list *)malloc(sizeof(struct list));
		curr->tag = n, curr->next = NULL;
		HASH[m] = curr;return;
	}
	temp = HASH[m], prev = NULL;
	while(temp->tag <= n) {
		if(temp->tag == n) return;
		if(temp->next != NULL)
			prev = temp, temp = temp->next;
		else {
			curr = (struct list *)malloc(sizeof(struct list));
			curr->tag = n, curr->next = NULL;
			temp->next = curr; return;
		}
	}
	if(prev != NULL) {
		curr = (struct list *)malloc(sizeof(struct list));
		curr->tag = n;
		prev->next = curr, curr->next = temp;
	}
	else {
		curr = (struct list *)malloc(sizeof(struct list));
		curr->tag = n;
		HASH[m] = curr, curr->next = temp;
	}
	return;
}
void DelHash(int n) {
	int m = n%Mod;
	curr = HASH[m], prev = NULL;
	while(curr != NULL) {
		if(curr->tag < n) prev = curr, curr = curr->next;
		else if(curr->tag == n) {
			if(prev != NULL)	prev->next = curr->next;
			else HASH[m] = curr->next;
			free(curr);
			return;
		}
		else return;
	}
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
void PrintHash() {
	puts("===== s =====");
	int a;
	for(a = 0; a < Mod; a++) {
		printf("[%03d]:", a);
		curr = HASH[a];
		while(curr != NULL) {
			printf("%d -> ", curr->tag);
			curr = curr->next;
		}
		puts("NULL");
	}
	puts("===== e =====");
}
main() {
	int a, k, n, op;
	while(scanf("%d %d", &k, &Mod) == 2) {
		FreeAll();
		while(k--) {
			scanf("%d", &op);
			switch(op) {
				case 1:scanf("%d", &n);
						InsHash(n);break;
				case 2:scanf("%d", &n);
						DelHash(n);break;
				case 3:PrintHash();break;
			}
		}
	}
	return 0;
}
