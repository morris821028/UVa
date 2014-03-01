#include<stdio.h>
#include<string.h>
struct record {
	char l[13], r[13], st[4];
}D[3];
main() {
	int t, a, b, c, suml, sumr;
	scanf("%d", &t);
	while(t--) {
		for(a = 0; a < 3; a++)
			scanf("%s %s %s", &D[a].l, &D[a].r, &D[a].st);
		/*light*/
		for(a = 0; a < 12; a++) {
			for(b = 0; b < 3; b++) {
				suml = 0, sumr = 0;
				for(c = 0; D[b].l[c]; c++)
					suml += (D[b].l[c] - 'A' != a);
				for(c = 0; D[b].r[c]; c++)
					sumr += (D[b].r[c] - 'A' != a);
				if(suml == sumr && D[b].st[0] == 'e') continue;
				if(suml < sumr && D[b].st[0] == 'd') continue;
				if(suml > sumr && D[b].st[0] == 'u') continue;
				break;
			}
			if(b == 3)	break;
		}
		if(a != 12)
			printf("%c is the counterfeit coin and it is light.\n", a + 'A');
		/*heavy*/
		for(a = 0; a < 12; a++) {
			for(b = 0; b < 3; b++) {
				suml = 0, sumr = 0;
				for(c = 0; D[b].l[c]; c++)
					suml += (D[b].l[c] - 'A' == a);
				for(c = 0; D[b].r[c]; c++)
					sumr += (D[b].r[c] - 'A' == a);
				if(suml == sumr && D[b].st[0] == 'e') continue;
				if(suml < sumr && D[b].st[0] == 'd') continue;
				if(suml > sumr && D[b].st[0] == 'u') continue;
				break;
			}
			if(b == 3)	break;
		}
		if(a != 12)
			printf("%c is the counterfeit coin and it is heavy.\n", a + 'A');
	}
	return 0;
}
