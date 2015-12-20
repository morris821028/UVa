#include "node.h"
#include <stdio.h>
#include <stdlib.h>

static int path[1024];

static void dfs(struct node *u, int dep) {
	if (u == NULL)	return ;
	path[dep] = u->data;
	if (u->left == NULL && u->right == NULL) {
		for (int i = 0; i <= dep; i++)
			printf("%d%c", path[i], " \n"[i == dep]);
		return ;
	}
	dfs(u->left, dep+1);
	dfs(u->right, dep+1);
}

void print_all_paths(struct node *root) {
	dfs(root, 0);
}
