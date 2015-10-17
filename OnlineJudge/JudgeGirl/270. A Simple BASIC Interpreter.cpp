#include <stdio.h>
#include <string.h>
const char SEPARA[10] = " \n";
char code[2048], source[1024][2048];
char _memIdx[1024][512];
int _memVal[1024];
int n = 0, PC = 0, m = 0;
void setval(char s[], int val) {
	for (int i = 0; i < m; i++) {
		if (!strcmp(s, _memIdx[i])) {
			_memVal[i] = val;
			return ;
		}
	}
	_memVal[m] = val;
	strcpy(_memIdx[m], s);
	m++;
}
int getval(char s[]) {
	for (int i = 0; i < m; i++) {
		if (!strcmp(s, _memIdx[i])) {
			return _memVal[i];
		}
	}
	return -1;
}
void dump() {
//	printf("PC %d ", PC);
//	for (int i = 0; i < m; i++)
//		printf("%s %d, ", _memIdx[i], _memVal[i]);
//	puts("");
//	getchar();
}
int run() {
	strcpy(code, source[PC]);
	char *token, *var, *foo, *val, *opr, *rhs, *lhs;
	int x;
	if (PC == 0) {
		int x;
		var = strtok(code, SEPARA);
		while (var && strcmp(var, "END")) {
			foo = strtok(NULL, SEPARA);
			val = strtok(NULL, SEPARA);
			sscanf(val, "%d", &x);
			setval(var, x);
			var = strtok(NULL, SEPARA);
		}
		PC++;
		return 1;
	}
	token = strtok(code, SEPARA);
	if (!strcmp(token, "GOTO")) {
		val = strtok(NULL, SEPARA);
		sscanf(val, "%d", &x);
		PC = x;
		return 1;
	}
	if (!strcmp(token, "IF")) {
		var = strtok(NULL, SEPARA);
		opr = strtok(NULL, SEPARA);
		rhs = strtok(NULL, SEPARA);
		strtok(NULL, SEPARA);
		val = strtok(NULL, SEPARA);
		sscanf(val, "%d", &x);
		int a = getval(var), b = getval(rhs), equ = 0;
		if (!strcmp(opr, "==")) {
			equ = a == b;
		} else if (!strcmp(opr, "!=")) {
			equ = a != b;
		} else if (!strcmp(opr, ">")) {
			equ = a > b;
		} else if (!strcmp(opr, "<")) {
			equ = a < b;
		} else if (!strcmp(opr, ">=")) {
			equ = a >= b;
		} else if (!strcmp(opr, "<=")) {
			equ = a <= b;
		}
		PC = equ ? x : PC+1;
		return 1;
	}
	if (!strcmp(token, "PRINT")) {
		var = strtok(NULL, SEPARA);
		printf("%d\n", getval(var));
		PC++;
		return 1;
	}
	if (!strcmp(token, "STOP")) {
		return 0;
	}
	lhs = token;
	foo = strtok(NULL, SEPARA);
	rhs = strtok(NULL, SEPARA);
	opr = strtok(NULL, SEPARA);
	var = strtok(NULL, SEPARA);
	if (!strcmp(opr, "+")) {
		setval(lhs, getval(rhs)+getval(var));
	} else if (!strcmp(opr, "-")) {
		setval(lhs, getval(rhs)-getval(var));
	} else if (!strcmp(opr, "*")) {
		setval(lhs, getval(rhs)*getval(var));
	} else if (!strcmp(opr, "/")) {
		setval(lhs, getval(rhs)/getval(var));
	} else if (!strcmp(opr, "%")) {
		setval(lhs, getval(rhs)%getval(var));
	}
	PC++;
	return 1;	
}
int main() {
	while (gets(source[n]))	n++;
	while (run()) dump();
	return 0;
}

