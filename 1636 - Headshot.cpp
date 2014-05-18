#include <stdio.h>
#include <string.h>

int main(){
	char s[1024];
    while(scanf("%s", s) == 1){
        int n = strlen(s);
        int zero = 0, one = 0, czero = 0;
        for(int i = 0 ; i < n ; i++ ){
            if(s[i] == '1') 
				continue;
            zero++;
            if(s[(i+1)%n] == '0') czero++;
        }
        // czero - zero * (zero / n)
        if(czero * n == zero * zero) 
			puts("EQUAL");
        else if(czero * n > zero * zero)
			puts("SHOOT");
        else 
			puts("ROTATE");
    }
    return 0;
}
