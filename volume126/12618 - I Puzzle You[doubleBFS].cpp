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
	static int used[128] = {}, R[128], testcase = 0;
	char idx = 'A';
	testcase++;
	for (int i = 0; i < u.length(); i++) {
		if (used[u[i]] != testcase) {
			R[u[i]] = idx++, used[u[i]] = testcase;
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
	static int used[128] = {}, testcase = 0, cnt = 0;
	int ret = 0;
	for (int i = 0; i < 6; i++) {
		testcase++, cnt = 0;
		for (int j = 0; j < 9; j++) {
			if (used[u[face[i][j]]] != testcase) {
				used[u[face[i][j]]] = testcase;
				cnt++;
			}
		}
		ret = max(ret, cnt - 1);
	}
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

int bfs2(string A) {
	if (isCompleted(A.c_str()))
		return 0;
	queue<string> Q;
	string u, v;
	Bstep.clear();
	A = reduceCube(A); 
	Q.push(A), Bstep[A] = 0;
	int ret = 0x3f3f3f3f;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		int step = Bstep[u];
		if (Rstep.find(u) != Rstep.end())
			ret = min(ret, step + Rstep[u]);
		if (step >= 3 || step + hfunction(u) >= min(7, ret))
			continue;
		for (int i = 0; i < 9; i++) {
			v = reduceCube(rotateCube(u, i, 0));
			if (Bstep.find(v) == Bstep.end()) {
				Bstep[v] = step + 1;
				Q.push(v);
			}
			v = reduceCube(rotateCube(u, i, 1));
			if (Bstep.find(v) == Bstep.end()) {
				Bstep[v] = step + 1;
				Q.push(v);
			}
		}
	}
	return ret <= 7 ? ret : -1;
}
int main() {
	adjustInfo();
	bfs("WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOGGGYYYYYYYYY");
	int testcase, cases = 0;
	char A[64];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", A);
		int ret = bfs2(A);
		
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

4
WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOGGGYYYYYYYYY
WWWWWWRRRRRYBBBWOOGGGRRYBBBWOOGGGRRYBBBWOOGGGOOOYYYYYY
WWBWWBWWBRRRBBYOOOWGGBBYOOOWGGRRRRRRBBYOOOWGGYYGYYGYYG
WWWWWWWWWRRRBBBOOOGGGRRRBBBOOOGGGRRRBBBOOOYYYGGGYYYYYY
*/
