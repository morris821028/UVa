#include <stdio.h>
const int mod = 0x3fff;
int main() {
    char op[][10] =
    {"ADD","SUB","MUL","DIV","MOV","BREQ","BRLE","BRLS",
        "BRGE","BRGR","BRNE","BR","AND","OR","XOR","NOT"
    };
    char opcode[][5] =
    { "R", "$", "PC+", ""
    };
    int opN[] =
    {2,  2,  2,  2,  2,  1,  1,  1,
        1,  1,  1,  1,  3,  3,  3,  1
    };
    char buf[500000], *p = buf;
    int opnum, i;
    while(scanf("%s", p) == 1) {
        while(*p)   p++;
    }
    p = buf;
    while(*p) {
        sscanf(p, "%1X", &opnum), p++;
        printf("%s ", op[opnum]);
        for(i = 0; i < opN[opnum]; i++) {
            if(i)   putchar(',');
            int code;
            sscanf(p, "%4X", &code);
            p += 4;
            printf("%s%d", opcode[code/(mod+1)], code&mod);
        }
        puts("");
    }
    return 0;
}
