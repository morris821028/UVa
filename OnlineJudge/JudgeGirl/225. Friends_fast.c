#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

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

#define HSIZE 10007
#define HNODE 1048576
typedef struct HashNode {
	Friends f;
	struct HashNode *next;
} HashNode;
HashNode *hhead[HSIZE], hnodes[HNODE];
int nodesize = 0;
void initHash() {
	memset(hhead, 0, sizeof(hhead));
	nodesize = 0;
}
int insertHash(Friends f) {
	unsigned int hidx = hash(f)%HSIZE;
	for (HashNode *p = hhead[hidx]; p != NULL; p = p->next) {
		if (memcmp(&f, &(p->f), sizeof(Friends)) == 0)
			return 0;
	}
	HashNode s = {f, NULL};
	hnodes[nodesize] = s;
	hnodes[nodesize].next = hhead[hidx];
	hhead[hidx] = &hnodes[nodesize];
	nodesize++;
	return 1;
}
int countHash(Friends f) {
	unsigned int hidx = hash(f)%HSIZE;
	for (HashNode *p = hhead[hidx]; p != NULL; p = p->next) {
		if (memcmp(&f, &(p->f), sizeof(Friends)) == 0)
			return 1;
	}
	return 0;
}

#define MAXCHAR 52
#define toIndex(c) (islower(c) ? c - 'a' : c - 'A' + 26)
#define toChar(c) (islower(c) ? c + 'a' : c - 26 + 'A')
#define TNODE 1048576
typedef struct TrieNode {
	int id;
	struct TrieNode *next[MAXCHAR];
} TrieNode;

TrieNode *trieroot, tnodes[TNODE];
int tnodesize;
TrieNode* newTrieNode() {
	assert(tnodesize < TNODE);
    TrieNode *p = &tnodes[tnodesize++];
    memset(p->next, 0, sizeof(p->next));
    p->id = -1;
    return p;
}
void initTrie() {
	tnodesize = 0;
	trieroot = newTrieNode();
}
void insertTrie(char *str, int id) {
    TrieNode *p = trieroot;
    for (int idx; *str; str++) {
        idx = toIndex(*str);
        if (p->next[idx] == NULL)
            p->next[idx] = newTrieNode();
        p = p->next[idx];
    }
    p->id = id;
}
int findTrie(char *str) {
	TrieNode *p = trieroot;
    for (int idx; *str; str++) {
        idx = toIndex(*str);
        if (p->next[idx] == NULL)
            return -1;
        p = p->next[idx];
    }
    return p->id;
}

#define MAXN 32767
unsigned char *buf;
int fsize(FILE *fp) {
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fseek(fp, prev, SEEK_SET);
    return size;
}
int main() {
	FILE *fin = fopen("friends", "rb");
	int finsize = fsize(fin);
	buf = malloc(sizeof(unsigned char*)*finsize);
	fread(buf, 1, finsize, fin);
	char *p = buf;
	int P, F;
	P = fetchInt32(&p);
	initTrie();
	for (int i = 0; i < P; i++) {
		Person person;
		person = fetchPerson(&p);
		insertTrie(person.name, person.id);
	}
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
		int x = findTrie(s1);
		int y = findTrie(s2);
		Friends tmp = {x, y};
		int ok = countHash(tmp);
		if (ok)
			puts("yes");
		else
			puts("no");
	}
	free(buf);
	return 0;
}
