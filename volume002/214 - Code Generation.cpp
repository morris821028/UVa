#include <bits/stdc++.h>
using namespace std;

struct Node {
	int memIdx;
	int op, dat, sz, vz;
	Node *l, *r;
};
Node nodes[65536];
int bufIdx = 0;
int regused[65536] = {};
Node* newNode() {
	assert(bufIdx < 65536);
	Node *p = &nodes[bufIdx++];
	p->l = p->r = NULL, p->memIdx = -1, p->dat = -1;
	return p;
}
int findReg() {
	for (int i = 0; i < 32767; i++) {
		if (regused[i] == 0)
			return i;
	}
	return -1;
}
int dfs3(Node *u) {
	if (u == NULL)		return 0;
	u->vz = dfs3(u->l) + dfs3(u->r) + 1;
	return u->vz;
}
int dfs1(Node *u) {
	if (u == NULL)		return 0;
	u->sz = dfs1(u->l) + dfs1(u->r) + (u->op != '@');
	return u->sz;
}
char toASM(char c) {
	switch(c) {
		case '*': return 'M';
		case '+': return 'A';
		case '-': return 'S';
		case '/': return 'D';
	}
	assert(false);
}
struct Inst {
	string op;
	int val, mem;
	Inst(string op, int a=-1, int b=-1): op(op) {
		val = mem = -1;
		if (a == 0)	val = b;
		if (a == 1) mem = b;
	}
};
vector<Inst> solution;
void dfs2(Node *u, int sflag) {
	if (u == NULL)
		return ;
	if (u->op == '+' || u->op == '*') {
		if (u->l->vz == 1 && u->r->vz == 1) {
			solution.push_back(Inst("L", 0, u->l->dat));
			solution.push_back(Inst(u->op == '+' ? "A" : "M", 0, u->r->dat));
		} else {
			dfs2(u->l, u->r->vz > 1);
			if (u->r->vz > 1) {
				u->l->memIdx = findReg();
				regused[u->l->memIdx] = 1;
				solution.push_back(Inst("ST", 1, u->l->memIdx));
				dfs2(u->r, 0);
				if (u->l->memIdx == -1)
					solution.push_back(Inst(u->op == '+' ? "A" : "M", 0, u->l->dat));
				else
					solution.push_back(Inst(u->op == '+' ? "A" : "M", 1, u->l->memIdx)), regused[u->l->memIdx] = 0;
			} else {
				if (u->r->memIdx == -1)
					solution.push_back(Inst(u->op == '+' ? "A" : "M", 0, u->r->dat));
				else
					solution.push_back(Inst(u->op == '+' ? "A" : "M", 1, u->r->memIdx)), regused[u->r->memIdx] = 0;
			}
		}
	} else if (u->op == '-') {
		if (u->l->vz == 1 && u->r->vz == 1) {
			solution.push_back(Inst("L", 0, u->l->dat));
			solution.push_back(Inst("S", 0, u->r->dat));
		} else {
			if (u->r->vz > 1 || u->l->vz > 1) {
				dfs2(u->l, u->r->sz > 1);
				u->l->memIdx = findReg();
				regused[u->l->memIdx] = 1;
				solution.push_back(Inst("ST", 1, u->l->memIdx));
			}
			if (u->r->vz > 1) {
				dfs2(u->r, 0);
				solution.push_back(Inst("N"));
				if (u->l->memIdx == -1)
					solution.push_back(Inst("A", 0, u->l->dat));
				else
					solution.push_back(Inst("A", 1, u->l->memIdx)), regused[u->l->memIdx] = 0;
			} else {
				if (u->r->vz > 1 || u->l->vz > 1)
					regused[solution.back().mem] = 0, solution.pop_back();
				solution.push_back(Inst("S", 0, u->r->dat));
			}
		}
	} else if (u->op == '/') {
		if (u->l->vz == 1 && u->r->vz == 1) {
			solution.push_back(Inst("L", 0, u->l->dat));
			solution.push_back(Inst("D", 0, u->r->dat));
		} else {
			if (u->l->vz > 1 || u->r->vz > 1) {
				dfs2(u->l, u->r->vz > 1);
				if (u->r->vz > 1) {
					u->l->memIdx = findReg();
					regused[u->l->memIdx] = 1;
					solution.push_back(Inst("ST", 1, u->l->memIdx));
				}
			}
			if (u->r->vz == 1) {
				if (u->r->memIdx == -1)
					solution.push_back(Inst("D", 0, u->r->dat));
				else
					solution.push_back(Inst("D", 1, u->r->memIdx)), regused[u->r->memIdx] = 0;
			} else {
				dfs2(u->r, 1);
				u->r->memIdx = findReg();
				regused[u->r->memIdx] = 1;
				solution.push_back(Inst("ST", 1, u->r->memIdx));
				if (u->l->vz > 1 || u->r->vz > 1) {
					solution.push_back(Inst("L", 1, u->l->memIdx)), regused[u->l->memIdx] = 0;
				} else {
					if (u->l->memIdx == -1)
						solution.push_back(Inst("L", 0, u->r->dat));
					else
						solution.push_back(Inst("L", 1, u->r->memIdx)), regused[u->l->memIdx] = 0;
				}
				if (u->r->memIdx == -1)
					solution.push_back(Inst("D", 0, u->r->dat));
				else
					solution.push_back(Inst("D", 1, u->r->memIdx)), regused[u->r->memIdx] = 0;
			}
		}
	} else if (u->op == '@') {
		dfs2(u->l, sflag);
		solution.push_back(Inst("N"));
	} else {
		solution.push_back(Inst("L", 0, u->dat));
	}
}
int main() {
	char s[65536];
	int testcase = 0;
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		stack<Node*> stk;
		bufIdx = 0;
		for (int i = 0; i < n; i++) {
			if (isalpha(s[i])) {
				Node *u = newNode();
				u->op = 0, u->dat = s[i];
				stk.push(u);
			} else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
				Node *u = newNode();
				u->op = s[i];
				u->r = stk.top(), stk.pop();
				u->l = stk.top(), stk.pop();
				stk.push(u);
			} else {
				Node *u = newNode();
				u->op = s[i];
				u->l = stk.top(), stk.pop();
				stk.push(u);
			}
		}
		Node *root = stk.top();
		dfs1(root);
		dfs3(root);
		
		solution.clear();
		dfs2(root, 0);
		if (testcase++)
			puts("");
		for (int i = 0; i < solution.size(); i++) {
			Inst inst = solution[i];
			printf("%s", inst.op.c_str());
			if (inst.val != -1)
				printf(" %c\n", inst.val);
			else if (inst.mem != -1)
				printf(" $%d\n", inst.mem);
			else
				printf("\n");
		}
	}
	return 0;
}
/*
BAC-WA*@+-
D@@
AB+
CD-
EF*
DC/
AB+CD+EF++GH+++
AB+CD+-
A@B@+C@D@++
DE*F-
AB@/
A@B@/
AA+
AAA++
AAAA+++
ABABA++++
*/
