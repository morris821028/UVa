#include<stdio.h>
#define oo 10000
int main() {
	int T;
	scanf("%d", &T);
	puts("Lumberjacks:");
	while(T--) {
		int i, st1 = oo, st2 = -oo, f1 = 1, f2 = 1, x;
		for(i = 0; i < 10; i++)	{
			scanf("%d", &x);
			if(x < st1)	st1 = x;
			else	f1 = 0;
			if(x > st2)	st2 = x;
			else	f2 = 0;
		}
		puts((f1 != 0 || f2 !=0) ? "Ordered" : "Unordered");
	}
    return 0;
}
