#include <stdio.h>

struct Student {
	char name;
	int id;
	int height;
};

typedef struct Student Student;

void sort(int, int, Student[], int(Student, Student));
int cmpId(Student, Student);
int cmpHt(Student, Student);
void swap(Student*, Student*);

int main() {
	int i, n, m;
	Student student[6];
	
	while(scanf("%d %d\n", &n, &m) == 2) {
		for(i = 0; i < 6; i++)
			scanf("%c %d %d\n", &student[i].name, &student[i].id, &student[i].height);
		
		if(n%2 == 0)
			sort(0, 6, student, cmpHt);
		else
			sort(0, 6, student, cmpId);
		
		for(i = 0; i < 6; i++)
			printf("%c %d %d\n", student[i].name, student[i].id, student[i].height);
		printf("\n");
	}
	
	return 0;
}

void sort(int begin, int end, Student stu[], int cmp(Student, Student)) {
	int i, j;
	Student tmp;
	
	for(i = end-1; i >= begin; i--)
		for(j = begin; j < i; j++)
			if(cmp(stu[j], stu[j+1]) == 1)
				swap(&stu[j], &stu[j+1]);
}

int cmpId(Student a, Student b) {
	return a.id > b.id;
}

int cmpHt(Student a, Student b) {
	return a.height > b.height;
}

void swap(Student *a, Student *b) {
	Student tmp = *a;
	*a = *b;
	*b = tmp;
}

