#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
struct Trie {
int n, label, dist;
int link[2];
} Node[1048576];
int TrieSize;
int insertTrie(const char* str) {
static int i, idx;
for(i = idx = 0; str[i]; i++) {
if(Node[idx].link[str[i]-'0'] == 0) {
TrieSize++;
memset(&Node[TrieSize], 0, sizeof(Node[0]));
Node[TrieSize].label = TrieSize;
Node[TrieSize].dist = i + 1;
Node[idx].link[str[i]-'0'] = TrieSize;
}
idx = Node[idx].link[str[i]-'0'];
}
Node[idx].n ++;
return Node[idx].label;
}
void binaryIP(const int ip[], char buf[]) {
int idx = 0;
for (int i = 0; i < 4; i++) {
for (int j = 8 - 1; j >= 0; j--) {
buf[idx++] = '0' + ((ip[i]>>j)&1);
}
}
buf[idx] = '\0';
}
void getAllLCP(char buf[]) {
int idx = 0, bidx = 0;
do {
int branch = 0, next = 0, c = 0;
for (int i = 0; i < 2; i++) {
if (Node[idx].link[i]) {
branch++, next = Node[idx].link[i], c = i;
}
}
if (branch != 1)
break;
buf[bidx++] = c + '0', idx = next;
} while (true);
buf[bidx] = '\0';
}
int main() {
int n, ip[4];
char bip[128];
while (scanf("%d", &n) == 1) {
TrieSize = 0;
memset(&Node[0], 0, sizeof(Node[0]));
for (int i = 0; i < n; i++) {
scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
binaryIP(ip, bip);
insertTrie(bip);
}
getAllLCP(bip);
int m = (int)strlen(bip);
for (int i = 0; i < 4; i++) {
int bb = 0;
for (int j = 8 - 1; j >= 0; j--) {
if (i * 8 + 7 - j < m) {
if (bip[i * 8 + 7 - j] == '1') {
bb |= 1<<j;
}
}
}
printf("%d%c", bb, i == 3 ? '\n' : '.');
}
for (int i = 0; i < 4; i++) {
int bb = 0;
for (int j = 8 - 1; j >= 0; j--) {
if (i * 8 + 7 - j < m) {
bb |= 1<<j;
}
}
printf("%d%c", bb, i == 3 ? '\n' : '.');
}
}
return 0;
}
/*
3
194.85.160.177
194.85.160.183
194.85.160.178
*/
using namespace std;

struct Trie {
    int n, label, dist;
    int link[2];
} Node[1048576];
int TrieSize;
int insertTrie(const char* str) {
	static int i, idx;
	for(i = idx = 0; str[i]; i++) {
		if(Node[idx].link[str[i]-'0'] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[TrieSize].label = TrieSize;
			Node[TrieSize].dist = i + 1;
			Node[idx].link[str[i]-'0'] = TrieSize;
		}
		idx = Node[idx].link[str[i]-'0'];
	}
	Node[idx].n ++;
	return Node[idx].label;
}

void binaryIP(const int ip[], char buf[]) {
    int idx = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 8 - 1; j >= 0; j--) {
            buf[idx++] = '0' + ((ip[i]>>j)&1);
        }
    }
    buf[idx] = '\0';
}
void getAllLCP(char buf[]) {
    int idx = 0, bidx = 0;
    do {
        int branch = 0, next = 0, c = 0;
        for (int i = 0; i < 2; i++) {
            if (Node[idx].link[i]) {
                branch++, next = Node[idx].link[i], c = i;
            }
        }
        if (branch != 1)
            break;
        buf[bidx++] = c + '0', idx = next;
    } while (true);
    buf[bidx] = '\0';
}
int main() {
    int n, ip[4];
    char bip[128];
    while (scanf("%d", &n) == 1) {
        TrieSize = 0;
        memset(&Node[0], 0, sizeof(Node[0]));
        for (int i = 0; i < n; i++) {
            scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
            binaryIP(ip, bip);
            insertTrie(bip);
        }
        getAllLCP(bip);
        int m = (int)strlen(bip);
        for (int i = 0; i < 4; i++) {
            int bb = 0;
            for (int j = 8 - 1; j >= 0; j--) {
                if (i * 8 + 7 - j < m) {
                    if (bip[i * 8 + 7 - j] == '1') {
                        bb |= 1<<j;
                    }
                }
            }
            printf("%d%c", bb, i == 3 ? '\n' : '.');
        }
        for (int i = 0; i < 4; i++) {
            int bb = 0;
            for (int j = 8 - 1; j >= 0; j--) {
                if (i * 8 + 7 - j < m) {
                    bb |= 1<<j;
                }
            }
            printf("%d%c", bb, i == 3 ? '\n' : '.');
        }
    }
    return 0;
}
/*
 3
 194.85.160.177
 194.85.160.183
 194.85.160.178
*/
