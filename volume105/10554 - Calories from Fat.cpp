#include <stdio.h>
#include <string.h>
int main() {
    char line[1000];
    while(gets(line)) {
        if(!strcmp(line, "-"))
            break;
        double tot_C = 0, fat_C = 0;
        do {
            if(!strcmp(line, "-"))
                break;
            int a1, b1, c1, d1, e1;
            char a, b, c, d, e;
            sscanf(line, "%d%c %d%c %d%c %d%c %d%c", &a1, &a, &b1, &b,
                    &c1, &c, &d1, &d, &e1, &e);
            double tot_percent = 0, know = 0;
            double tmp_C = 0, tmp_fat = 0;
            if(a == 'g') {tmp_C += a1*9, tmp_fat += a1*9, know += a1*9;}
            if(a == 'C') {tmp_C += a1, tmp_fat += a1, know += a1;}
            if(a == '%') {tot_percent += a1;}

            if(b == 'g') {tmp_C += b1*4, know += b1*4;}
            if(b == 'C') {tmp_C += b1, know += b1;}
            if(b == '%') {tot_percent += b1;}

            if(c == 'g') {tmp_C += c1*4, know += c1*4;}
            if(c == 'C') {tmp_C += c1, know += c1;}
            if(c == '%') {tot_percent += c1;}

            if(d == 'g') {tmp_C += d1*4, know += d1*4;}
            if(d == 'C') {tmp_C += d1, know += d1;}
            if(d == '%') {tot_percent += d1;}

            if(e == 'g') {tmp_C += e1*7, know += e1*7;}
            if(e == 'C') {tmp_C += e1, know += e1;}
            if(e == '%') {tot_percent += e1;}

            if(a == '%') {tmp_C += (double)know*a1/(100-tot_percent), tmp_fat += (double)know*a1/(100-tot_percent);}
            if(b == '%') {tmp_C += (double)know*b1/(100-tot_percent);}
            if(c == '%') {tmp_C += (double)know*c1/(100-tot_percent);}
            if(d == '%') {tmp_C += (double)know*d1/(100-tot_percent);}
            if(e == '%') {tmp_C += (double)know*e1/(100-tot_percent);}
            tot_C += tmp_C;
            fat_C += tmp_fat;
        } while(gets(line));
        printf("%.0lf%%\n", fat_C*100/tot_C);
    }
    return 0;
}
