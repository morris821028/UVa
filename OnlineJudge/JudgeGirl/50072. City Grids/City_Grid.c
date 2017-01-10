#include <stdlib.h>
#include "City_Grid.h"
static City* LSON(City *x, City *y) {
	return ((x) == NULL ? (y) : (x)->east);
}
static City* USON(City *x, City *y) {
	return ((x) == NULL ? (y) : (x)->north);
}
static int dfs(City *u) {
	if (u == NULL || u->label < 0)
		return 0;
	u->label = -u->label-1;
	City *l = USON(LSON(u, NULL), NULL);
	City *r = LSON(USON(u, NULL), NULL);
	int f = l && r && l == r;
	return f + dfs(LSON(u, NULL)) + dfs(USON(u, NULL));
}
int City_Grid(City *u) {
	return dfs(u);
}
