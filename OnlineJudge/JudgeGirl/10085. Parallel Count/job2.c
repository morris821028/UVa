#include "utils.h"
 
int ret[128];
int run(int n, int key) {
    int sum = 0;
    f(n, key, ret, ret+1, ret+2, ret+3);
    for (int i = 0; i < 4; i++)
        sum += ret[i];
    return sum;
}
