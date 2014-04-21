/**********************************************************************************/
/*  Problem: a263 "日期差幾天" from 板橋高中練習題                    */
/*  Language: C (662 Bytes)                                                       */
/*  Result: AC(8ms, 288KB) judge by this@ZeroJudge                                */
/*  Author: morris1028 at 2012-08-13 09:34:52                                     */
/**********************************************************************************/


#include <stdio.h>
int addDay[] = {0, 0, 31, 59, 90, 120, 151,
                181, 212, 243, 273, 304,
                334, 365};
int cntDay(int y, int m, int d) {
    int sum, leap, isleap;
    isleap = (y%4 == 0 && y%100 != 0) || y%400 == 0;
    y--;
    leap = y/4 - y/100 + y/400;
    sum = y*365 + leap + addDay[m] + (m > 2)*isleap + d;
    return sum;
}
int main() {
    int y, m, d;
    while(scanf("%d %d %d", &y, &m, &d) == 3) {
        int sum = cntDay(y, m, d);
        scanf("%d %d %d", &y, &m, &d);
        sum -= cntDay(y, m, d);
        if(sum < 0)
            sum *= -1;
        printf("%d\n", sum);
    }
    return 0;
}

