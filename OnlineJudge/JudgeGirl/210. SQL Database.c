#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXCOL 16
#define MAXROW 64
typedef char string[96];
typedef enum {INT, STRING} DATATYPE;
typedef union mData {
	string str;
	int num;
} mData;
typedef struct Data {
	mData d;
} Data;
void Data_printString(Data *v) {
	printf("%s", v->d.str);
}
void Data_printNumber(Data *v) {
	printf("%d", v->d.num);
}
typedef struct SQLRow {
	Data fields[MAXCOL];
} SQLRow;
typedef struct SQLTable {
	// SQLTable Public Member
	int colsize, rowsize;
	string columns[MAXCOL];
	DATATYPE coltype[MAXCOL];
	SQLRow data[MAXROW];
	
	// SQLTable Public Method
	int (*columnToIndex) (struct SQLTable*, string*);
	void (*SQLquery) (struct SQLTable*, char[]);
	void (*printData[]) (Data*);
} SQLTable;
void show_table(SQLTable *table) {
	for (int i = 0; i < table->rowsize; i++) {
		for (int j = 0; j < table->colsize; j++) {
			table->printData[j](&(table->data[i].fields[j]));
			putchar(j == table->colsize-1 ? '\n' : ' ');
		}
	}
}
int columnToIndex(SQLTable *self, string *name) {
	for (int i = 0; i < self->colsize; i++)
		if (!strcmp(*name, self->columns[i]))
			return i;
	return -1;
}
int SQLoperatorToIndex(char *name) {
	if (!strcmp(name, ">"))		return 0;
	else if (!strcmp(name, "<"))	return 1;
	else if (!strcmp(name, "=="))	return 2;
	else if (!strcmp(name, "!="))	return 3;
	return -1;
}
int fetch_cond(SQLTable *self, SQLRow *row, int lhs, int op, Data *rhs) {
	if (self->coltype[lhs] == INT) {
		if (op == 0)	return row->fields[lhs].d.num > rhs->d.num;
		if (op == 1)	return row->fields[lhs].d.num < rhs->d.num;
		if (op == 2)	return row->fields[lhs].d.num == rhs->d.num;
		if (op == 3)	return row->fields[lhs].d.num != rhs->d.num;
	} else {
		int cmp = strcmp(row->fields[lhs].d.str, rhs->d.str);
		if (op == 2)	
			return cmp == 0;
		else if (op == 3)		
			return cmp != 0;
	}
	return 0;
}
void SQLquery(SQLTable *self, char cmd[]) {
	static int selcol[128], seln, has_cond;
	static int tmpTable[MAXROW];
	static string s;
	int tmpsize = self->rowsize;
	char *token;
	
	for (int i = 0; i < self->rowsize; i++)
		tmpTable[i] = i;
		
	seln = has_cond = 0;
	token = strtok(cmd, " ");
	assert (strcmp(token, "select") == 0);
	token = strtok(NULL, " ");
	while (token != NULL) {
		if (!strcmp(token, "where")) {
			has_cond = 1;
			token = strtok(NULL, " ");
			strcpy(s, token);
			int lhs = self->columnToIndex(self, &s);
			token = strtok(NULL, " ");
			int op = SQLoperatorToIndex(token);
			token = strtok(NULL, " \r\n");
			Data rhs;
			if (self->coltype[lhs] == INT)
				sscanf(token, "%d", &rhs.d.num);
			else if (self->coltype[lhs] == STRING)
				strcpy(rhs.d.str, token);
			int tmpn = 0;
			for (int i = 0; i < tmpsize; i++) {
				if (fetch_cond(self, &(self->data[tmpTable[i]]), lhs, op, &rhs))
					tmpTable[tmpn++] = tmpTable[i];
			}
			tmpsize = tmpn;
			break;
		}
		strcpy(s, token);
		selcol[seln++] = self->columnToIndex(self, &s);
		token = strtok(NULL, " ");
	}
	for (int i = 0; i < tmpsize; i++) {
		int rid = tmpTable[i];
		for (int j = 0; j < seln; j++) {
			self->printData[selcol[j]](&(self->data[rid].fields[selcol[j]]));
			putchar(j == seln-1 ? '\n' : ' ');
		}
	}
}


void create_table(SQLTable *table, const string colname[], const DATATYPE coltype[], int n) {
	table->colsize = n;
	for (int i = 0; i < n; i++) {
		strcpy(table->columns[i], colname[i]);
		table->coltype[i] = coltype[i];
		if (coltype[i] == INT)
			table->printData[i] = Data_printNumber;
		else if (coltype[i] == STRING)
			table->printData[i] = Data_printString;
	}
	table->columnToIndex = columnToIndex;
	table->SQLquery = SQLquery;
}


SQLTable table;
int main() {
	const string colname[16] = {"lastname", "firstname", "ID", "salary", "age"};
	const DATATYPE coltype[5] = {STRING, STRING, STRING, INT, INT};
	create_table(&table, colname, coltype, 5);
	
	int N, Q;
	scanf("%d", &N);
	
	table.rowsize = N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++)
			scanf("%s", &(table.data[i]).fields[j].d.str);
		for (int j = 3; j < 5; j++)
			scanf("%d", &(table.data[i]).fields[j].d.num);
	}
	scanf("%d", &Q);
	while (getchar() != '\n');
	
	char cmd[1024];
	for (int i = 0; i < Q; i++) {
		fgets(cmd, 1024, stdin);
		table.SQLquery(&table, cmd);
	}
	return 0;
}
/*
4
Liu Pangfeng A123456789 80000 40
Wu Janet B123456789 79999 30
Liu Kevin C123456789 0 10
Liu Eric C123456789 0 7
2
select lastname firstname ID where salary > 1000
select firstname lastname salary lastname where lastname == Liu
*/
