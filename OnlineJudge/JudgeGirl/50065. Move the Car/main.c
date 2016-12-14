#include <stdio.h>
#include <assert.h>
#include "car.h"
 
int main(){
    int N;
    CarStatus car;
    Command commands[MAXN];
 
    assert(scanf("%d%d%d", &car.x, &car.y, &car.g) == 3);
    assert(scanf("%d", &N) == 1);
    for(int i = 0; i < N; i++)
        assert(scanf("%d%d", &commands[i].t, &commands[i].v) == 2);
 
    CarStatusList result= carSimulation(car, commands);
 
    for(int i = 0; i < result.num; i++)
        printf("%d %d %d\n", result.status[i].x, result.status[i].y, result.status[i].g);
 
    return 0;
}
