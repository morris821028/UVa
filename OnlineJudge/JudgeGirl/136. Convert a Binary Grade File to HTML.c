#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[20];
	int id;
	char phone[10];
	float grade[4];
	int birth_year;
	int birth_month;
	int birth_day;
} Student;
Student *stu;

int fsize(FILE *fp) {
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fseek(fp, prev, SEEK_SET);
    return size;
}
int main() {
	char finName[128], foutName[128];
	scanf("%s %s", finName, foutName);
	FILE *fin = fopen(finName, "rb");
	FILE *fout = fopen(foutName, "w");
	int finsize = fsize(fin);
	unsigned char *buf = malloc(sizeof(unsigned char)*finsize);
	fread(buf, 1, finsize, fin);
	stu = (Student *) buf;
	int n = finsize / sizeof(Student);
	fprintf(fout, "<table border=\"1\">\n");
	fprintf(fout, "<tbody>\n");
	for (int i = 0; i < n; i++) {
		fprintf(fout, "<tr>\n");
		fprintf(fout, "<td>%s</td>\n", stu[i].name);
		fprintf(fout, "<td>%d</td>\n", stu[i].id);
		fprintf(fout, "<td>%s</td>\n", stu[i].phone);
		fprintf(fout, "<td>%f, %f, %f, %f</td>\n", stu[i].grade[0], stu[i].grade[1], stu[i].grade[2], stu[i].grade[3]);
		fprintf(fout, "<td>%d, %d, %d</td>\n", stu[i].birth_year, stu[i].birth_month, stu[i].birth_day);
		fprintf(fout, "</tr>\n");
	}
	fprintf(fout, "</tbody>\n");
	fprintf(fout, "</table>\n");
	fclose(fin), fclose(fout);
	free(buf);
	return 0;
}
