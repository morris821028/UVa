#include <bits/stdc++.h>
using namespace std;

enum DATA {VAR, VAL, UNKNOWN};
struct Inst;
typedef int (*FUNC) (Inst*);

struct Inst {
	FUNC call;
	DATA vt;
	string var;
	int val;
};

vector<Inst> insts;
int inst_idx, in_idx;
stack<int> stk;
unordered_map<string, int> var;
vector<int> in, out;
void init() {
	in.clear(), out.clear();
	var.clear();
	insts.clear();
	inst_idx = 1, in_idx = 0;
	while (!stk.empty())
		stk.pop();
}
int PUSH_F(Inst *inst) {
	if (inst->vt == DATA::VAL) {
		stk.push(inst->val);
	} else {
		auto x = var.find(inst->var);
		if (x == var.end())
			return 1;
		stk.push(x->second);
	}
	inst_idx++;
	return 0;
}
int POP_F(Inst *inst) {
	if (stk.size() == 0)
		return 1;
	var[inst->var] = stk.top();
	stk.pop();
	inst_idx++;
	return 0;
}
int DUP_F(Inst *inst) {
	if (stk.size() == 0)
		return 1;
	stk.push(stk.top());
	inst_idx++;
	return 0;
}
int ADD_F(Inst *inst) {
	if (stk.size() < 2)
		return 1;
	int va = stk.top(); stk.pop();
	int vb = stk.top(); stk.pop();
	stk.push(va + vb);
	inst_idx++;
	return 0;
}
int SUB_F(Inst *inst) {
	if (stk.size() < 2)
		return 1;
	int va = stk.top(); stk.pop();
	int vb = stk.top(); stk.pop();
	stk.push(va - vb);
	inst_idx++;
	return 0;
}
int MUL_F(Inst *inst) {
	if (stk.size() < 2)
		return 1;
	int va = stk.top(); stk.pop();
	int vb = stk.top(); stk.pop();
	stk.push(va * vb);
	inst_idx++;
	return 0;
}
int DIV_F(Inst *inst) {
	if (stk.size() < 2)
		return 1;
	int va = stk.top(); stk.pop();
	int vb = stk.top(); stk.pop();
	if (vb == 0)
		return 1;
	stk.push(va / vb);
	inst_idx++;
	return 0;
}
int READ_F(Inst *inst) {
	if (in_idx >= in.size())
		return 1;
	stk.push(in[in_idx]);
	inst_idx++, in_idx++;
	return 0;
}
int WRITE_F(Inst *inst) {
	if (stk.size() == 0)
		return 1;
	out.push_back(stk.top());
	stk.pop();
	inst_idx++;
	return 0;
}
int JUMP_F(Inst *inst) {
	if (inst->vt == DATA::VAL) {
		inst_idx = inst->val;
	} else {
		auto x = var.find(inst->var);
		if (x == var.end())
			return 1;
		inst_idx = x->second;
	}
	return 0;
}
int JUMPPOS_F(Inst *inst)  {
	if (stk.size() == 0)
		return 1;
	int v = stk.top(); stk.pop();
	if (v <= 0)
		inst_idx++;
	else
		return JUMP_F(inst);
	return 0;
}
int JUMPZERO_F(Inst *inst) {
	if (stk.size() == 0)
		return 1;
	int v = stk.top(); stk.pop();
	if (v != 0)
		inst_idx++;
	else
		return JUMP_F(inst);
	return 0;
}

DATA checkType(char *q) {
	if (q == NULL || q[0] == '\0')
		return DATA::UNKNOWN;
	if (q[0] == '-' || q[0] == '+')	q++;
	if (q[0] == '\0')	return DATA::UNKNOWN;
	for (; *q; q++) {
		if (!isdigit(*q))
			return DATA::VAR;
	}
	return DATA::VAL;
}

void dump() {
	printf("Instruction [%d]\n", inst_idx);
	stack<int> tmp = stk;
	printf("stack:");
	while (!tmp.empty()) {
		int u = tmp.top(); tmp.pop();
		printf(" %d", u);
	}
	puts("");
	printf("map: [");
	for (auto &x : var) {
		printf("{%s, %d} ", x.first.c_str(), x.second);
	}
	puts("]");
}

void exec_insts() {
	while (true) {
		if (inst_idx < 1 || inst_idx > insts.size())
			break;
		Inst *inst = &insts[inst_idx-1];
		int ret = inst->call(inst);
		if (ret) {
			puts("ABORTED");
			puts("#");
			return;
		}
	}
	for (auto x : out)
		printf("%d\n", x);
	puts("#");
}

int main() {
	char buf[1024];
	unordered_map<string, FUNC> fmap = {{"PUSH", PUSH_F}, {"POP", POP_F}, 
		{"DUP", DUP_F}, {"ADD", ADD_F}, {"SUB", SUB_F}, {"MUL", MUL_F},
		{"DIV", DIV_F}, {"READ", READ_F}, {"WRITE", WRITE_F}, {"JUMP", JUMP_F},
		{"JUMPPOS", JUMPPOS_F}, {"JUMPZERO", JUMPZERO_F}};
	while (fgets(buf, 1024, stdin)) {
		init();
		while (buf[0] != '#') {
			char *p = strtok(buf, " \n"), *q = NULL;
			Inst inst;
			for (int i = 0; p != NULL; i++) {
				if (i == 0)
					inst.call = fmap[p];
				else
					q = p;
				p = strtok(NULL, " \n");
			}
			if (q != NULL) {
				inst.vt = checkType(q);
				if (inst.vt == DATA::VAL)
					inst.val = stoi(q);
				else
					inst.var = q;
			}
			insts.push_back(inst);
			fgets(buf, 1024, stdin);
		}

		while (fgets(buf, 1024, stdin) && buf[0] != '#')
			in.push_back(stoi(buf));

		exec_insts();
	}
	return 0;
}
/*
READ
POP num
PUSH 2
POP x
PUSH num
PUSH 2
SUB
JUMPPOS 31
PUSH num
PUSH x
SUB
DUP
JUMPZERO 28
JUMPPOS 28
PUSH x
PUSH num
DIV
PUSH x
MUL
PUSH num
SUB
JUMPZERO 31
PUSH x
PUSH 1
ADD
POP x
JUMP 9
PUSH 1
WRITE
JUMP 33
PUSH 0
WRITE
#
7
#
PUSH undefined
WRITE
#
#
*/
