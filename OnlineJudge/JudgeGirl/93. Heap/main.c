#include <stdio.h>
#include <assert.h>
#include "heap.h"
int main(){
    struct Heap myHeap[10];
    int n;
    while(scanf("%d", &n) == 1){
        int instr;
        int min, i, ret;
        int r;
        r = scanf("%d", &instr);
        assert(r == 1);
        switch(instr){
            case 0:
                initialize(&myHeap[n]);
                break;
            case 1:
                assert(!isEmpty(&myHeap[n]));
                min = removeMin(&myHeap[n]);
                printf("min = %d\n", min);
                break;
            case 2:
                assert(!isFull(&myHeap[n]));
                r = scanf("%d", &i);
                assert(r == 1);
                add(&myHeap[n], i);
                break;
            case 3:
                ret = isFull(&myHeap[n]);
                if(ret)
                    printf("Full\n");
                else
                    printf("Not Full\n");
                break;
            case 4:
                ret = isEmpty(&myHeap[n]);
                if(ret)
                    printf("Empty\n");
                else
                    printf("Not Empty\n");
                break;
        }
    }
    return 0;
}
