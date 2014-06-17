#include <stdio.h>

struct Node {
	int data;
	int height;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
};

struct Tree {
	struct Node* root;
};

typedef struct Node Node;
typedef struct Tree Tree;

void iniNode(int, Node**);
int max(int, int);
int nodeHt(Node*);
void insert(Node*, Tree*);
void delete(Node*, Tree*);
Node* search(Node*, Node*);
Node* findSuccessor(Node*);
Node* rebalance(Node*, Tree*);
Node* sRotateLeft(Node*);
Node* sRotateRight(Node*);
Node* dRotateLeft(Node*);
Node* dRotateRight(Node*);
void calculateHt(Node*);
void print(Node*);

int main() {
	int i, j, k, m, n, command;
	Node *node;
	Tree avl[201];
	
	while(scanf("%d %d", &k, &m) == 2) {
		for(i = 0; i < m; i++)
			avl[i].root = NULL;
		
		for(i = 0; i < k; i++) {
			scanf("%d", &command);
			
			switch(command) {
				case 1:
					scanf("%d", &n);
					iniNode(n, &node);
					insert(node, &avl[n%m]);
					break;
				case 2:
					scanf("%d", &n);
					iniNode(n, &node);
					delete(search(node, avl[n%m].root), &avl[n%m]);
					break;
				default:
					puts("===== s =====");
					for(j = 0; j < m; j++)
						printf("[%03d]:", j), print(avl[j].root), puts("NULL");
					puts("===== e =====");
			}
		}
	}
	
	return 0;
}

void iniNode(int n, Node** node) {
	*node = (Node *) malloc(sizeof(Node));
	
	(*node)->data = n;
	(*node)->height = 0;
	(*node)->left = (*node)->right = (*node)->parent = NULL;
}

int max(int a, int b) {
	return a > b?a:b;
}

int nodeHt(Node* node) {
	return node == NULL?-1:node->height;
}

void insert(Node* node, Tree* tree) {
	Node *p;
	
	if(tree->root == NULL)
		tree->root = node;
	
	p = tree->root;
	while(1) {
		if(node->data < p->data) {
			if(p->left == NULL) {
				p->left = node;
				node->parent = p;
				break;
			} else
				p = p->left;
		} else if(node->data > p->data) {
			if(p->right == NULL) {
				p->right = node;
				node->parent = p;
				break;
			} else
				p = p->right;
		} else
			return ;
	}
	
	tree->root = rebalance(node, tree);
}

void delete(Node* remove, Tree* tree) {
	Node *succ, *snr;
	
	if(remove == NULL)
		return ;
	
	if(remove->left == NULL&&remove->right == NULL) {
		if(remove->parent == NULL)
			tree->root = NULL;
		else if(remove == (remove->parent)->left)
			(remove->parent)->left = NULL;
		else
			(remove->parent)->right = NULL;
		
		snr = remove->parent;
	} else {
		succ = findSuccessor(remove);
		
		if(succ == remove->left) {
			succ->parent = remove->parent;
			if(remove->parent != NULL)
				if(remove == (succ->parent)->left)
					(succ->parent)->left = succ;
				else
					(succ->parent)->right = succ;
			
			snr = succ;
		} else if(succ == remove->right) {
			succ->parent = remove->parent;
			if(remove->parent != NULL)
				if(remove == (succ->parent)->left)
					(succ->parent)->left = succ;
				else
					(succ->parent)->right = succ;
			
			succ->left = remove->left;
			if(remove->left != NULL)
				(remove->left)->parent = succ;
			
			snr = succ;
		} else {
			snr = succ->parent;
			
			(succ->parent)->left = succ->right;
			if(succ->right != NULL)
				(succ->right)->parent = succ->parent;
			
			succ->parent = remove->parent;
			if(remove->parent != NULL)
				if(remove == (succ->parent)->left)
					(succ->parent)->left = succ;
				else
					(succ->parent)->right = succ;
			
			succ->left = remove->left;
			if(remove->left != NULL)
				(remove->left)->parent = succ;
			
			succ->right = remove->right;
			(remove->right)->parent = succ;
		}
	}
	
	calculateHt(snr);
	tree->root = rebalance(snr, tree);
	
	free(remove);
}

Node* search(Node* targ, Node* root) {
	if(root == NULL)
		return NULL;
	
	if(targ->data > root->data)
		return search(targ, root->right);
	else if(targ->data < root->data)
		return search(targ, root->left);
	else
		return root;
}

Node* findSuccessor(Node* node) {
	if(node->right == NULL) {
		return node->left;
	} else {
		node = node->right;
		
		while(node->left != NULL)
			node = node->left;
		
		return node;
	}
}

Node* rebalance(Node* node, Tree* tree) {
	if(node == NULL)
		return NULL;
	
	if(nodeHt(node->left)-nodeHt(node->right) == 2) {
		if(nodeHt((node->left)->left) >= nodeHt((node->left)->right))
			node = sRotateLeft(node);
		else
			node = dRotateLeft(node);
	} else if(nodeHt(node->right)-nodeHt(node->left) == 2) {
		if(nodeHt((node->right)->right) >= nodeHt((node->right)->left))
			node = sRotateRight(node);
		else
			node = dRotateRight(node);
	} else
		calculateHt(node);
	
	if(node->parent == NULL)
		return node;
	else
		return rebalance(node->parent, tree);
}

Node* sRotateLeft(Node* k2) {
	Node *k1;
	
	k1 = k2->left;
	
	k2->left = k1->right;
	
	if(k2->left != NULL)
		(k2->left)->parent = k2;
	
	k1->parent = k2->parent;
	
	if(k1->parent != NULL)
		if(k2 == (k1->parent)->left)
			(k1->parent)->left = k1;
		else
			(k1->parent)->right = k1;
	
	k2->parent = k1;
	k1->right = k2;
	
	k2->height = max(nodeHt(k2->left), nodeHt(k2->right))+1;
	k1->height = max(nodeHt(k1->left), k2->height)+1;
	
	return k1;
}

Node* sRotateRight(Node* k2) {
	Node *k1;
	
	k1 = k2->right;
	
	k2->right = k1->left;
	
	if(k2->right != NULL)
		(k2->right)->parent = k2;
	
	k1->parent = k2->parent;
	
	if(k1->parent != NULL)
		if(k2 == (k1->parent)->left)
			(k1->parent)->left = k1;
		else
			(k1->parent)->right = k1;
	
	k2->parent = k1;
	k1->left = k2;
	
	k2->height = max(nodeHt(k2->right), nodeHt(k2->left))+1;
	k1->height = max(nodeHt(k1->right), k2->height)+1;
	
	return k1;
}

Node* dRotateLeft(Node* node) {
	node->left = sRotateRight(node->left);
	return sRotateLeft(node);
}

Node* dRotateRight(Node* node) {
	node->right = sRotateLeft(node->right);
	return sRotateRight(node);
}

void calculateHt(Node* node) {
	if(node == NULL)
		return ;
	
	node->height = max(nodeHt(node->left), nodeHt(node->right))+1;
}

void print(Node* node) {
	if(node == NULL)
		return ;
	
	print(node->left);
	printf("%d -> ", node->data);
	print(node->right);
}

