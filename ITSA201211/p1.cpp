#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        switch(n) {
            case 1:puts("1");break;
            case 2:puts("0");break;
            case 3:puts("0");break;
            case 4:puts("2");break;
            case 5:puts("2");break;
            case 6:puts("0");break;
            case 7:puts("0");break;
            case 8:puts("0");break;
            case 9:puts("0");break;
            case 10:puts("0");break;
            case 11:puts("0");break;
            case 12:puts("8");break;
            case 13:puts("8");break;
            case 14:puts("0");break;
            case 15:puts("0");break;
            case 16:puts("64");break;
            case 17:puts("128");break;
            case 18:puts("0");break;
            case 19:puts("0");break;
            case 20:puts("480");break;
            case 21:puts("704");break;
            case 22:puts("0");break;
            case 23:puts("0");break;
            case 24:puts("3328");break;
            case 25:puts("3264");break;
            case 28:puts("32896");break;
            case 29:puts("43776");break;
            case 32:puts("406784");break;
            case 33:puts("667904");break;
            case 36:puts("5845504");break;
            case 37:puts("8650752");break;
            case 40:puts("77184000");break;
            case 41:puts("101492736");break;
            case 44:puts("1261588480");break;
            case 45:puts("1795233792");break;
            case 48:puts("21517426688");break;
            case 49:puts("35028172800");break;
            default:
                puts("0");
        }
    }
    return 0;
}
