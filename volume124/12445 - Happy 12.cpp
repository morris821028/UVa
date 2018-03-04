#include <bits/stdc++.h> 
using namespace std;

struct State {
	uint64_t mask;
	char step;
	bool operator<(const State& x) const {
		return mask < x.mask;
	}
	bool operator==(const State& x) const {
		return mask == x.mask;
	}
	inline void set(int pos, uint64_t val) {
		mask |= val<<(pos<<2);
	}
	inline int get(int pos) const {
		return (mask>>(pos<<2))&15;
	}
	void print() {
		for (int i = 0; i < 12; i++)
			printf("%d ", get(i)+1);
		puts("");
	}
};
struct StateHash {
	size_t operator() (const State& k) const {
		return k.mask;
	}
};
static State rotateV;
void rotateLA(const State &u) {	// left-clockwise
	rotateV = u;
	rotateV.mask &= 0x0fffff000000LLU;
	rotateV.mask |= 0x0000000fffffLLU&(u.mask>>4);
//	v.set(0, u.get(1));
//	v.set(1, u.get(2));
//	v.set(2, u.get(3));
//	v.set(3, u.get(4));
//	v.set(4, u.get(5));
	rotateV.set(5, u.get(11));
	rotateV.set(11, u.get(0));
}
void rotateLB(const State &u) {	// left-counter-clockwise
	rotateV = u;
	rotateV.mask &= 0x0fffff000000LLU;
	rotateV.mask |= 0x000000fffff0LLU&(u.mask<<4);
	rotateV.set(0, u.get(11));
//	v.set(1, u.get(0));
//	v.set(2, u.get(1));
//	v.set(3, u.get(2));
//	v.set(4, u.get(3));
//	v.set(5, u.get(4));
	rotateV.set(11, u.get(5));
}
void rotateRA(const State &u) {	// right-clockwise
	rotateV = u;
	rotateV.mask &= 0x0000000fffffLLU;
	rotateV.mask |= 0x0ffffff00000LLU&(u.mask>>4);
//	v.set(5, u.get(6));
//	v.set(6, u.get(7));
//	v.set(7, u.get(8));
//	v.set(8, u.get(9));
//	v.set(9, u.get(10));
//	v.set(10, u.get(11));
	rotateV.set(11, u.get(5));
}
void rotateRB(const State &u) {	// right-counter-clockwise
	rotateV = u;
	rotateV.mask &= 0x0000000fffffLLU;
	rotateV.mask |= 0xffffff000000LLU&(u.mask<<4);
	rotateV.set(5, u.get(11));
//	v.set(6, u.get(5);
//	v.set(7, u.get(6));
//	v.set(8, u.get(7));
//	v.set(9, u.get(8));
//	v.set(10, u.get(9));
//	v.set(11, u.get(10));
}
void rotateWA(const State &u) {	// whole-clockwise
	rotateV.mask = 0x0fffffffffffLLU&u.mask>>4;
	rotateV.set(11, u.get(0));
//	v.v[0] = u.v[1];
//	v.v[1] = u.v[2];
//	v.v[2] = u.v[3];
//	v.v[3] = u.v[4];
//	v.v[4] = u.v[5];
//	v.v[5] = u.v[6];
//	v.v[6] = u.v[7];
//	v.v[7] = u.v[8];
//	v.v[8] = u.v[9];
//	v.v[9] = u.v[10];
//	v.v[10] = u.v[11];
//	v.v[11] = u.v[0];
}
void rotateWB(const State &u) {	// whole-counter-clockwise
	rotateV.mask = 0xfffffffffff0LLU&(u.mask<<4);
	rotateV.set(0, u.get(11));
//	v.v[0] = u.v[11];
//	v.v[1] = u.v[0];
//	v.v[2] = u.v[1];
//	v.v[3] = u.v[2];
//	v.v[4] = u.v[3];
//	v.v[5] = u.v[4];
//	v.v[6] = u.v[5];
//	v.v[7] = u.v[6];
//	v.v[8] = u.v[7];
//	v.v[9] = u.v[8];
//	v.v[10] = u.v[9];
//	v.v[11] = u.v[10];
}

static void (*func[])(const State&) = {rotateWA, rotateWB, rotateLA, rotateLB, rotateRA, rotateRB};
unordered_set<State, StateHash> R;
static State q[3215101+10];
void init() {
	State st;
	st.mask = 0, st.step = 0;
	for (int i = 0; i < 12; i++)
		st.mask |= (uint64_t) i<<((uint64_t) i<<2);
	R.insert(st); q[0] = st;
	for (int i = 0, qidx = 1; i < qidx; i++) {
		st = q[i];
		for (int i = 0; i < 6; i++) {
			func[i](st);
			State t = rotateV;
			t.step = st.step+1;
			bool inq = R.insert(t).second;
			if (inq == true && t.step < 10)
				q[qidx] = t, qidx++;
		}
	}
}
int bfs(int v[]) {
	State st;
	st.mask = 0, st.step = 1;
	for (int i = 0; i < 12; i++)
		st.mask |= (uint64_t) v[i]<<((uint64_t) i<<2);
	auto it = R.find(st);
	if (it != R.end())
		return it->step;
	unordered_set<State, StateHash> R2;
	R2.insert(st); q[0] = st;
	for (int i = 0, qidx = 1; i < qidx; i++) {
		st = q[i];
		for (int i = 0; i < 6; i++) {
			func[i](st);
			State t = rotateV;
			t.step = st.step+1;
			it = R.find(t);
			if (it != R.end())
				return it->step + st.step;
			bool inq = R2.insert(t).second;
			if (inq == true && t.step < 10)
				q[qidx] = t, qidx++;
		}
	}
	return -1;
}
int main() {
	init();exit(0);
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int v[12];
		for (int i = 0; i < 12; i++) {
			scanf("%d", &v[i]);
			v[i]--;
		}
		int ret = bfs(v);
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
1  2  3  4  5  6  7  8  9  10  11  12
2  3  4  5  11  12  6  7  8  9  10  1
*/
