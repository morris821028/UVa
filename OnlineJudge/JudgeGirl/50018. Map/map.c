#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(Map *map) {
	map->sz = 0;
}
int map(Map *map, const int key, const char *value) {
	for (int i = 0; i < map->sz; i++) {
		if (map->dat[i].key == key) {
			strcpy(map->dat[i].val, value);
			return 0;
		}
	}
	int n = map->sz;
	map->dat[n].key = key;
	strcpy(map->dat[n].val, value);
	map->sz++;
	return 1;
}
int numPairs(Map *map) {
	return map->sz;
}
static int intcmp(const void *a, const void *b) {
	return *(int *) a - *(int *) b;
}
static int paircmp(const void *a, const void *b) {
	return intcmp(&((*(MapPair**)a)->key), &((*(MapPair**)b)->key));
}
void print(Map *map) {
	static MapPair *A[1024];
	for (int i = 0; i < map->sz; i++)
		A[i] = &(map->dat[i]);
	qsort(A, map->sz, sizeof(MapPair*), paircmp);
	printf("----- map begin -----\n");
	for (int i = 0; i < map->sz; i++) {
		printf("%d %s\n", A[i]->key, A[i]->val);
	}
	printf("----- end       -----\n");
}
const char *getValue(Map *map, const int key) {
	for (int i = 0; i < map->sz; i++) {
		if (map->dat[i].key == key)
			return map->dat[i].val;
	}
	return NULL;
}
int unmap(Map *map, int key) {
	for (int i = 0; i < map->sz; i++) {
		if (map->dat[i].key == key) {
			for (int j = i+1; j < map->sz; j++)
				map->dat[j-1] = map->dat[j];
			map->sz--;
			return 1;
		}
	}
	return 0;
}
int reverseMap(Map *map, const char *value, int keys[]) {
	int n = 0;
	for (int i = 0; i < map->sz; i++) {
		if (!strcmp(map->dat[i].val, value))
			keys[n++] = map->dat[i].key;
	}
	qsort(keys, n, sizeof(int), intcmp);
	return n;
}
