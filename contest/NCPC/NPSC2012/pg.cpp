#include <stdio.h>

int main() {
    int t, i;
    unsigned int hh0, hh1, hh2, hh3, hh4;
    unsigned int h0 = 0xdead, h1 = 0xcafe, h2 = 0xbeef, h3 = 0x3399, h4 = 0x7788, k = 0x5a82;
    char buf[100], bt = 0;
    for(i = '0'; i <= '9'; i++) buf[bt++] = i;
    for(i = 'A'; i <= 'Z'; i++) buf[bt++] = i;
    for(i = 'a'; i <= 'z'; i++) buf[bt++] = i;
    scanf("%d", &t);
    while(t--) {
        scanf("%x %x %x %x %x", &hh0, &hh1, &hh2, &hh3, &hh4);
        char word[5];
        for(i = 0; i < bt; i++) {
            word[0] = buf[i]-' ';
            if(8*(4*(h0)+h1+h2+h4+k+word[0])+h4 == hh4)
                break;
        }
        for(i = 0; i < bt; i++) {
            word[1] = buf[i]-' ';
            if(8*(4*(4*(h0)+h1+h2+h4+k+word[0])+h0+8*(h1)+h3+k+word[1])+h3 == hh3)
                break;
        }
        for(i = 0; i < bt; i++) {
            word[2] = buf[i]-' ';
            if(8*(4*(4*(4*(h0)+h1+h2+h4+k+word[0])+h0+8*(h1)+h3+k+word[1])+4*(h0)
                     +h1+h2+h4+k+word[0]+8*(h0)+h2+k+word[2])+h2 == hh2)
                break;
        }
        for(i = 0; i < bt; i++) {
            word[3] = buf[i]-' ';
            if(h1+4*(4*(4*(4*(h0)+h1+h2+h4+k+word[0])+h0+8*(h1)+h3+k+word[1])+4*(h0)+h1+h2+h4+k+word[0]
+8*(h0)+h2+k+word[2])+4*(4*(h0)+h1+h2+h4+k+word[0])+h0+8*(h1)+h3+k+word[1]+8*(4*(h0)
+h1+h2+h4+k+word[0])+8*(h1)+k+word[3] == hh1)
                break;
        }
        for(i = 0; i < bt; i++) {
            word[4] = buf[i]-' ';
            if(h0+4*(4*(4*(4*(4*(h0)+h1+h2+h4+k+word[0])+h0+8*(h1)+h3+k+word[1])+4*(h0)+h1+h2+h4+k+word[0]
+8*(h0)+h2+k+word[2])+4*(4*(h0)+h1+h2+h4+k+word[0])+h0+8*(h1)+h3+k+word[1]+8*(4
*(h0)+h1+h2+h4+k+word[0])+8*(h1)+k+word[3])+4*(4*(4*(h0)+h1+h2+h4+k+word[0])+h0+8*(h1
)+h3+k+word[1])+4*(h0)+h1+h2+h4+k+word[0]+8*(h0)+h2+k+word[2]+8*(4*(4*(h0)+h1+h2+h4+k
+word[0])+h0+8*(h1)+h3+k+word[1])+8*(h0)+k+word[4] == hh0)
                break;
        }
        for(i = 0; i < 5; i++)
            printf("%c", word[i]+' ');
        puts("");
    }
    return 0;
}
/*
4
0b8414f6 027eeb13 0453edaf 00f93379 002f2d88
0b8419b0 027eec17 0453ef3f 00f933f1 002f2da8
0b8459a5 027efa02 045406ff 00f93981 002f2f10
0b845578 027ef91a 04540577 00f93921 002f2ef8
*/
