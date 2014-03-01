#include <stdio.h>
#include <string.h>
struct Node {
    Node *next;
    int ele;
    Node(int e) {
        next = NULL;
        ele = e;
    }
};
int main() {
    int n, Case = 0;
    short team[1000000];
    char str[100];
    while(scanf("%d", &n) == 1 && n) {
        Node *teamSet[1001], *head = NULL, *tail = NULL, *node;
        int i, x, y, in;
        memset(team, 0, sizeof(team));
        for(i = 1; i <= n; i++) {
            scanf("%d", &x);
            while(x--) {
                scanf("%d", &y);
                team[y] = i;
            }
            teamSet[i] = NULL;
        }
        printf("Scenario #%d\n", ++Case);
        while(scanf("%s", str)) {
            if(str[0] == 'S') {
                break;
            } else if(str[0] == 'D') {
                printf("%d\n", head->ele);
                int teamNum = team[head->ele];
                if(teamSet[teamNum] == head)
                    teamSet[teamNum] = NULL;
                node = head;
                head = head->next;
                delete node;
            } else {
                scanf("%d", &in);
                Node *tmp = new Node(in);
                int teamNum = team[in];
                if(teamSet[teamNum] == NULL) {
                    if(head == NULL) {
                        head = tmp;
                        tail = head;
                    } else {
                        tail->next = tmp;
                        tail = tmp;
                    }
                } else {
                    node = teamSet[teamNum];
                    tmp->next = node->next;
                    if(tmp->next == NULL)
                        tail = tmp;
                    node->next = tmp;
                }
                teamSet[teamNum] = tmp;
            }
        }
        puts("");
    }
    return 0;
}
