#include<stdio.h>
int main() {
	int n, Case = 0, i, j;
	char str[1002];
	while(scanf("%d", &n) == 1 && n) {
		getchar();
		printf("Case %d:\n", ++Case);
		puts("#include<string.h>\n#include<stdio.h>\nint main()\n{");
		while(n--) {
			gets(str);
			printf("printf(\"");
			for(i = 0; str[i]; i++) {
				if(str[i] == '\\' || str[i] == '\"')
					printf("\\");
				printf("%c", str[i]);
			}
			printf("\\n\");\n");
		}
		puts("printf(\"\\n\");\nreturn 0;\n}");
	}
    return 0;
}
