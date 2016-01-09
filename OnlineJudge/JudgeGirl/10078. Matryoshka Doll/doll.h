#ifndef _DOLL_H
#define _DOLL_H

typedef struct Doll {
    char top, bottom;
    struct Doll *interior;
} Doll;

Doll *newDoll(char top, char bottom);
void package(Doll *outer, Doll *inter);
const char* doll_c_str(Doll *doll);

#endif
