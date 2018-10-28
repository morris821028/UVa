#include <bits/stdc++.h>
using namespace std;

struct Tile {
	int8_t first, second;
	Tile() {}
	Tile(int a, int b) {
		first = a, second = b;
	}
	bool operator<(const Tile &x) const {
		if (first != x.first)
			return first < x.first;
		return second < x.second;
	}
};
static Tile A[8];
int read() {
	for (int i = 0; i < 8; i++) {
		int a, b;
		if (scanf("%d %d", &a, &b) != 2)
			return 0;
		if (a > b)	swap(a, b);
		A[i] = Tile(a, b);
	}
	return 1;
}

int8_t row[4], col[4], dia[4];
int8_t cntr[4], cntc[4], cntd[4];
int8_t g[4][4];
inline int valid_x(int x, int y, int i, int t, int grid) {
	int a = A[i].first, b = A[i].second;
	if (t)	swap(a, b);
	if (row[x] < a || row[x+1] < b || col[y] < a+b)	return 0;
	if (x == y && dia[0] < a)		return 0;
	if (x+1 == y && dia[0] < b)		return 0;
	if (x == 3-y && dia[1] < a)		return 0;
	if (x+1 == 3-y && dia[1] < b)	return 0;
//	g[x][y] = a, g[x+1][y] = b;
	return 1;
}
inline void remove_x(int x, int y, int i, int t) {
	int a = A[i].first, b = A[i].second;
	if (t)	swap(a, b);
	row[x] -= a, row[x+1] -= b, col[y] -= a+b;
	cntr[x]++, cntr[x+1]++, cntc[y] += 2;
	if (x == y)		dia[0] -= a, cntd[0]++;
	if (x+1 == y)	dia[0] -= b, cntd[0]++;
	if (x == 3-y)	dia[1] -= a, cntd[1]++;
	if (x+1 == 3-y)	dia[1] -= b, cntd[1]++;
}
inline void resume_x(int x, int y, int i, int t) {
	int a = A[i].first, b = A[i].second;
	if (t)	swap(a, b);
	row[x] += a, row[x+1] += b, col[y] += a+b;
	cntr[x]--, cntr[x+1]--, cntc[y] -= 2;
	if (x == y)		dia[0] += a, cntd[0]--;
	if (x+1 == y)	dia[0] += b, cntd[0]--;
	if (x == 3-y)	dia[1] += a, cntd[1]--;
	if (x+1 == 3-y)	dia[1] += b, cntd[1]--;
}

inline int valid_y(int x, int y, int i, int t, int grid) {
	int a = A[i].first, b = A[i].second;
	if (t)	swap(a, b);
	if (row[x] < a+b || col[y] < a || col[y+1] < b)	return 0;
	if (x == y && dia[0] < a)		return 0;
	if (x == y+1 && dia[0] < b)		return 0;
	if (x == 3-y && dia[1] < a)		return 0;
	if (x == 3-(y+1) && dia[1] < b)	return 0;
	return 1;
}
inline void remove_y(int x, int y, int i, int t) {
	int a = A[i].first, b = A[i].second;
	if (t)	swap(a, b);
	row[x] -= a+b, col[y] -= a, col[y+1] -= b;
	cntr[x] +=2, cntc[y]++, cntc[y+1]++;
	if (x == y)		dia[0] -= a, cntd[0]++;
	if (x == y+1)	dia[0] -= b, cntd[0]++;
	if (x == 3-y)	dia[1] -= a, cntd[1]++;
	if (x == 3-(y+1))	dia[1] -= b, cntd[1]++;
//	g[x][y] = a, g[x][y+1] = b;
}
inline void resume_y(int x, int y, int i, int t) {
	int a = A[i].first, b = A[i].second;
	if (t)	swap(a, b);
	row[x] += a+b, col[y] += a, col[y+1] += b;
	cntr[x] -=2, cntc[y]--, cntc[y+1]--;
	if (x == y)		dia[0] += a, cntd[0]--;
	if (x == y+1)	dia[0] += b, cntd[0]--;
	if (x == 3-y)	dia[1] += a, cntd[1]--;
	if (x == 3-(y+1))	dia[1] += b, cntd[1]--;
}
void print(int grid) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int pos = i*4+j;
			if ((grid>>pos)&1)
				printf("%d", g[i][j]);
			else
				printf("-");
				
		}
		puts("");
	}
	printf("r %d %d %d %d\n", row[0], row[1], row[2], row[3]);
	printf("c %d %d %d %d\n", col[0], col[1], col[2], col[3]);
	printf("d %d %d\n", dia[0], dia[1]);
//	getchar();
}
int bingo_x(int x, int y) {
	if (cntr[x] == 4 && row[x])
		return 0;
	if (cntr[x+1] == 4 && row[x+1])
		return 0;
	if (cntc[y] == 4 && col[y])
		return 0;
	if (cntd[0] == 4 && dia[0])
		return 0;
	if (cntd[1] == 4 && dia[1])
		return 0;
	return 1;
}
int bingo_y(int x, int y) {
	if (cntr[x] == 4 && row[x])
		return 0;
	if (cntc[y] == 4 && col[y])
		return 0;
	if (cntc[y+1] == 4 && col[y+1])
		return 0;
	if (cntd[0] == 4 && dia[0])
		return 0;
	if (cntd[1] == 4 && dia[1])
		return 0;
	return 1;
}
int place(int x, int y, int used, int grid) {
	if (y == 4)
		y = 0, x++;
	if (x == 4 || used == (1<<8)-1)
		return 1;

	int pos = x*4+y;
	if ((grid>>(pos))&1)
		return place(x, y+1, used, grid);
	int type_x = pos && x+1 < 4 && ((grid>>(pos+4))&1) == 0;
	int type_y = y+1 < 4 && ((grid>>(pos+1))&1) == 0;
	
	if (!type_x && !type_y)
		return 0;

	int a = -1, b = -1;
	for (int i = 0; i < 8; i++) {
		if ((used>>i)&1)
			continue;
		if (A[i].first == a && A[i].second == b)
			continue;
		a = A[i].first, b = A[i].second;
				
		if (type_x) {
			if (valid_x(x, y, i, 0, grid)) {
				remove_x(x, y, i, 0);
				if (bingo_y(x, y) && place(x, y+1, used|(1<<i), grid|(1<<pos)|(1<<(pos+4))))
					return 1;
				resume_x(x, y, i, 0);
			}
			if (A[i].first != A[i].second && valid_x(x, y, i, 1, grid)) {
				remove_x(x, y, i, 1);
				if (bingo_y(x, y) && place(x, y+1, used|(1<<i), grid|(1<<pos)|(1<<(pos+4))))
					return 1;
				resume_x(x, y, i, 1);
			}
		}
		if (type_y) {
			if (valid_y(x, y, i, 0, grid)) {
				remove_y(x, y, i, 0);
				if (bingo_x(x, y) && place(x, y+1, used|(1<<i), grid|(1<<pos)|(1<<(pos+1))))
					return 1;
				resume_y(x, y, i, 0);
			}
			if (A[i].first != A[i].second && valid_y(x, y, i, 1, grid)) {
				remove_y(x, y, i, 1);
				if (bingo_x(x, y) && place(x, y+1, used|(1<<i), grid|(1<<pos)|(1<<(pos+1))))
					return 1;
				resume_y(x, y, i, 1);
			}
		}
	}
	return 0;
}
int solvable() {
	int sum = 0;
	for (int i = 0; i < 8; i++)
		sum += A[i].first + A[i].second;
	if (sum%4)
		return 0;
	sum /= 4;
	for (int i = 0; i < 4; i++) {
		row[i] = sum, col[i] = sum, dia[i] = sum;
		cntr[i] = cntc[i] = cntd[i] = 0;
	}
	sort(A, A+8);
	return place(0, 0, 0, 0);
}
int main() {
	while (read()) {
		int ret = solvable();
		puts(ret ? "Y" : "N");
	}
	return 0;
}
/*
1 4
5 2
4 4
2 3
5 4
5 3
1 3
3 3

6 5
2 4
2 2
5 4
5 5
5 1
2 3
3 6
*/
