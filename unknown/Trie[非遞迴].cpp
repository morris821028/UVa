#include<stdio.h>
#include<stdlib.h>
typedef struct TrieNode	{
	char c;
	struct TrieNode *kid, *peer;
}TrieNode;
typedef struct Trie	{
	struct TrieNode *root;
}Trie;
typedef struct Stack {
	struct Stack *prev;
	struct TrieNode *now, *curr;	
	int dv;
	char work;
}Stack;

void Trieinit(Trie*);
void InsTrie(Trie*, char s[]);
void TriePrint(TrieNode*, int);

void Trieinit(Trie *tree) {
	tree->root = (TrieNode*)malloc(sizeof(TrieNode));
	tree->root->c = ' ';
	tree->root->kid = tree->root->peer = NULL;
}
void TriePrint(TrieNode *now, int dv) {
	Stack *stack, *temp;
	stack = (Stack*)malloc(sizeof(Stack));
	stack->prev = NULL, stack->now = now, stack->dv = dv, stack->work = 0;
	int a;
	char flag = 0, flag2;
	while(stack != NULL) {
		if(stack->work == 0) {			
			if(flag == 1) {
				for(a = 0, flag = 0; a < stack->dv; a++)
					printf("   ");
			}
			stack->curr = stack->now->kid, stack->work = 1;
			printf("[%c]", stack->now->c);

		}			
		flag2 = 0;
		while(stack->curr != NULL) {
			temp = (Stack*)malloc(sizeof(Stack));
			temp->now = stack->curr, temp->prev = stack, temp->dv = stack->dv+1;
			temp->work = 0;
			stack->curr = stack->curr->peer;
			stack = temp, flag2 = 1;
			break;
		}
		if(flag2) continue;
		if(stack->now->kid == NULL)	flag = 1, puts("");
		temp = stack->prev, free(stack->now), free(stack), stack = temp;
	}
}
void InsTrie(Trie *tree, char s[]) {
	TrieNode *curr = tree->root, *prev = NULL, *temp, *p;
	int a;
	for(a = 0; s[a]; a++) {
		p = curr, curr = p->kid, prev = NULL;
		while(curr != NULL && curr->c < s[a]) {
			prev = curr, curr = curr->peer;
		}
		
		if(curr == NULL) {
			temp = (TrieNode*)malloc(sizeof(TrieNode));
			temp->c = s[a], temp->kid = temp->peer = NULL;
			if(prev == NULL)	p->kid = temp;
			else	prev->peer = temp;
			curr = temp;
		}
		else {
		    if(curr->c == s[a])    {continue;}
            temp = (TrieNode*)malloc(sizeof(TrieNode));
            temp->c = s[a], temp->kid = NULL;
            if(curr == p->kid)    p->kid = temp, temp->peer = curr;
            else    prev->peer = temp,    temp->peer = curr;
            curr = temp;
        }
    }
}

main() {
    int N;
    char s[1000001];
    while(scanf("%d", &N) == 1) {
        Trie Tree;
        Trieinit(&Tree);
        getchar();
        while(N--)
            gets(s), InsTrie(&Tree, s);
	    TriePrint(Tree.root, 0);
    }
    return 0;
}
