#include <stdio.h> 
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
int rotateInfo[9][12] = {
	{1, 4, 7, 13, 25, 37, 46, 49, 52, 45, 33, 21}, // margin rotate begin
	{3, 6, 9, 15, 27, 39, 48, 51, 54, 43, 31, 19},
	{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
	{34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
	{1, 2, 3, 18, 30, 42, 54, 53, 52, 34, 22, 10},
	{7, 8, 9, 16, 28, 40, 48, 47, 46, 36, 24, 12},
	{2, 5, 8, 14, 26, 38, 47, 50, 53, 44, 32, 20}, // center rotate begin
	{4, 5, 6, 17, 29, 41, 51, 50, 49, 35, 23, 11},
	{22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33}
};
int rotateFace[6][9] = { // not center rotate
	{10, 11, 12, 22, 23, 24, 34, 35, 36},
	{18, 17, 16, 30, 29, 28, 42, 41, 40},
	{1, 4, 7, 2, 5, 8, 3, 6, 9},
	{52, 49, 46, 53, 50, 47, 54, 51, 48},
	{21, 20, 19, 33, 32, 31, 45, 44, 43},
	{13, 14, 15, 25, 26, 27, 37, 38, 39}
};
int rotateOrder1[9] = {2, 5, 8, 1, 4, 7, 0, 3, 6};
int rotateOrder2[9] = {6, 3, 0, 7, 4, 1, 8, 5, 2};

int face[6][9] = {
	{1, 2, 3, 4, 5, 6, 7, 8, 9},
	{10, 11, 12, 22, 23, 24, 34, 35, 36},
	{13, 14, 15, 25, 26, 27, 37, 38, 39},
	{16, 17, 18, 28, 29, 30, 40, 41, 42},
	{19, 20, 21, 31, 32, 33, 43, 44, 45},
	{46, 47, 48, 49, 50, 51, 52, 53, 54}
};

map<string, int> Rstep, Bstep;

void adjustInfo() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 12; j++)
			rotateInfo[i][j]--;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 9; j++)
			face[i][j]--;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 9; j++)
			rotateFace[i][j]--;
}
int isCompleted(const char A[]) {
	for (int i = 0; i < 6; i++) {
		int ok = 1;
		for (int j = 0; j < 9; j++)
			ok &= A[face[i][j]] == A[face[i][0]];
		if (!ok)	return ok;
	}
	return 1;
}
string reduceCube(string u) {
	map<char, char> R;
	char idx = 'A';
	for (int i = 0; i < u.length(); i++) {
		if (R.find(u[i]) == R.end()) {
			R[u[i]] = idx++;
		}
		u[i] = R[u[i]];
	}
	return u;
}
string rotateCube(string u, int kind, int dir) {
	static int a, b, c;
	static char tmp[9];
	if (dir == 0) {
		char v[3] = {u[rotateInfo[kind][0]], u[rotateInfo[kind][1]], u[rotateInfo[kind][2]]};
		for (int i = 0; i < 3; i++) {
			a = i * 3, b = i * 3 + 1, c = i * 3 + 2;
			u[rotateInfo[kind][a]] = u[rotateInfo[kind][a + 3]];
			u[rotateInfo[kind][b]] = u[rotateInfo[kind][b + 3]];
			u[rotateInfo[kind][c]] = u[rotateInfo[kind][c + 3]];
		}
		a = 3 * 3, b = 3 * 3 + 1, c = 3 * 3 + 2;
		u[rotateInfo[kind][a]] = v[0];
		u[rotateInfo[kind][b]] = v[1];
		u[rotateInfo[kind][c]] = v[2];
		if (kind < 6) {
			for (int i = 0; i < 9; i++)
				tmp[i] = u[rotateFace[kind][i]];
			for (int i = 0; i < 9; i++)
				u[rotateFace[kind][i]] = tmp[rotateOrder1[i]];
		}
	} else {
		char v[3] = {u[rotateInfo[kind][9]], u[rotateInfo[kind][10]], u[rotateInfo[kind][11]]};
		for (int i = 3; i > 0; i--) {
			a = i * 3, b = i * 3 + 1, c = i * 3 + 2;
			u[rotateInfo[kind][a]] = u[rotateInfo[kind][a - 3]];
			u[rotateInfo[kind][b]] = u[rotateInfo[kind][b - 3]];
			u[rotateInfo[kind][c]] = u[rotateInfo[kind][c - 3]];
		}
		a = 0, b = 1, c = 2;
		u[rotateInfo[kind][a]] = v[0];
		u[rotateInfo[kind][b]] = v[1];
		u[rotateInfo[kind][c]] = v[2];		
		if (kind < 6) {
			for (int i = 0; i < 9; i++)
				tmp[i] = u[rotateFace[kind][i]];
			for (int i = 0; i < 9; i++)
				u[rotateFace[kind][i]] = tmp[rotateOrder2[i]];
		}
	}
	return u;
}

int hfunction(string u) {
	int ret = 0;
	for (int i = 0; i < 6; i++) {
		set<char> s;
		for (int j = 0; j < 9; j++)
			s.insert(u[face[i][j]]);
		ret = max(ret, (int)s.size() - 1);
	}
//	if (Rstep.find(reduceCube(u)) != Rstep.end())
//		ret = Rstep[reduceCube(u)];
	return ret;
}
void bfs(string A) {
	queue<string> Q;
	string u, v;
	Rstep.clear();
	A = reduceCube(A); 
	Q.push(A), Rstep[A] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		int step = Rstep[u];
		if (step >= 4)	continue;
		for (int i = 0; i < 9; i++) {
			v = reduceCube(rotateCube(u, i, 0));
			if (Rstep.find(v) == Rstep.end()) {
				Rstep[v] = step + 1;
				Q.push(v);
			}
			v = reduceCube(rotateCube(u, i, 1));
			if (Rstep.find(v) == Rstep.end()) {
				Rstep[v] = step + 1;
				Q.push(v);
			}
		}
	}
//	printf("4 steps state %d\n", Rstep.size());
}

int solved = -1, ida_dep;
int IDA(int dep, int hv, int prekind, int predir, string u) {
	if (hv == 0) {
		solved = dep;
		return dep;
	}
	if (dep + hv > ida_dep)	return dep + hv;
	
	int ret = 0x3f3f3f3f, shv, tmp;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 2; j++) {
			if (i == prekind && j == predir)
				continue;
			string v = rotateCube(u, i, j);
			shv = hfunction(v);
			tmp = IDA(dep + 1, shv, i, j, v);
			if (solved)	return solved;
			ret = min(ret, tmp);
		}
	}
	return ret;
}
int main() {
	adjustInfo();
	bfs("WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOGGGYYYYYYYYY");
	int testcase, cases = 0;
	char A[64];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", A);
//		int ret = bfs(A);
		
		int initH = hfunction(string(A)), ret;
		solved = 0;
		ida_dep = initH;
		if (initH == 0) {
			ret = 0;
		} else {
			while (solved == 0 && ida_dep < 7) {
//				printf("%d\n", ida_dep);
				ida_dep = IDA(0, initH, -1, -1, string(A));
			}
			ret = solved == 0 ? -1 : solved;
		}
		printf("Case %d: ", ++cases);
		if (ret == -1)
			puts("Impossible");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
      W W W                               1  2  3
      W W W                               4  5  6
      W W W                               7  8  9
R R R B B B O O O G G G         10 11 12 13 14 15 16 17 18 19 20 21
R R R B B B O O O G G G         22 23 24 25 26 27 28 29 30 31 32 33
R R R B B B O O O G G G         34 35 36 37 38 39 40 41 42 43 44 45
      Y Y Y                              46 47 48
      Y Y Y                              49 50 51
      Y Y Y                              52 53 54
      
999
WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOGGGYYYYYYYYY 
WWWWWWRRRRRYBBBWOOGGGRRYBBBWOOGGGRRYBBBWOOGGGOOOYYYYYY

4
WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOGGGYYYYYYYYY
WWWWWWRRRRRYBBBWOOGGGRRYBBBWOOGGGRRYBBBWOOGGGOOOYYYYYY
WWBWWBWWBRRRBBYOOOWGGBBYOOOWGGRRRRRRBBYOOOWGGYYGYYGYYG
WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOYYYGGGYYYYYY
*/
