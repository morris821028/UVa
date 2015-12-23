#ifndef MAP_H
#define MAP_H

typedef struct MapPair {
	int key;
	char val[128];
} MapPair;
typedef struct Map {
	MapPair dat[1024];
	int sz;
} Map;

void init(Map *map);
int map(Map *map, const int key, const char *value);
int numPairs(Map *map);
void print(Map *map);
const char *getValue(Map *map, const int key);
int unmap(Map *map, int key);
int reverseMap(Map *map, const char *value, int keys[]);

#endif
