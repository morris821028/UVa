#include <stdio.h>
#include <map>
#include <string.h>
#include <iostream>
using namespace std;
map<string, string> R;
int main() {
    R["UUU"] = R["UUC"] = "Phe";
    R["UUA"] = R["UUG"] = R["CUU"] = R["CUC"] = "Leu";
    R["CUA"] = R["CUG"] = "Leu";
    R["UCU"] = R["UCC"] = R["UCA"] = R["UCG"] = "Ser";
    R["AGU"] = R["AGC"] = "Ser";
    R["CCU"] = R["CCC"] = R["CCA"] = R["CCG"] = "Pro";
    R["CGU"] = R["CGC"] = R["CGA"] = R["CGG"] = "Arg";
    R["AGA"] = R["AGG"] = "Arg";
    R["ACU"] = R["ACC"] = R["ACA"] = R["ACG"] = "Thr";
    R["GUU"] = R["GUC"] = R["GUA"] = R["GUG"] = "Val";
    R["GCU"] = R["GCC"] = R["GCA"] = R["GCG"] = "Ala";
    R["GGU"] = R["GGC"] = R["GGA"] = R["GGG"] = "Gly";
    R["AUU"] = R["AUC"] = R["AUA"] = "Ile";
    R["UAU"] = R["UAC"] = "Tyr";
    R["CAU"] = R["CAC"] = "His";
    R["CAA"] = R["CAG"] = "Gln";
    R["UGU"] = R["UGC"] = "Cys";
    R["AAU"] = R["AAC"] = "Asn";
    R["AAA"] = R["AAG"] = "Lys";
    R["GAU"] = R["GAC"] = "Asp";
    R["GAA"] = R["GAG"] = "Glu";
    R["AUG"] = "Met";
    R["UAA"] = R["UAG"] = "end";
    R["UGA"] = "end";
    R["UGG"] = "Trp";
    char s[32767], buf[32767];
    while(gets(s) && s[0] != '0') {
        printf("Case \" %s \":\n", s);
        int idx = 0, i, len = strlen(s), flag = 0;
        for(i = 0; s[i]; i++)
            if(s[i] == '3') flag = 1;
        if(flag) {
            for(i = strlen(s)-1; i >= 0; i--)
                if(s[i] >= 'A' && s[i] <= 'Z')
                    buf[idx++] = s[i];
        } else {
            for(i = 0; s[i]; i++)
                if(s[i] >= 'A' && s[i] <= 'Z')
                    buf[idx++] = s[i];
        }
        buf[idx] = '\0';
        for(i = 0; i <= idx; i++)
            s[i] = buf[i];
        for(i = 0; i <= idx; i++) {
            if(s[i] == 'A' && s[i+1] == 'U' && s[i+2] == 'G') {
                char tmp, flag = 0;
                while(true) {
                    tmp = s[i+3];
                    s[i+3] = '\0';
                    if(R[s+i] == "end") {
                        s[i+3] = tmp;
                        i += 2;
                        break;
                    }
                    if(flag)  putchar('-');
                    flag = 1;
                    cout << R[s+i];
                    s[i+3] = tmp;
                    i += 3;
                }
                puts("");
            }
        }
    }
    return 0;
}
