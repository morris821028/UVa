#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

int main() {
    int t, n;
    char str[100], nstr[100];
    char ch[] = "22233344455566677778889991";
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        map<string, int> record;
        getchar();
        int i, j;
        while(n--) {
            gets(str);

            for(i = 0, j = 0; str[i]; i++) {
                if(str[i] >= '0' && str[i] <= '9')
                    nstr[j++] = str[i];
                else if(str[i] >= 'A' && str[i] <= 'Z')
                    nstr[j++] = ch[str[i]-'A'];
                if(j == 3)
                    nstr[j++] = '-';
            }
            nstr[j] = '\0';
            record[nstr]++;
        }
        int flag = 0;
        for(map<string, int>::iterator i = record.begin(); i != record.end(); i++) {
            if(i->second != 1) {
                flag = 1;
                cout << i->first << ' ' << i->second << endl;
            }
        }
        if(!flag)
            puts("No duplicates.");
        if(t)
            puts("");
    }
    return 0;
}
