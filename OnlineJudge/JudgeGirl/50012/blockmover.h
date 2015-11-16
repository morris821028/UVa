// #include <stdint.h>	// standard witdth uint64_t;
#ifndef BLOCKMOVER_H

#define BLOCKMOVER_H
#define uint64_t unsigned long long
void initialize(uint64_t *block, int row, int column, int size);
void printBlock(uint64_t *block);
int moveLeft(uint64_t *block);
int moveRight(uint64_t *block);
int moveUp(uint64_t *block);
int moveDown(uint64_t *block);
#undef uint64_t
#endif // BLOCKMOVER_H
