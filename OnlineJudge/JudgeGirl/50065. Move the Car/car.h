#ifndef _CAR_H
#define _CAR_H
 
#define MAXN 100
 
typedef struct{
    int x, y;
    int g;
} CarStatus;
 
typedef struct{
    int t, v;
} Command;
 
typedef struct{
    int num;
    CarStatus status[MAXN];
} CarStatusList;
 
CarStatusList carSimulation(CarStatus car, Command commands[]);
 
#endif
