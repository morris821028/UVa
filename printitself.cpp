#include<stdio.h>
#include<stdlib.h>
int main() {
	char str[] = "#include<stdio.h>%c#include<stdlib.h>%cint main() {%c%cchar str[] = %c%s%c;%c%cprintf(str, 10, 10, 10, 9, 34, str, 34, 10, 10, 9, 10, 10, 9, 10);%c%cgetchar();%c%creturn 0;%c}";
	printf(str, 10, 10, 10, 9, 34, str, 34, 10, 9, 10, 9, 10, 9, 10);
	getchar();
    return 0;
}
