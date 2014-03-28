#include <stdio.h>
#include <stdlib.h>
struct Node {
	int v[512], v_size;
	int v_sum; // sigma(abs(v[i]))
	int v_pair; // this problem matched.
	int v_girl; // unmatch girl.
	Node *next;
	Node() {
		v_size = v_sum = v_pair = v_girl = 0;
		next = NULL;
	}
};
int P_SIZE = 250;
void freeList(Node *head) {
    Node *idx = head, *pre = NULL;
    while(idx != NULL) {
        pre = idx, idx = idx->next;
        delete pre;
    }
}
int calcList(Node *head) {
	int mpair = 0;
	int boy = 0;
	Node *idx = head, *pre = NULL;
    while(idx != NULL) {
    	mpair += idx->v_pair;
    	mpair += boy < idx->v_girl ? boy : idx->v_girl;
    	boy -= idx->v_girl;
    	if(boy < 0)	boy = 0;
    	boy += idx->v_sum - idx->v_pair*2 - idx->v_girl;
    	pre = idx, idx = idx->next;
    }
	return mpair;
}
void reCalculate(Node *p) {
	int sum = 0, mpair = 0, boy = 0, girl = 0;
	for(int i = 0; i < p->v_size; i++) {
		if(p->v[i] > 0)	{
			boy += p->v[i];
		} else {
			mpair += boy < -(p->v[i]) ? boy : -(p->v[i]);
			girl += boy + p->v[i] < 0 ? -(boy + p->v[i]) : 0;
			boy = boy + p->v[i] > 0 ? boy + p->v[i] : 0;
		}
		sum += abs(p->v[i]);
	}
	p->v_sum = sum, p->v_pair = mpair, p->v_girl = girl;
}
Node* insertNode(Node *head, int where, int val) {
	if(where == 0) {
		Node *p = new Node();
		p->v[0] = val, p->v_size = 1;
		p->next = head;
		reCalculate(p);
		return p;
	}
	int sum =  0;
    Node *idx = head, *pre = NULL;
    while(idx != NULL) {
    	sum += idx->v_sum;
    	pre = idx, idx = idx->next;
    	if(sum >= where)
    		break;
    }
    if(sum == where) {
    	Node *p = new Node();
    	p->next = pre->next, pre->next = p;
		p->v[0] = val, p->v_size = 1;
    	reCalculate(p);
    	return head;
    }
    sum -= pre->v_sum;
    for(int i = 0; i < pre->v_size; i++) {
    	if(sum + abs(pre->v[i]) >= where) {
    		Node *p = new Node();
    		int div = i+1;
    		int diff = sum + abs(pre->v[i]) - where;
    		p->next = pre->next, pre->next = p;
			p->v[p->v_size++] = val;
    		if(diff > 0) {
    			if(pre->v[i] > 0) {
    				p->v[p->v_size++] = diff; 
    				pre->v[i] -= diff;
				} else {
    				p->v[p->v_size++] = -diff;
    				pre->v[i] += diff;
    			}
    		}
			for(int j = div; j < pre->v_size; j++)
				p->v[p->v_size++] = pre->v[j];
			pre->v_size = div;
    		reCalculate(p);
    		reCalculate(pre);
    		break;
    	}
    	sum += abs(pre->v[i]);
    }
    return head;
}
void maintainList(Node *head) {
    Node *idx = head, *p;
    while(idx != NULL && idx->next != NULL) {
        if(idx->v_size + idx->next->v_size <= 2 * P_SIZE) { // merge
            p = idx->next;
            for(int i = idx->v_size, j = 0; j < p->v_size; i++, j++)
                idx->v[i] = p->v[j];
            idx->v_size += p->v_size;
            idx->next = p->next;
            delete p;
    		reCalculate(idx);
        }
        idx = idx->next;
    }
}
void printList(Node *head) {
    Node *idx = head;
    int i, j = 0;
    while(idx != NULL) {
        printf("%d [%d, %d]: ", ++j, idx->v_pair, idx->v_girl);
        for(i = 0; i < idx->v_size; i++)
            printf("%d ", idx->v[i]);
        puts("");
        idx = idx->next;
    }
    puts("====");
}
int main() {
	int testcase, cases = 0, N;
	scanf("%d", &testcase);
	while(testcase--) {
		printf("Case %d:\n", ++cases);
		scanf("%d", &N);
		Node *head = NULL;
		head = new Node();
		head->v[0] = 1, head->v_size = 1;
		head->v_sum = 1, head->v_pair = 0;
		for(int i = 0; i < N; i++) {
			int girl, where, cnt;
			scanf("%d %d %d", &girl, &where, &cnt);
			if(girl)	cnt = -cnt;
			head = insertNode(head, where, cnt);
			maintainList(head);
			//printList(head);
			printf("%d\n", calcList(head));
		}
		freeList(head);
	}
	return 0;
}
/*
2
3
1 1 4
0 3 3
0 0 2
1
1 0 1
*/
