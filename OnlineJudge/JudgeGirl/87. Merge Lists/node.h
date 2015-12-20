#ifndef _NODE_H
#define _NODE_H
 
struct node {
    int value;
    struct node * next;
};

struct node * merge(struct node *, struct node *);
 
#endif
