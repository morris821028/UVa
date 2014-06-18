#include<stdio.h>
#include<stdlib.h>
typedef struct TrieNode	{
	char c;
	struct TrieNode *kid, *peer;
}TrieNode;
typedef struct Trie	{
	struct TrieNode *root;
}Trie;

void Trieinit(Trie*);
void TrieFree(TrieNode*);
void InsTrie(Trie*, char s[]);
void TriePrint(TrieNode*, int);

void Trieinit(Trie *tree) {
	tree->root = (TrieNode*)malloc(sizeof(TrieNode));
	tree->root->c = ' ';
	tree->root->kid = tree->root->peer = NULL;
}
void TrieFree(TrieNode *now) {
	if(now == NULL)	return;
	TrieNode *curr = now->kid, *prev;
	while(curr != NULL) {
		prev = curr, curr = curr->peer;
		TrieFree(prev);
	}
	free(now);
}
int flag, Atop = 0;
char Ans[3000005];
void TriePrint(TrieNode *now, int dv) {
	if(now == NULL)	return;
	TrieNode *curr = now->kid;
	if(flag == 1) {
		int a;
		for(a = 0, flag = 0; a < dv; a++)
			Ans[Atop++] = ' ', Ans[Atop++] = ' ', Ans[Atop++] = ' ';
	}
	Ans[Atop++] = '[', Ans[Atop++] = now->c, Ans[Atop++] = ']';
	while(curr != NULL) {
		TriePrint(curr, dv+1);
		curr = curr->peer;
	}
	if(now->kid == NULL)	Ans[Atop] = '\0', puts(Ans), flag = 1, Atop = 0;
}
void InsTrie(Trie *tree, char s[]) {
	TrieNode *curr = tree->root, *prev = NULL, *temp, *p;
	int a;
	for(a = 0; s[a]; a++) {
		p = curr, curr = p->kid, prev = NULL;
		while(curr != NULL && curr->c < s[a])
			prev = curr, curr = curr->peer;
		
		if(curr == NULL) {
			temp = (TrieNode*)malloc(sizeof(TrieNode));
			temp->c = s[a], temp->kid = temp->peer = NULL;
			if(prev == NULL)	p->kid = temp;
			else	prev->peer = temp;
			curr = temp;
		}
		else {
			if(curr->c == s[a])	continue;
			temp = (TrieNode*)malloc(sizeof(TrieNode));
			temp->c = s[a], temp->kid = NULL;
			if(curr == p->kid)	p->kid = temp, temp->peer = curr;
			else	prev->peer = temp,	temp->peer = curr;
			curr = temp;
		}
	}
}
char s[1000001];
main() {
	/*freopen("in1.txt", "rt", stdin);   
	freopen("out1.txt", "w+t", stdout);*/
	int N;
	
	while(scanf("%d", &N) == 1) {
		Trie Tree;
		Trieinit(&Tree);
		getchar();
		while(N--)
			gets(s), InsTrie(&Tree, s);
		flag = 0, TriePrint(Tree.root, 0);
		TrieFree(Tree.root);
	}
	return 0;
}
