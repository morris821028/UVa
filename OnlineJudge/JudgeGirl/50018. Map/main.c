#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void test_spec0(Map *maps, int map_n) {
	for (int i = 0; i < map_n; i++)
		init(&maps[i]);
	for (int i = 0; i < map_n; i++)
		print(&maps[i]);
}
void test_spec1(Map *maps, int map_n) {
	for (int i = 0; i < map_n; i++)
		init(&maps[i]);
	int cmds, mid, cmd, key;
	char val[128];	
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
		} else {
			assert(false);
		}
	}
}
void test_spec2(Map *maps, int map_n) {
	for (int i = 0; i < map_n; i++)
		init(&maps[i]);
	int cmds, mid, cmd, key;
	char val[128];	
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
		} else {
			assert(false);
		}
	}
}
void test_spec3(Map *maps, int map_n) {
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
			printf("list");
			for (int i = 0; i < keylist_n; i++)
				printf(" %d", keylist[i]);
			puts("");
		} else {
			assert(false);
		}
	}
}
void test_spec4(Map *maps, int map_n) {
	for (int i = 0; i < map_n; i++)
		init(&maps[i]);
	int cmds, mid, cmd, key;
	char val[128];
	int keylist[1024];
	scanf("%d", &cmds);
	for (int i = 0; i < cmds; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			assert(false);
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
			assert(false);
			scanf("%d %s", &mid, val);
			int keylist_n = reverseMap(&maps[mid], val, keylist);
			assert(keylist_n <= 1024);
			for (int i = 0; i < keylist_n; i++)
				printf("%d%c", keylist[i], " \n"[i == keylist_n-1]);
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
void test_spec5(Map *maps, int map_n) {
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
			assert(false);
		} else if (cmd == 4) {
			assert(false);
		} else if (cmd == 5) {
			assert(false);
		} else if (cmd == 6) {
			scanf("%d %d", &mid, &key);
			char *val = getValue(&maps[mid], key);
			printf("%s\n", val == NULL ? "NOT FOUND" : val);
		}
	}
}
int main() {
	int spec;
	while (scanf("%d", &spec) == 1) {
		int map_n = 32;
		Map *maps = (Map *) malloc(sizeof(Map) * map_n);
		if (spec == 0) {
			test_spec0(maps, map_n);
		} else if (spec == 1) {
			test_spec1(maps, map_n);
		} else if (spec == 2) {
			test_spec2(maps, map_n);
		} else if (spec == 3) {
			test_spec3(maps, map_n);
		} else if (spec == 4) {
			test_spec4(maps, map_n);
		} else if (spec == 5) {
			test_spec5(maps, map_n);
		}
		free(maps);
	}
	return 0;
}

/*
[10%] Implement init and print.
[30%] Implement init, map, and print.
[20%] Implement init, map, and unmap, and print.
[30%] Implement init, map, and unmap, print, and reverseMap.
[10%] Implemment init, map, unmap, and numPairs.
*/
