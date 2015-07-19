#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f, MAXQ = 524288;
class Unrolled {
public:
	int PILE, mask, shift;
	vector< vector<int> > nodes;
	vector<int> dirty;
	void alloc(int size) {
		nodes.clear(), dirty.clear();
		for (PILE = 1, shift = 0; PILE * PILE < size; PILE <<= 1, shift++);
		mask = PILE - 1;
		for (int l = 0, r; l < size; l = r+1) {
			r = min(l+PILE-1, size-1);
			nodes.push_back(vector<int>(r-l+1, INF));
			dirty.push_back(INF);
		}
	}
	int operator[](const int x) const {
		return nodes[x>>shift][x&mask];
	}
	int empty(int l, int r) {
		int bl = l>>shift, br = r>>shift;
		int ret = INF;
		if (bl == br) {
			for (int i = l; i <= r; i++)
				ret = min(ret, (*this)[i]);
			return ret;
		}
		for (int i = bl+1; i < br; i++)
			ret = min(ret, dirty[i]);
		for (int i = (bl+1) * PILE-1; i >= l; i--)
			ret = min(ret, (*this)[i]);
		for (int i = (br) * PILE; i <= r; i++)
			ret = min(ret, (*this)[i]);
		return ret;
	}
	void fill(int l, int r, int val) {
		int bl = l>>shift, br = r>>shift;
		for (int i = bl; i <= br; i++)
			dirty[i] = min(dirty[i], val);
		for (int i = l, bi; i <= r; i++)
			nodes[i>>shift][i&mask] = val;
	}
} mem;
char cmd[MAXQ][8];
int args[MAXQ][3];
int main() {
	int N;
	while (scanf("%d", &N) == 1) {
		map<int, int> R;
		for (int i = 0; i < N; i++) {
			scanf("%s", &cmd[i]);
			int a, b, c;
			if (cmd[i][0] == 'l')
				scanf("%d", &a), R[a] = 0;
			else if (cmd[i][0] == 'm')
				scanf("%d %d %d", &a, &b, &c), R[b] = R[c] = 0;
			else
				scanf("%d", &a), R[a] = 0;
			args[i][0] = a, args[i][1] = b, args[i][2] = c;
		}
		
		int size = 0;
		for (auto &x : R)
			x.second = size++;
		mem.alloc(size);
		for (int i = 0; i < N; i++) {
			int a, b, c, t;
			a = args[i][0], b = args[i][1], c = args[i][2];
			if (cmd[i][0] == 'l') {
				t = mem[R[a]];
				if (t == INF)
					printf("fail to load from %d\n", a);
				else
					printf("load from region %d\n", t);
			} else if (cmd[i][0] == 'm') {
				t = mem.empty(R[b], R[c]);
				if (t != INF)
					printf("fail to create region %d, overlap with region %d\n", a, t);
				else
					printf("region %d created\n", a), mem.fill(R[b], R[c], a);
			} else {
				t = mem[R[a]];
				if (t == INF)
					printf("fail to store to %d\n", a);
				else
					printf("store to region %d\n", t);
			}
		}
	}
	return 0;
}
/*
7
load 29
map 1 25 39
map 2 23 24
map 3 22 25
map 4 25 40
store 33   
store 22   
*/
