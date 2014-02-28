#include<stdio.h>
main() {
    char s[1030], *A;
    while(gets(s)) {
        if(s[0] == '#')    break;
        int CRC = 0;
        for(A = s; *A; A++)
        	CRC = ((CRC*256)+(*A))%34943;
        CRC = ((34943 - ((CRC*256)%34943*256))%34943 + 34943)%34943;
        printf("%02X %02X\n", CRC/256, CRC%256);
    }
    return 0;
}
