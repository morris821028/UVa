// permutation group, math
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
void rotateCube(int u[], int kind, int dir) {
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
}
int main() {
	adjustInfo();
	char s[1024];
	int A[54];
	while (scanf("%s", s) == 1) {
		for (int i = 0; i < 54; i++)	
			A[i] = i;
		for (int i = 0; s[i]; i++) {
			if (s[i] == 'F')		rotateCube(A, 5, 1);
			else if (s[i] == 'f')	rotateCube(A, 5, 0);
			else if (s[i] == 'B')	rotateCube(A, 4, 0);
			else if (s[i] == 'b')	rotateCube(A, 4, 1);
			else if (s[i] == 'U')	rotateCube(A, 2, 0);
			else if (s[i] == 'u')	rotateCube(A, 2, 1);
			else if (s[i] == 'D')	rotateCube(A, 3, 1);
			else if (s[i] == 'd')	rotateCube(A, 3, 0);
			else if (s[i] == 'L')	rotateCube(A, 0, 1);
			else if (s[i] == 'l')	rotateCube(A, 0, 0);
			else if (s[i] == 'R')	rotateCube(A, 1, 0);
			else if (s[i] == 'r')	rotateCube(A, 1, 1);
		}
		
		int used[54] = {};
		int lcm = 1;
		for (int i = 0; i < 54; i++) {
			if (!used[i]) {
				int cnt = 0;
				for (int j = i; !used[j]; j = A[j], cnt++)
					used[j] = 1;
				lcm = cnt / __gcd(lcm, cnt) * lcm;
			}
		}
		printf("%d\n", lcm);
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
*/
