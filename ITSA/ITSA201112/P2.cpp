#include<stdio.h>
#include<string.h>
int map[14][14], max, n;
int set[150], limit;
int way[150], xy[150][2];
int longest[14][14][150], longL[14][14];
int connect(int x, int y, int L) {
	static	int i;
	for(i = 0; i < L; i++) {
		if(longest[x][y][way[i]] == 1)
			return 0;
	}
	return 1;
}
void DFS(int x, int y, int L) {
	if(max < L)		max = L;
	if(x < 0 || y < 0 || x >= n || y >= n)	return;
	if(set[map[x][y]] == 0 && longL[x][y] > 0 && connect(x, y, L) == 1) {
		if(L + longL[x][y] > max) {
			max = L + longL[x][y];		
			int i;
			if(longL[xy[0][0]][xy[0][1]] < max) {
				longL[xy[0][0]][xy[0][1]] = max;
				memset(longest[xy[0][0]][xy[0][1]], 0, sizeof(longest[xy[0][0]][xy[0][1]]));
				for(i = 0; i < L; i++) {
					longest[xy[0][0]][xy[0][1]][way[i]] = 1;
				}
			}
		}
		return;
	}
	if(max >= limit)	return;
	if(L + longL[x][y] <= limit && longL[x][y] != 0)	return;
	if(set[map[x][y]] == 0) {
		set[map[x][y]] = 1;
		way[L] = map[x][y];
		xy[L][0] = x, xy[L][1] = y;
		DFS(x-1, y, L+1);
		DFS(x, y+1, L+1);
		DFS(x+1, y, L+1);
		DFS(x, y-1, L+1);
		set[map[x][y]] = 0;
	}
}
int main() {
	int t, i, j;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		memset(set, 0, sizeof(set));
		memset(longL, 0, sizeof(longL));
		memset(longest, 0, sizeof(longest));
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				scanf("%d", &map[i][j]);
				if(set[map[i][j]] == 0)
					set[map[i][j]] = 1, limit++;
			}
		}
		memset(set, 0, sizeof(set));
		max = 0;
		int maxL = limit;
		for(limit = 1; limit <= maxL; limit++) {
			for(i = 0; i < n; i++)
				for(j = 0; j < n; j++)
					DFS(i, j, 0)/*, printf("(%d %d)", i, j)*/;
		//	printf("\n%d %d\n", limit, max);
		}
		printf("%d\n", max);
		if(t)	puts("");
	}
    return 0;
}/*
5
8
0 1 2 3 4 5 6 7
8 9 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63

12
0 1 2 3 4 5 6 7 8 9 10 11
12 13 14 15 16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31 32 33 34 35
36 37 38 39 40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55 56 57 58 59
60 61 62 63 64 65 66 67 68 69 70 71
72 73 74 75 76 77 78 79 80 81 82 83
84 85 86 87 88 89 90 91 92 93 94 95
96 97 98 99 100 101 102 103 104 105 106 107
108 109 110 111 112 113 114 115 116 117 118 119
120 121 122 123 124 125 126 127 128 129 129 129
132 133 134 135 136 137 138 139 140 129 142 143
*/
