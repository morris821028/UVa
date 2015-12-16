#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
	unsigned int id;
	char name[32];
} Person;
typedef struct {
    unsigned id1;
    unsigned id2;
} Friends;
int32_t fetchInt32(char **p) {
	int32_t *tp = (int32_t *) *p;
	(*p) += 4;
	return *tp; 
}
Person fetchPerson(char **p) {
	Person *tp = (Person *) *p;
	(*p) += sizeof(Person);
	return *tp; 
}
Friends fetchFriends(char **p) {
	Friends *tp = (Friends *) *p;
	(*p) += sizeof(Friends);
	return *tp; 
}

#define MAXFILESIZE 1048576
#define MAXN 32767
char buf[MAXFILESIZE];
Person people[MAXN];
Friends friends[MAXN];
int findID(Person people[], int n, char s[]) {
	for (int i = 0; i < n; i++) {
		if (!strcmp(people[i].name, s))
			return people[i].id;
	}
	return -1;
}
int main() {
	FILE *fin = fopen("friends", "rb");
	fread(buf, 1, MAXFILESIZE, fin);
	char *p = buf;
	int P, F;
	P = fetchInt32(&p);
	for (int i = 0; i < P; i++)
		people[i] = fetchPerson(&p);
	F = fetchInt32(&p);
	for (int i = 0; i < F; i++)
		friends[i] = fetchFriends(&p);
	char s1[32], s2[32];
	while (scanf("%s %s", s1, s2) == 2) {
		int x = findID(people, P, s1);
		int y = findID(people, P, s2);
		int ok = 0;
		for (int i = 0; i < F; i++) {
			if ((friends[i].id1 == x && friends[i].id2 == y)
				|| (friends[i].id1 == y && friends[i].id2 == x)) {
				ok = 1;
				break;
			}
		}
		if (ok)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}


