#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int t, n, m, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        queue<int> ADD, GET;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            ADD.push(x);
        }
        for(int i = 0; i < m; i++) {
            scanf("%d", &x);
            GET.push(x);
        }
        priority_queue<int, vector<int>, greater<int> > MinHeap;
        priority_queue<int, vector<int>, less<int> > MaxHeap;
        int i = 0;
        while(!ADD.empty()) {
            if( !MinHeap.empty() && ADD.front() > MaxHeap.top())
                MinHeap.push(ADD.front());
            else
                MaxHeap.push(ADD.front());
            ADD.pop();
            while(!GET.empty() && MaxHeap.size()+MinHeap.size() == GET.front()) {
                while(MaxHeap.size() != i) {
                    if(MaxHeap.size() < i) {
                        MaxHeap.push(MinHeap.top());
                        MinHeap.pop();
                    } else if(MaxHeap.size() > i) {
                        MinHeap.push(MaxHeap.top());
                        MaxHeap.pop();
                    }
                }
                printf("%d\n", MinHeap.top());
                i++, GET.pop();
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
