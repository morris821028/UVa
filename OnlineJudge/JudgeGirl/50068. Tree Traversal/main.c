#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000 
 
Node* newNode(int label, Node *l, Node *r) {
    Node *u = (Node *) malloc(sizeof(Node));
    u->label = label, u->left = l, u->right = r;
    return u;
}
 
int main() {
    Node *root = newNode(
            6,
            newNode(
                3,
                newNode(1, 
                        NULL, 
                        newNode(2, NULL, NULL)
                        ),
                newNode(5, 
                        newNode(4, NULL, NULL), 
                        NULL
                        )                
            ),
            newNode(
                7,
                NULL,
                NULL                
            )
    );
 
    int N, command[MAX];
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &command[i]);        
    }
    traversal(root, N, command);
    return 0;
}
