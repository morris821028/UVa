#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void test_all(Map *maps, int map_n) {
	for (int i = 0; i < map_n; i++)
		init(&maps[i]);
	int cmds, mid, cmd, key;
	char val[128];
	int keylist[1024];
	scanf("%d", &cmds);
	for (int i = 0; i < cmds; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d", &mid);
			print(&maps[mid]);
		} else if (cmd == 2) {	
			scanf("%d %d %s", &mid, &key, val);
			int f = map(&maps[mid], key, val);
			printf("mf %d\n", f);
		} else if (cmd == 3) {
			scanf("%d %d", &mid, &key);
			int f = unmap(&maps[mid], key);
			printf("uf %d\n", f);
		} else if (cmd == 4) {
			scanf("%d %s", &mid, val);
			int keylist_n = reverseMap(&maps[mid], val, keylist);
			assert(keylist_n <= 1024);
			printf("list");
			for (int i = 0; i < keylist_n; i++)
				printf(" %d", keylist[i]);
			puts("");
		} else if (cmd == 5) {
			scanf("%d", &mid);
			int ret = numPairs(&maps[mid]);
			assert(ret <= 1024);
			printf("size %d\n", ret);
		} else {
			assert(false);
		}
	}
}
int main() {
	int spec;
	int map_n = 32;
	Map *maps = (Map *) malloc(sizeof(Map) * map_n);
	test_all(maps, map_n);
	free(maps);
	return 0;
}
/*
15
1 0
2 0 1 10pt
1 0
2 0 2 10pt
1 0
2 0 2 20pt
2 0 0 god
1 0
3 0 0
2 0 0 pangfeng
1 0
2 0 3 10pt
4 0 10pt
1 0
5 0
*/
