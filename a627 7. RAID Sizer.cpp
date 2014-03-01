#include <stdio.h>
#define oo 0xfffffff
int V[4] = {250,400,500,750}, P[5] = {75,110,140,250};
int i, j, item, price, kind, used;
void RAID0(int v) {
    price = oo;
    for(i = 0; i < 4; i++) {
        for(j = 1; j <= 8; j++) {
            if(j * V[i] >= v) {
                if(j * P[i] < price)
                    price = j * P[i], item = j, kind = i, used = j;
            }
        }
    }
}
void RAID1(int v) {
    price = oo;
    for(i = 0; i < 4; i++) {
        for(j = 1; j <= 4; j++) {
            if(j * V[i] >= v) {
                if(j*2 * P[i] < price)
                    price = j*2 * P[i], item = j*2, kind = i, used = j;
            }
        }
    }
}
void RAID5(int v) {
    price = oo;
    for(i = 0; i < 4; i++) {
        for(j = 1; j <= 7; j++) {
            if(j * V[i] >= v) {
                if((j+1) * P[i] < price)
                    price = (j+1) * P[i], item = j+1, kind = i, used = j;
            }
        }
    }
}
int main() {
    int v, raid;
    while(scanf("%d %d", &v, &raid) == 2) {
        if(raid == 0)
            RAID0(v);
        else if(raid == 1)
            RAID1(v);
        else
            RAID5(v);
        printf("Qty: %d Disk: %dGB Price: $%d\n", item, V[kind], P[kind]);
        printf("Total price of this %dGB array: $%d\n\n", V[kind]*used, price);
    }
    return 0;
}
