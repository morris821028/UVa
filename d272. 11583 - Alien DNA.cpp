#include<stdio.h>
main() {
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int i, j, Ans = 0, letter, tmp;
		char DNA[27];
		letter = (1<<27) - 1;
		for(i = 0; i < n; i++) {
			scanf("%s", DNA);
			for(j = 0, tmp = 0; DNA[j]; j++)
				tmp |= 1<<(DNA[j]-'a');
			if(tmp&letter) {
				letter &= tmp;
			} else {
				Ans++, letter = tmp;
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
