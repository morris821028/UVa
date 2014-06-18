#include <iostream>
#include <iomanip>

#include "node.h"
#include "heap.h"

using namespace std;

int Heap::cmp(int a, int b) {
    if(tree[a].f > tree[b].f)
        return 1;
    else if(tree[a].f < tree[b].f)
        return -1;
    else
        return 0;
}

Heap::Heap() {
    cnt = 0;
}

bool Heap::isEmpty() {
    return cnt == 0;
}

int Heap::getCnt() {
    return cnt;
}

void Heap::insert(Node node) {
    tree[++cnt] = node;

    int a = cnt;
    while(a != 1) {
        if(cmp(a, a/2) == 1)
            break;

        Node::swap(tree[a], tree[a/2]);

        a /= 2;
    }
}

Node Heap::remove() {
    Node tmp = tree[1];

    Node::swap(tree[1], tree[cnt--]);

    int a = 1;
    while(a < cnt) {
        if(a*2+1 <= cnt) {
            if(cmp(a, a*2) == 1 || cmp(a, a*2+1) == 1) {
                if(cmp(a*2, a*2+1) == -1)
                    Node::swap(tree[a], tree[a*2]), a = a*2;
                else
                    Node::swap(tree[a], tree[a*2+1]), a = a*2+1;
            } else
                break;
        } else if(a*2 <= cnt) {
            if(cmp(a, a*2) == 1)
                Node::swap(tree[a], tree[a*2]), a = a*2;
            else
                break;
        } else
            break;
    }

    return tmp;
}

void Heap::print() {
    for(int i = 1; i <= cnt; i++)
        cout<<"("<<setw(2)<<tree[i].x<<", "<<setw(2)<<tree[i].y<<") "<<tree[i].f<<")";
    cout<<endl;
}

