#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
main() {
	int n, T, i, j, a, b;
	char map[301][301];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		memset(map, 0, sizeof(map));
		getchar();
		for(i = 0; i < n; i++)
			gets(map[i]);
		n = 100;
		int White = 0, Black = 0;
		for(i = 0; i < 300; i++)
			for(j = 0; j < 300; j++) {
				int tmp = 0;
				if(map[i][j] == '0') {
					if(j%2 == 0) {
						for(a = 0; a < n; a++) {
							for(b = -a; b <= a; b++) {
								if(i+a < 0 || i+a >= n ||
								j+b < 0 || j+b >= 2*n-1)
									break;
								if(map[i+a][j+b] != '0')
									break;
							}
							if(b != a+1)	break;
						}
						tmp = (a)*(2+(a-1)*2)/2;
						if(tmp > White)
							White = tmp;
					} else {
						for(a = 0; a < n; a++) {
							for(b = -a; b <= a; b++) {
								if(i-a < 0 || i-a >= n ||
									j+b < 0 || j+b >= 2*n-1)
									break;
								if(map[i-a][j+b] != '0')
									break;
							}
							if(b != a+1)	break;
						}
						tmp = (a)*(2+(a-1)*2)/2;
						if(tmp > White)
							White = tmp;
					}
				} else if(map[i][j] == '1') {
					if(j%2 == 0) {
						for(a = 0; a < n; a++) {
							for(b = -a; b <= a ; b++) {
								if(i+a < 0 || i+a >= n ||
								j+b < 0 || j+b >= 2*n-1)
									break;
								if(map[i+a][j+b] != '1')
									break;
							}
							if(b != a+1)	break;
						}
						tmp = (a)*(2+(a-1)*2)/2;
						if(tmp > Black)
							Black = tmp;
					} else {
						for(a = 0; a < n; a++) {
							for(b = -a; b <= a; b++) {
								if(i-a < 0 || i-a >= n ||
								j+b < 0 || j+b >= 2*n-1)
									break;
								if(map[i-a][j+b] != '1')
									break;
							}
							if(b != a+1)	break;
						}
						tmp = (a)*(2+(a-1)*2)/2;
						if(tmp > Black)
							Black = tmp;
					}
				}
			}
		if(Black == White)
			printf("No answer\n");
		else if(Black > White)
			printf("Black\n%d\n", Black);
		else
			printf("White\n%d\n", White);
		if(T)	puts("");
	}
	return 0;
}
/*
4
5
    1
   111
  11111
 1111111
111111111
*/
