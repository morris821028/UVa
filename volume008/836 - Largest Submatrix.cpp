#include <stdio.h>
#include <string.h>

int main() {
	int T;
	int i, j, k;
	char clear[3], map[50][50];
	scanf("%d", &T);
	gets(clear);
	while(T--) {
		gets(clear);
		gets(map[0]);
		int row, column;
		row = column = strlen(map[0]);
		for(i = 1; i < row; i++)		
			gets(map[i]);
		int max = 0, length, width, tmp;
		for(i = 0; i < row; i++) {
			int sum[50] = {};
			for(j = i; j < row; j++) {
				for(k = 0; k < column; k++) {
					sum[k] += map[j][k]-'0';
					if(k == 0 || tmp != length*width)
						tmp = 0, length = 0;
					tmp += sum[k];
					length++, width = j-i+1;
					if(tmp == length*width)
						max = max > tmp ? max : tmp;
				}
			}
		}
		printf("%d\n", max);
		if(T)	puts("");
	}
    return 0;
}
