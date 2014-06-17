#include<stdio.h>
#include<string.h>
main() {
	int n, a, b, ta, tb;
	char s1[5], s2[5];
	while(scanf("%d", &n) == 1) {
		int set[25] = {}, block[25][25] = {}, bt[25] = {};
		for(a = 0; a < n; a++)/*init*/
			set[a] = a, block[a][0] = a;
		while(scanf("%s", s1) == 1) {
			if(s1[0] == 'q') /*quit*/
				break;
			scanf("%d %s %d", &ta, s2, &tb);
			if(ta == tb || set[ta] == set[tb])	continue;
			if(s1[0] == 'm') {/*move*/
				if(s2[1] == 'n') {/*onto*/
					for(a = bt[set[ta]]; block[set[ta]][a] != ta; a--, bt[set[ta]]--) 
						block[block[set[ta]][a]][++bt[block[set[ta]][a]]] = block[set[ta]][a],
						set[block[set[ta]][a]] = block[set[ta]][a];
					for(a = bt[set[tb]]; block[set[tb]][a] != tb; a--, bt[set[tb]]--) 
						block[block[set[tb]][a]][++bt[block[set[tb]][a]]] = block[set[tb]][a],
						set[block[set[tb]][a]] = block[set[tb]][a];
					block[set[tb]][++bt[set[tb]]] = ta, bt[set[ta]]--, set[ta] = set[tb];
				}
				else {/*over*/
					for(a = bt[set[ta]]; block[set[ta]][a] != ta; a--, bt[set[ta]]--) 
						block[block[set[ta]][a]][++bt[block[set[ta]][a]]] = block[set[ta]][a],
						set[block[set[ta]][a]] = block[set[ta]][a];
					block[set[tb]][++bt[set[tb]]] = ta, bt[set[ta]]--, set[ta] = set[tb];
				}
			}
			else { /*pile*/
				if(s2[1] == 'n') {/*onto*/
					for(a = bt[set[tb]]; block[set[tb]][a] != tb; a--, bt[set[tb]]--) 
						block[block[set[tb]][a]][++bt[block[set[tb]][a]]] = block[set[tb]][a],
						set[block[set[tb]][a]] = block[set[tb]][a];
					for(a = bt[set[ta]]; block[set[ta]][a] != ta; a--) ;
					int in = a, tin = bt[set[ta]], sset = set[ta];
					for(a = in; a <= tin; a++, bt[sset]--)
						block[set[tb]][++bt[set[tb]]] = block[sset][a], set[block[sset][a]] = set[tb];
				}
				else {
					for(a = bt[set[ta]]; block[set[ta]][a] != ta; a--) ;
					int in = a, tin = bt[set[ta]], sset = set[ta];
					for(a = in; a <= tin; a++, bt[sset]--)
						block[set[tb]][++bt[set[tb]]] = block[sset][a], set[block[sset][a]] = set[tb];	
				}
			}
		}
		for(a = 0; a < n; a++) {
			printf("%d: ", a);
			for(b = 0; b <= bt[a]; b++)
				printf("%d ",block[a][b]);
			puts("");
		}
	}
	return 0;
}
