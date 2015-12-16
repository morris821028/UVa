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
unsigned int hash(Friends f) {
	unsigned int a = 63689, b = 378551;
	unsigned int value = 0;
	value = value * a + f.id1, a *= b;
	value = value * a + f.id2, a *= b;
	return value;
}
typedef struct Node {
	Friends f;
	struct Node *next;
} HashNode;
#define HSIZE 10007
#define HNODE 1048576
HashNode *head[HSIZE], nodes[HNODE];
int nodesize = 0;
void initHash() {
	memset(head, 0, sizeof(head));
	nodesize = 0;
}
int insertHash(Friends f) {
	unsigned int hidx = hash(f)%HSIZE;
	for (HashNode *p = head[hidx]; p != NULL; p = p->next) {
		if (memcmp(&f, &(p->f), sizeof(Friends)) == 0)
			return 0;
	}
	HashNode s = {f, NULL};
	nodes[nodesize] = s;
	nodes[nodesize].next = head[hidx];
	head[hidx] = &nodes[nodesize];
	nodesize++;
	return 1;
}
int countHash(Friends f) {
	unsigned int hidx = hash(f)%HSIZE;
	for (HashNode *p = head[hidx]; p != NULL; p = p->next) {
		if (memcmp(&f, &(p->f), sizeof(Friends)) == 0)
			return 1;
	}
	return 0;
}

#define MAXFILESIZE 1048576
#define MAXN 32767
char buf[MAXFILESIZE];
Person people[MAXN];
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
	initHash();
	for (int i = 0; i < F; i++) {
		Friends friends;
		friends = fetchFriends(&p);
		insertHash(friends);
		Friends tmp = {friends.id2, friends.id1};
		insertHash(tmp);
	}
	char s1[32], s2[32];
	while (scanf("%s %s", s1, s2) == 2) {
		int x = findID(people, P, s1);
		int y = findID(people, P, s2);
		Friends tmp = {x, y};
		int ok = countHash(tmp);
		if (ok)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
