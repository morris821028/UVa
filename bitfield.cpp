#include <stdio.h>
struct bitfield {
    unsigned int s0:1;
    unsigned int s1:1;
    unsigned int s2:1;
    unsigned int s3:1;
    unsigned int s4:1;
    unsigned int s5:1;
    unsigned int s6:1;
    unsigned int s7:1;
};
union NUM {
    char word;
    bitfield bit;
};
int main() {
    NUM n;
    n.word = 65;
    printf("%c(%d)\n", n.word, n.word);
    printf("%d%d%d%d-%d%d%d%d\n", n.bit.s7, n.bit.s6, n.bit.s5, n.bit.s4
           , n.bit.s3, n.bit.s2, n.bit.s1, n.bit.s0);
    return 0;
}
