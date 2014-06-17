#include<stdio.h>
#include<string.h>
main() {
	int p1, p2, p3, a, b, c;
	while(scanf("%d %d %d", &p1, &p2, &p3) == 3) {
		char s[30000], Ans[30000];
		int AIdx = 0, st, ed, flag;
		scanf("%s", s);
		for(a = 0; s[a]; a++) {
			if(s[a] == '-') { 
				if(s[a-1] >= s[a+1]) {
					Ans[AIdx++] = s[a], Ans[AIdx++] = s[a+1];
					a++;
				} else {
					if(s[a-1]+1 == s[a+1])
						{continue;}
					if(!(((s[a-1] >= '0' && s[a-1] <= '9') && (s[a+1] >= '0' && s[a+1] <= '9')) ||
					((s[a-1] >= 'a' && s[a-1] <= 'z') && (s[a+1] >= 'a' && s[a+1] <= 'z')) ||
					((s[a-1] >= 'A' && s[a-1] <= 'Z') && (s[a+1] >= 'A' && s[a+1] <= 'Z')))
					) {Ans[AIdx++] = s[a];continue;}
					if(p3 == 1)
						st = s[a-1]+1, ed = s[a+1], flag = 1;
					else
						st = s[a+1]-1, ed = s[a-1], flag = -1;
					for(b = st; ;) {
						if(p1 == 3) {
							for(c = 0; c < p2; c++)
								Ans[AIdx++] = '*';
						} else {
							if(b >= '0' && b <= '9') {
								for(c = 0; c < p2; c++)
									Ans[AIdx++] = b;
							}
							if(p1 == 1 && (b >= 'a' && b <= 'z' || b >= 'A' && b <= 'Z'))
								for(c = 0; c < p2; c++)
									Ans[AIdx++] = b >= 'a' ? b : (b - 'A' + 'a');
							if(p1 == 2 && (b >= 'a' && b <= 'z' || b >= 'A' && b <= 'Z'))
								for(c = 0; c < p2; c++)
									Ans[AIdx++] = b >= 'a' ? b - 'a' + 'A' : b;
						} 
						b += flag;
						if(p3 == 1 && b >= ed) break;
						if(p3 == 2 && b <= ed) break;
					}
				}
			} 
			else {
				Ans[AIdx++] = s[a];
			}
		}
		Ans[AIdx]  = '\0';
		puts(Ans);
	}
	return 0;
}
