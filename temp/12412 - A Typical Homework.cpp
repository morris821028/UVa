// WTF > Try adding 1e-5 to all floating point values as you print them.
#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define eps 1e-5
class Student {
	public:
	string SID, name;
	int CID, score[4];
	Student(int c, int d[], string a = "", string b = "") {
		SID = a, name = b;
		CID = c;
		for (int i = 0; i < 4; i++)
			score[i] = d[i];
	}
	void print() {
		printf("%s %d %s %d %d %d %d %d %.2lf\n", 
			SID.c_str(), CID, name.c_str(),
				score[0], score[1], score[2], score[3], getTotal(), getAvg());
	}
	int getTotal() {
		return score[0] + score[1] + score[2] + score[3];
	}
	double getAvg() {
		return (score[0] + score[1] + score[2] + score[3]) / 4.0 + eps;
	}
};
class SPMS {
	public:
	map<string, int> R_SID;
	vector<Student> students;
	void printMainMenu() {
		puts("Welcome to Student Performance Management System (SPMS).\n");
		puts("1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n");
	}
	void addStudent() {
		char SID[128], name[128];
		int CID, score[4];
		while (true) {
			puts("Please enter the SID, CID, name and four scores. Enter 0 to finish.");
			scanf("%s", SID);
			if (!strcmp(SID, "0"))
				return;
			scanf("%d %s", &CID, name);
			for (int i = 0; i < 4; i++)	scanf("%d", &score[i]);
			
			if (R_SID[SID]) {
				puts("Duplicated SID.");
			} else {
				R_SID[SID]++;
				Student u(CID, score, SID, name);
				students.push_back(u);
			}
		}
	}
	void removeStudent() {
		char s[128];
		while (true) {
			puts("Please enter SID or name. Enter 0 to finish.");
			scanf("%s", s);
			if (!strcmp(s, "0"))
				return;
			int cnt = 0;
			for (vector<Student>::iterator it = students.begin();
				it != students.end(); ) {
				if (it->SID == s || it->name == s) {
					cnt++;
					R_SID[it->SID]--;
					it = students.erase(it);
				} else {
					it++;
				}
			}
			printf("%d student(s) removed.\n", cnt);
		}
	}
	int getRank(Student u) {
		int ret = 1;
		for (int i = 0; i < students.size(); i++)
			if (students[i].getTotal() > u.getTotal())
				ret++;
		return ret;
	}
	void queryStudent() {
		char s[128];
		while (true) {
			puts("Please enter SID or name. Enter 0 to finish.");
			scanf("%s", s);
			if (!strcmp(s, "0"))
				return;
			for (vector<Student>::iterator it = students.begin();
				it != students.end(); it++) {
				if (it->SID == s || it->name == s) {
					printf("%d ", getRank(*it));
					it->print();
				}
			}
		}
	}
	void printRankList() {
		puts("Showing the ranklist hurts students' self-esteem. Don't do that.");
	}
	void printStatistics() {
		puts("Please enter class ID, 0 for the whole statistics.");
		int CID;
		scanf("%d", &CID);
		
		int pass[4] = {}, fail[4] = {}; // subject
		int sum[4] = {}, n = 0;
		int sumtable[5] = {};
		vector<int> table; // student
		table.resize(students.size(), 0); 
		for (int i = 0; i < students.size(); i++) {
			if (CID && CID != students[i].CID)
				continue;
			n++;
			for (int j = 0; j < 4; j++) {
				sum[j] += students[i].score[j];
				if (students[i].score[j] >= 60) {
					pass[j]++;
					table[i]++;
				} else {
					fail[j]++;
				}
			}
			sumtable[table[i]]++;
		}
		
		for (int i = 3; i >= 1; i--)
			sumtable[i] += sumtable[i+1];

		printf("Chinese\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n",
			(double) sum[0] / n + eps, pass[0], fail[0]);
		printf("Mathematics\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n",
			(double) sum[1] / n + eps, pass[1], fail[1]);
		printf("English\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n",
			(double) sum[2] / n + eps, pass[2], fail[2]);
		printf("Programming\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n",
			(double) sum[3] / n + eps, pass[3], fail[3]);
		printf("Overall:\nNumber of students who passed all subjects: %d\nNumber of students who passed 3 or more subjects: %d\nNumber of students who passed 2 or more subjects: %d\nNumber of students who passed 1 or more subjects: %d\nNumber of students who failed all subjects: %d\n\n",
			sumtable[4], sumtable[3], sumtable[2], sumtable[1], sumtable[0]);
	}
} spms;
int main() {
	int cmd;
	while (true) {
		spms.printMainMenu();	
		scanf("%d", &cmd);
		if (cmd == 0)
			return 0;
		if (cmd == 1)
			spms.addStudent();
		if (cmd == 2)
			spms.removeStudent();
		if (cmd == 3)
			spms.queryStudent();
		if (cmd == 4)
			spms.printRankList();
		if (cmd == 5)
			spms.printStatistics();
	}	
	return 0;
}
/*
1
0011223344 1 John 79 98 91 100
0022334455 1 Tom 59 72 60 81
0011223344 2 Alice 100 100 100 100
2423475629 2 John 60 80 30 99
0
3
0022334455
John
0
5
1
2
*/
