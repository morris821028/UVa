#include<stdio.h>
main() {
	char s[1025];
	while(gets(s)) {
		if(s[0] == '#' && s[1] == '\0')	break;
		long long A[1026] = {};
		int a,b;
		for(a = 0; s[a]; a++)	A[a] = s[a];
		for(a = 0; s[a]; a++)
			A[a] %= 34943, A[a+1] += A[a]*256;
		for(b = 0; ; b++)
			if((b+A[a]*256)%34943 == 0) break;
		printf("%02X %02X\n", b/256, b%256);
	}
	return 0;
}
