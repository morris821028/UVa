#include<stdio.h>
#include<string.h>
int time[100000] = {}, t = 0;
void Build() {
	int a1, a2, a3, a4, a5;
	for(a1 = 1; a1 <= 5; a1++)	
		for(a2 = 1; a2 <= 5; a2++) {
			if(a1 == a2) continue;
			for(a3 = 1; a3 <= 5; a3++)	{
				if(a1 == a3 || a2 == a3)
					continue;
				for(a4 = 1; a4 <= 5; a4++)	{
					if(a1 == a4 || a2 == a4 || a3 == a4)
						continue;
					for(a5 = 1; a5 <= 5; a5++)	{
						if(a1 == a5 || a2 == a5 || a3 == a5 || a4 == a5)
							continue;
						time[a1*10000 + a2*1000 + a3*100 + a4*10 + a5] = ++t;
					}
				}
			}
		}

}
main() {
	int T, a, b, n;
	char s[10];
	Build();
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		n = 0;
		for(a = 0; a < 9; a += 2) {
			n = n*10 + s[a] - '0';
		}
		printf("%d\n", time[n]);
	}
	return 0;
}
