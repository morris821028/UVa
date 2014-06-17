#include<stdio.h>
struct {
	int x, y;
}Stack[52][52];
main() {
	char s[3];
	while(scanf("%s", s) == 1 && s[0] != '#') {
		Stack[0][0].x = s[0], Stack[0][0].y = s[1];
		int Stacktop[52] = {}, i, j, k, pile = 51, Flag;
		for(i = 1; i < 52; i++) {
			scanf("%s", s);
			Stack[i][0].x = s[0], Stack[i][0].y = s[1];
		}
		while(1) {
			Flag = 0;
			for(i = 0; i <= pile; i++) {
				if(i >= 3 && (Stack[i][Stacktop[i]].x == Stack[i-3][Stacktop[i-3]].x ||
					Stack[i][Stacktop[i]].y == Stack[i-3][Stacktop[i-3]].y)) {
					Stack[i-3][++Stacktop[i-3]] = Stack[i][Stacktop[i]--];
					Flag = 1;
				}
				if(i >= 1 && (Stack[i][Stacktop[i]].x == Stack[i-1][Stacktop[i-1]].x ||
					Stack[i][Stacktop[i]].y == Stack[i-1][Stacktop[i-1]].y) && Flag == 0) {
					Stack[i-1][++Stacktop[i-1]] = Stack[i][Stacktop[i]--];
					Flag = 1;
				}
				if(Stacktop[i] == -1) {
					for(j = i+1; j <= pile; j++) {
						for(k = 0; k <= Stacktop[j]; k++)
							Stack[j-1][k] = Stack[j][k];
						Stacktop[j-1] = Stacktop[j];
					}
					pile--;
				}
				if(Flag)	break;
			}
			if(Flag == 0)
				break;
		}
		printf("%d pile%s remaining:", pile+1, pile == 0 ? "" : "s");
		for(i = 0; i <= pile; i++)
			printf(" %d", Stacktop[i]+1);
		puts("");
	}
	return 0;
}
