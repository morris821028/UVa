#include <stdio.h>
#include <string.h>

typedef struct employee {
	int id;
	char first_name[32];
	char last_name[32];
	int boss_id;
} employee;
void readName(employee *e) {
	scanf("%s %s", e->first_name, e->last_name);
}

int n, m;
employee A[32];
int g[32][32];
int nameToIndex(employee *e) {
	for (int i = 0; i < n; i++) {
		if (!strcmp(A[i].first_name, e->first_name) &&
			!strcmp(A[i].last_name, e->last_name))
			return i;
	}
	return -1;
}
int parent[32];
void build_graph() {
	for (int i = 0; i < n; i++)
		parent[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)	continue;
			if (A[i].boss_id == A[j].id) {
				parent[i] = j;
			}
		}
	}
}
int relation(int x, int y) {
	int tx = parent[x], ty = parent[y];
	while (tx != parent[tx]) {
		if (tx == y)	return 0;
		tx = parent[tx];
	}	
	if (tx == y)	return 0;
	while (ty != parent[ty]) {
		if (ty == x)	return 1;
		ty = parent[ty];
	}
	if (ty == x)	return 1;
	if (tx == ty)
		return 2;
	return 3;
}
int main() {
	const char out[4][32] = {"subordinate", "supervisor", "colleague", "unrelated"};
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i].id);
			readName(&A[i]);
			scanf("%d", &A[i].boss_id);
		}
		build_graph();
		scanf("%d", &m);
		employee x, y;
		for (int i = 0; i < m; i++) {
			readName(&x);
			readName(&y);
			int ix = nameToIndex(&x), iy = nameToIndex(&y);
			if (ix == -1 || iy == -1) {
				puts(out[3]);
			} else {
				puts(out[relation(ix, iy)]);
			}
		}
	}
	return 0;
}
