#include <stdio.h>
#include <string.h>
int main() {
	int T, N;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		int A[300][300];
		int i, j, k, l;
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				scanf("%d", &A[i][j]);
				A[i+N][j] = A[i][j+N] = A[i+N][j+N] = A[i][j];
			}
		}
		int length, width, max = 0, tmp;
		for(i = 0; i < N; i++)
			for(j = 0; j < N; j++)
				max = max > A[i][j] ? max : A[i][j];
		int tmpN = N << 1;
		int sum[300] = {}, tmpSum, tmplength, tmpMax;
		if(max != 0) {
			for(i = 0; i < N; i++) {
				memset(sum, 0, sizeof(sum));
				for(j = i; j < tmpN; j++) {
					if(j-i+1 > N)	break;
					length = 0, tmp = 0;
					for(k = 0; k < tmpN; k++) {
						sum[k] += A[j][k];
						length++;
						tmp += sum[k];
						if(length > N) {
							tmp -= sum[k-length+1];
							length--;
						}
						tmpSum = 0, tmplength = length, tmpMax = tmp;
						for(l = k-length+1; l <= k; l++) {
							tmpSum += sum[l];
							if(tmp-tmpSum >= tmpMax)	
								tmplength = k-l, tmpMax = tmp-tmpSum;
						}
						tmp = tmpMax, length = tmplength;
						if(length > 0) {
							if(tmp > max)
								max = tmp;
							if(k-length+1 >= N)	break;
						}
					}
					for(k++; k < tmpN; k++)	sum[k] += A[j][k];
				} 
			}
		}
		printf("%d\n", max);
	}
    return 0;
}
