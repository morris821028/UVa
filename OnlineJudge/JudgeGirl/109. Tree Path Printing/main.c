#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

struct node *insert_bs_tree(struct node *root, int data)
{
    struct node *current;
    if (root == NULL)
    {
        current = (struct node *)malloc(sizeof(struct node));
        assert(current != NULL);
        current->data = data;
        current->left = NULL;
        current->right = NULL;
        return current;
    }

    if (data < root->data)
        root->left = insert_bs_tree(root->left, data);
    else
        root->right = insert_bs_tree(root->right, data);
    return root;
}

int main(void)
{
    int n;
    struct node *root = NULL;

    while (scanf("%d", &n) != EOF)
        root = insert_bs_tree(root, n);
    
    print_all_paths(root);
}
