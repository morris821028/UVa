#include <stdio.h>

int shuff[100][53], card[53];
void change(int n) {
    static int tmp[53], i;
    for(i = 1; i <= 52; i++)
        tmp[i] = card[shuff[n][i]];
    for(i = 1; i <= 52; i++)
        card[i] = tmp[i];
}
void print() {
    static char num[][10] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9",
        "10", "Jack", "Queen", "King"};
    static char suit[][10] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    static int i;
    for(i = 1; i <= 52; i++) {
        printf("%s of %s\n", num[card[i]%13], suit[(card[i]-1)/13]);
    }
}
int main() {
    int t, n;
    int i, j, k;
    char line[50];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(k = 1; k <= n; k++) {
            for(i = 1; i <= 52; i++) {
                scanf("%d", &shuff[k][i]);
            }
        }
        for(i = 1; i <= 52; i++)
            card[i] = i;
        gets(line);
        while(gets(line)) {
            if(line[0] == '\0') break;
            sscanf(line, "%d", &n);
            change(n);
        }
        print();
        if(t)
            puts("");
    }
    return 0;
}
