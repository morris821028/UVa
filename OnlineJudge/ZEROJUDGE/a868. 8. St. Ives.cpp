#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	map<string,int> R, C;
    char s1[1024], s2[1024], s3[1024];
    string word[] = {"TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN",
                        "ELEVEN", "TWELVE", "THIRTEEN" };
    for (int i = 0; i < 12; i++)
    	R[word[i]] = i+2;
    scanf("%*s %*s %*s %s %s", s1, s2);
    C[s2] = R[s1];
    scanf("%*s %s %*s %s %s", s1, s2, s3);
    n = strlen(s1), s1[n] = 'S', s1[n+1] = '\0';
    C[s3] = R[s2] * C[s1];
    scanf("%*s %s %*s %s %s", s1, s2, s3);
    n = strlen(s1), s1[n] = 'S', s1[n+1] = '\0';
    C[s3] = R[s2] * C[s1];
    scanf("%*s %s %*s %s %s", s1, s2, s3);
    n = strlen(s1), s1[n] = 'S', s1[n+1] = '\0';
    C[s3] = R[s2] * C[s1];
    
    scanf("%*s %*s %s", s1);
    n = strlen(s1), s1[n-1] = '\0';
    printf("%d %s\n", C[s1], s1);
	return 0;
}
