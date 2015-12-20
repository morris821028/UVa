#ifndef _NODE_H
#define _NODE_H

struct node {
    struct node *left;
    struct node *right;
    int data;
};

void print_all_paths(struct node *root);

#endif
