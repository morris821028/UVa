#include <stdio.h>
#include <algorithm>
using namespace std;
int target[1024], init[1024];
int n, head;
void oper1() {
    if(head == n-1)
        swap(init[head], init[0]);
    else
        swap(init[head], init[head+1]);
    putchar('1');
}
void oper2() {
    putchar('2');
    head++;
    if(head == n)
        head = 0;
    init[n] = init[head];
}
int main() {
    int i, j, k;
    int first = 0;
    while(scanf("%d", &n) == 1 && n) {
        first = 1;
        for(i = 0; i < n; i++)
            scanf("%d", &target[i]);
        for(i = 0; i < n; i++)
            init[i] = i+1;
        head = 0;
        for(i = 1; i < n; i++) {
            while(init[head] != target[i]) {
                oper2();
            }
            while(init[head+1] != target[i-1]) {
                oper1();
                oper2();
            }
            oper1();
        }
        oper2();
        while(init[head] != target[0])
            oper2();
        printf("\n");
    }
    return 0;
}
