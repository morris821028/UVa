#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
// math, kinetic energy 1/2 mv^2, potential energy 1/2 k x^2, mgh
int main() {
    double K, L, S, W;
    double g = 9.81;
    while (scanf("%lf %lf %lf %lf", &K, &L, &S, &W) == 4 && K+L+S+W) {
        if (L >= S) {
            double v0 = sqrt(2 * g * S);
            if (v0 > 10) {
                puts("Killed by the impact.");
            } else {
                puts("James Bond survives.");
            }
        } else {
            double e = W * g * S - 0.5 * K * pow(S - L, 2);
            if (e < 0) {
                puts("Stuck in the air.");
            } else {
                double v0 = sqrt(e * 2/ W); // 1/2 mv^2
                if (v0 > 10) {
                    puts("Killed by the impact.");
                } else {
                    puts("James Bond survives.");
                }
            }
        }
    }
    return 0;
}