#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int main() {
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        printf("Case %d:\n", ++cases);
        priority_queue<int, vector<int>, less<int> > heap;
        int n, m, x;
        scanf("%d %d", &n, &m);
        while(n--) {
            scanf("%d", &x);
            heap.push(x);
        }
        while(m--) {
            scanf("%d", &x);
            if(x == 1) {
                scanf("%d", &x);
                heap.push(x);
            } else {
                if(heap.empty())
                    puts("It's empty!");
                else {
                    printf("Max: %d\n", heap.top());
                    heap.pop();
                }
            }
        }
        if(heap.empty())
            printf("It's empty!");
        while(!heap.empty())
            printf("%d ", heap.top()), heap.pop();
        puts("");
    }
    return 0;
}
