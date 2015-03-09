#include <stdio.h>
#include <string.h>

char sol[12][5] = {"C", "C#", "D",
"D#", "E", "F", "F#", "G", "G#",
"A", "A#", "B"}, c[] = {2,2,1,2,2,2,1};
int main() {
    char in[1024], b[5];
    int i, j, k, st;
    while(gets(in)) {
        b[0] = in[0];
        if(in[1] == '#') {
            b[1] = in[1], b[2] = 0;
            for(i = 0; i < 12; i++)
                if(!strcmp(b, sol[i]))
                    st = i;
            k = 2;
        } else {
            b[1] = 0;
            for(i = 0; i < 12; i++)
                if(!strcmp(b, sol[i]))
                    st = i;
            k = 1;
        }
        int buf[10] = {st}, idx = 1, num;
        for(i = 0; i < 7; i++) {
            st = (st + c[i])%12;
            buf[idx++] = st;
        }
        st = 0;
        printf("%s", b);
        for(; in[k]; k++) {
            num = 0;
            if(in[k] == '+') {
                k++;
                while(in[k] >= '0' && in[k] <= '9')
                    num = num*10 + in[k++]-'0';
                k--;
                num--;
                st = (st + num)%7;
            } else {
                k++;
                while(in[k] >= '0' && in[k] <= '9')
                    num = num*10 + in[k++]-'0';
                k--;
                num--;
                st = ((st - num)%7+7)%7;
            }
            printf(" %s", sol[buf[st]]);
        }
        puts("");
    }
    return 0;
}
