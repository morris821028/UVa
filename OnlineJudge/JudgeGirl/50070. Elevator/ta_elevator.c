#include <stdlib.h>
#include "elevator.h"
 
struct Elevator{
    int position;
    int visited[MAXF + 1];
    int u, d, F;
    int dinvalid, uinvalid;
};
 
 
Elevator* newElevator(int u, int d, int F){
    Elevator* elevator = (Elevator*) malloc(sizeof(Elevator));
    elevator->position = 1;
    elevator->u = u;
    elevator->d = d;
    elevator->F = F;
    elevator->visited[1] = 1;
    for(int i = 2; i <= F; i++)
        elevator->visited[i] = 0;
    elevator->dinvalid = 0;
    elevator->uinvalid = 0;
    return elevator;
}
 
int up(Elevator* elevator){
    int p = elevator->position + elevator->u;
    elevator->dinvalid = 0;
    if (p > elevator->F){
        if (++elevator->uinvalid > 3) return -1;
        else return 0;
    }
    elevator->position = p;
    elevator->uinvalid = 0;
    return elevator->visited[p] = 1;
}
 
int down(Elevator* elevator){
    int p = elevator->position - elevator->d;
    elevator->uinvalid = 0;
    if (p <= 0){
        if (++elevator->dinvalid > 3) return -1;
        else return 0;
    }
    elevator->position = p;
    elevator->dinvalid = 0;
    return elevator->visited[p] = 1;
}
int visited(struct Elevator* elevator, int floor){
    return elevator->visited[floor];
}
 
int getPosition(struct Elevator* elevator){
    return elevator->position;
}
