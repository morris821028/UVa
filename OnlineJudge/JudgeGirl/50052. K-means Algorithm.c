#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int dist(char *s, char *t) {
	int sum = 0;
	while (*s)
		sum += abs(*s - *t), s++, t++;
	return sum;
}
int dist_int(int *s, char *t) {
	int sum = 0;
	while (*s)
		sum += abs(*s - *t), s++, t++;
	return sum;
}
void sum_dist(int *sum, char *s) {
	while (*s)
		*sum += *s, s++, sum++;
}
void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y, *y = tmp;
}
int cmp_int(const void *x, const void *y) {
	return *(int *) x - *(int *) y;
}
int cmp_str(const void *x, const void *y) {
	return strcmp(*(char **) x, *(char **) y);
}
void three_mean(int N, int L, char *dict[], char *ret[]) {
	char *belong[64] = {};
	for (int i = 0; i < N; i++) {
		int mn = INT_MAX;
		for (int j = 0; j < 3; j++) {
			int d = dist(dict[i], ret[j]);
			if (d < mn)
				mn = d, belong[i] = ret[j];
		}
	}
	
	int tmp_ret[3];
	for (int i = 0; i < 3; i++) {
		int sum[16] = {}, cnt = 0;
		for (int j = 0; j < N; j++) {
			if (belong[j] == ret[i])
				sum_dist(sum, dict[j]), cnt++;
		}
		for (int j = 0; j < L; j++)
			sum[j] /= cnt;
		int mn = INT_MAX, mnIdx = -1;
		for (int j = 0; j < N; j++) {
			if (belong[j] == ret[i]) {
				int d = dist_int(sum, dict[j]);
				if (d < mn)
					mn = d, mnIdx = j;
			}
		}
		tmp_ret[i] = mnIdx;
	}
	qsort(tmp_ret, 3, sizeof(int), cmp_int);
	for (int i = 0; i < 3; i++)
		ret[i] = dict[tmp_ret[i]];
}
int main() {
	int N, L, R;
	while (scanf("%d %d %d", &N, &L, &R) == 3) {
		char buff[2048];
		char *bptr = buff, *dict[64];
		for (int i = 0; i < N; i++) {
			scanf("%s", bptr);
			dict[i] = bptr;
			bptr += L+1;
		}
		
		char *ret[3] = {dict[0], dict[1], dict[2]};
		qsort(ret, 3, sizeof(char*), cmp_str);
		qsort(dict, N, sizeof(char*), cmp_str);
		
		for (int it = 0; it < R; it++)
			three_mean(N, L, dict, ret);
		for (int i = 0; i < 3; i++)
			puts(ret[i]);
	}
	return 0;
}

