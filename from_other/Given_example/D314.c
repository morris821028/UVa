#include <stdio.h>
#define RANGE 1000
#define BUCKET 10000

struct Node {
	int data;
	struct Node *next;
};

typedef struct Node Node;

int main() {
	int i, k, n, flag, t;
	int cnt[BUCKET];
	char command[5];
	Node *p, *s, *newNode;
	Node *bucket[BUCKET];
	
	for(i = 0; i < BUCKET; i++)
		cnt[i] = 0, bucket[i] = NULL;
	
	while(scanf("%s", command) == 1) {
		if(command[0] == 'G') {
			newNode = malloc(sizeof(Node));
			scanf("%d", &(newNode->data));
			newNode->next = NULL;
			
			k = (newNode->data)/RANGE;
			
			if(bucket[k] == NULL) {
				bucket[k] = newNode;
			} else {
				flag = 0;
				for(s = NULL, p = bucket[k]; p != NULL; s = p, p = p->next) {
					if(newNode->data > p->data) {
						flag = 1;
						break;
					}
				}
				
				if(flag == 1) {
					if(s == NULL) {
						newNode->next = bucket[k];
						bucket[k] = newNode;
					} else {
						s->next = newNode;
						newNode->next = p;
					}
				} else {
					s->next = newNode;
				}
			}
			cnt[k]++;
		} else if(command[0] == 'F') {
			scanf("%d", &n);
			
			t = 0;
			for(k = BUCKET-1; k >= 0; k--)
				if(t+cnt[k] >= n)
					break;
				else
					t += cnt[k];
			
			for(i = 1, p = bucket[k]; i+t < n; i++, p = p->next);
			printf("%d\n", p->data);
		} else
			break;
	}
	
	return 0;
}

