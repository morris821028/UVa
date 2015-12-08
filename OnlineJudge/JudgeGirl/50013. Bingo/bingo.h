// #include <stdint.h>	// standard witdth uint64_t;
#define uint64_t unsigned long long

#ifndef BINGO_H

#define BINGO_H
int bingo(const uint64_t* board, int *rowColumn);
void printBlock(uint64_t const *block);
#endif
