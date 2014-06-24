#include <stdio.h> 
#include <stdio.h>
#include <map>
#include <string.h>
#include <iostream>
using namespace std;	
map<string, string> R;
void init() {
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
}
int solve(char s[]) {
    int len = strlen(s);
    string ret = "";
    for(int i = 0; i < len; i++) {
        if(s[i] == 'A' && s[i+1] == 'U' && s[i+2] == 'G') {
        	i += 3;
            char tmp, flag = 0;
            while(i < len) {
                tmp = s[i+3];
                s[i+3] = '\0';
                if(R[s+i] == "end") {
                	cout << ret << endl;
                	return 1;
                }
                if(flag)  ret += "-";
                flag = 1;
                ret += R[s+i];
                s[i+3] = tmp;
                i += 3;
            }
            return 0;
        }
    }
    return 0;
}

int main() {
	init();
	char s[1024], invs[1024], cs[1024], invcs[1024];
	while(scanf("%s", s) == 1 && s[0] != '*') {
		
		int test = 0, n = strlen(s);
		invs[n] = cs[n] = invcs[n] = '\0';
		for(int i = 0; i < n; i++) {
			cs[i] = s[i];
			if(s[i] == 'T')
				cs[i] = 'U';
		}
		(!test) && (test = solve(cs));
		
		for(int i = 0; i < n; i++) {
			invs[i] = cs[n - i - 1];
		}
		(!test) && (test = solve(invs));
		
		for(int i = 0; i < n; i++) {
			switch(invs[i]) {
				case 'A': invcs[i] = 'U';break;
				case 'U': invcs[i] = 'A';break;
				case 'G': invcs[i] = 'C';break;
				case 'C': invcs[i] = 'G';break;
			}
		}
		(!test) && (test = solve(invcs));
		
		for(int i = 0; i < n; i++) {
			invs[i] = invcs[n - i - 1];
		}
		(!test) && (test = solve(invs));
		
		if(!test)
			puts("*** No translatable DNA found ***");
	}
	return 0;
}
