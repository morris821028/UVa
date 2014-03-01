#include<stdio.h>
#include<stdlib.h>
#define N 21
#define AnsL 1048576
struct node {
	int v, level;
	struct node *lc, *rc;
}*root, *curr, *temp, *Queue[N];
int Shift[N] = {1}, BaseShift[N], BaseSpace[N];
char Ans[AnsL];
void PrintTree(int MaxLevel) {
	int max_l = 0, shift, Qt = 0, last, At;
	int a, b, c, d, e;	
	Queue[0] = root, BaseShift[0] = Shift[MaxLevel];
	for(a = 0; a <= Qt; a++) {
		curr = Queue[a], BaseSpace[a] = 1;
		if(curr->lc != NULL)
			Queue[++Qt] = curr->lc, BaseShift[Qt] = BaseShift[a] - Shift[MaxLevel - curr->lc->level];
		if(curr->rc != NULL)
			Queue[++Qt] = curr->rc, BaseShift[Qt] = BaseShift[a] + Shift[MaxLevel - curr->rc->level];
	}
	curr = root;
	shift = BaseShift[0] + 1;
	while(curr->lc != NULL)
		max_l++, curr = curr->lc, shift -= Shift[MaxLevel - curr->level];
	
	last = shift, At = 0;
	for(; last <= BaseShift[0]; last++)	Ans[At++] = ' ';
	Ans[At++] = 'X', Ans[At] = '\0', puts(Ans);
	for(a = 0; a <= Qt; a++) {
		if(a != 0 && Queue[a]->level == Queue[a-1]->level) continue;
		for(b = Shift[MaxLevel - Queue[a]->level - 1]; b > 0; b--) {
			last = shift, At = 0;
			for(c = a; c <= Qt; c++) {
				curr = Queue[c];
				if(curr->lc != NULL || curr->rc != NULL)
					for(; last < BaseShift[c]; last++)	Ans[At++] = ' ';
				if(curr->lc != NULL) {
					Ans[At++] = b == 1 ? 'X': '/', last++;
				}
				else {
					if(last <= BaseShift[c])
						Ans[At++] = ' ', last++;
				}
				if(curr->rc != NULL)
					for(e = 1; e <= BaseSpace[c]; e++) {
						if(BaseShift[c] + e< last) continue;
						Ans[At++] = ' ', last++;
					} 
				if(curr->rc != NULL)	Ans[At++] = b == 1 ? 'X' : '\\';
				else	Ans[At++] = ' ';
				BaseShift[c]--, BaseSpace[c] += 2, last++;
				
				if(c < Qt && Queue[c]->level != Queue[c+1]->level)	break;
			}
			while(At > 0 && Ans[At-1] == ' ')	At--;
			Ans[At] = '\0',	puts(Ans);
		}
	}
	for(a = 0; a <= Qt; a++)
		free(Queue[a]);
}
main() {
	int n, m, a, MaxLevel;
	for(a = 1; a <= 20; Shift[a] = Shift[a-1]*2, a++);
	while(scanf("%d", &n) == 1) {
		scanf("%d", &m);
		temp = (struct node*)malloc(sizeof(struct node));
		temp->v = m, temp->lc = temp->rc = NULL, temp->level = 0;
		root = temp;
		for(a = 1, MaxLevel = 0; a < n; a++) {
			scanf("%d", &m);
			curr = root;
			while(1) {
				if(curr->v > m) {
					if(curr->lc == NULL) {
						temp = (struct node*)malloc(sizeof(struct node));
						temp->v = m, temp->lc = temp->rc = NULL, temp->level = curr->level+1;
						if(temp->level > MaxLevel) MaxLevel = temp->level;
						curr->lc = temp; break;
					}
					else
						curr = curr->lc;
				}
				else if(curr->v < m) {
					if(curr->rc == NULL) {
						temp = (struct node*)malloc(sizeof(struct node));
						temp->v = m, temp->lc = temp->rc = NULL, temp->level = curr->level+1;
						if(temp->level > MaxLevel) MaxLevel = temp->level;
						curr->rc = temp; break;
					}
					else
						curr = curr->rc;
				}
				else
					break;
			}
		}
		PrintTree(MaxLevel);
	}
	return 0;	
}
