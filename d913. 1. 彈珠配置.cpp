#include<stdio.h>
#include<stdlib.h>
int a, b, c, Map[6][7];
int Used[7]={0}, Find=0, Way[7];
void DFS(int Now) {
    int a;
    if(Find == 1) return;
    if(Now == 6) {
    	int b, t;
        for(a = 0; a < 6; a++) {
            t = 0;
            for(b = 0; b < 6; b++)
            	if(Way[b] == Map[a][b]) t++;
            if(t!=Map[a][6])	break;
        }
        if(a == 6) {
            for(a = 0; a < 6; a++)
                printf("%d ", Way[a]);
                puts(""), Find = 1;
        }
        return;
    }
	for(a = 1; a <= 6; a++)
        if(Used[a] == 0) {
			Used[a] = 1, Way[Now] = a, DFS(Now+1), Used[a] = 0;
		}
}
main() {
	while(scanf("%d", &Map[0][0]) == 1) {
        for(a = 1; a < 7; a++)
			scanf("%d", &Map[0][a]);
        for(a = 1; a < 6; a++)
            for(b = 0; b < 7; b++)
                scanf("%d", &Map[a][b]);
        Find = 0, DFS(0);
    }
    return 0;
}
