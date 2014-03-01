#include <stdio.h>
#include <string.h>
int MinExp(const char *s, const int slen) {
	int i = 0, j = 1, k = 0, x, y, tmp;
	while(i < slen && j < slen && k < slen) {
		x = i + k;
		y = j + k;
		if(x >= slen)	x -= slen;
		if(y >= slen)	y -= slen;
		if(s[x] == s[y]) {
			k++;
		} else if(s[x] > s[y]) {
			i = j+1 > i+k+1 ? j+1 : i+k+1;
			k = 0;
			tmp = i, i = j, j = tmp;
		} else {
			j = i+1 > j+k+1 ? i+1 : j+k+1;
			k = 0;
		}
	}
	return i;
}
int main() {
	char A[10001], B[10001];
	while(scanf("%s %s", A, B) == 2) {
		int minExpA, minExpB;
		int i, j, k, slen = strlen(A), tmp;
		minExpA = MinExp(A, slen);
		minExpB = MinExp(B, slen);
		i = minExpA;
		j = minExpB;
		k = 0;
		while(k < slen) {
			if(A[i] != B[j])	break;
			i++, j++;
			if(i >= slen)	i = 0;
			if(j >= slen)	j = 0;
			k++;
		}
		if(k == slen)
			puts("same");
		else {
			for(i = 0, j = slen-1; i < j; i++, j--)
				tmp = B[i], B[i] = B[j], B[j] = tmp;
			minExpB = MinExp(B, strlen(B));
			i = minExpA;
			j = minExpB;
			k = 0;
			while(k < slen) {
				if(A[i] != B[j])	break;
				i++, j++;
				if(i >= slen)	i = 0;
				if(j >= slen)	j = 0;
				k++;
			}
			if(k == slen)
				puts("same");
			else
				puts("difference");
		}
	}
    return 0;
}
