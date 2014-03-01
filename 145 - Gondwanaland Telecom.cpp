#include<stdio.h>
#include<stdlib.h>
float charge[5][3] = {{0.10,0.06,0.02},
                      {0.25,0.15,0.05},
                      {0.53,0.33,0.13},
                      {0.87,0.47,0.17},
                      {1.44,0.80,0.30}
                     };
main() {
    char stop[2], phone[10];
    int sh, sm, eh, em, C = 0;
    while(scanf("%s", stop) == 1 && stop[0] != '#') {
        scanf("%s %d %d %d %d", phone, &sh, &sm, &eh, &em);
        int D = 0, E = 0, N = 0, ssum, esum, a;
        if(eh < sh || (eh == sh && em <= sm)) eh += 24;
        ssum = sh * 60 + sm;
        esum = eh * 60 + em;
        for(a = 0; a <= 2880; a++) {
            if(a > ssum && a <= esum) {
                switch(a) {
                    case    0 ...  480: N++;break;
                    case  481 ... 1080: D++;break;
                    case 1081 ... 1320: E++;break;
                    case 1321 ... 1920: N++;break;
                    case 1921 ... 2520: D++;break;
                    case 2521 ... 2760: E++;break;
                    case 2761 ... 3360: N++;break;
                }
            }
        }
        double price = D*charge[stop[0]-'A'][0] +
                         E*charge[stop[0]-'A'][1] +
                             N*charge[stop[0]-'A'][2];
        printf("%10s%6d%6d%6d%3s%8.2lf\n", phone, D, E, N, stop, price);
    }
    return 0;
}
