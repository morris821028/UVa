#include <stdio.h>
using namespace std;
template<typename T>
T square(T num) {
    printf("template\n");
    return num*num;
}
double square(double num) {
    printf("double square\n");
    return num*num;
}
int main() {
    printf("%lf\n", square(23.4));
    return 0;
}
