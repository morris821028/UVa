#include "findLength.h"

int findLength(int A[][256], int n, int r, int c, int dr, int dc) {
	int len = 0, cnt = 0;
	while (1) {
		if (r < 0 || c < 0 || r >= n || c >= n)
			return len;
		if (A[r][c])
			cnt++;
		else
			cnt = 0;
		if (cnt > len)
			len = cnt;
		r += dr, c += dc; 
	}
	return len;
}
