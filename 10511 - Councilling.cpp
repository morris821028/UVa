#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>
#include <iostream>
#include <sstream>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[500005];
int e, head[5000], dis[5000], prev[5000], record[5000];
void addEdge(int x, int y, int v) {
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = 0;
    edge[e].next = head[y], head[y] = e++;
}
int maxflow(int s, int t) {
    int flow = 0;
    int i, j, x, y;
    while(1) {
        memset(dis, 0, sizeof(dis));
        dis[s] =  0xffff; // oo
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            x = Q.front();
            Q.pop();
            for(i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if(dis[y] == 0 && edge[i].v > 0) {
                    prev[y] = x, record[y] = i;
                    dis[y] = min(dis[x], edge[i].v);
                    Q.push(y);
                }
            }
            if(dis[t])  break;
        }
        if(dis[t] == 0) break;
        flow += dis[t];
        for(x = t; x != s; x = prev[x]) {
            int ri = record[x];
            edge[ri].v -= dis[t];
            edge[ri^1].v += dis[t];
        }
    }
    return flow;
}
char s[1005][100], buf[105];
string pstr[5000], cstr[5000], mstr[5000];
int main() {
    int t;
    scanf("%d", &t);
    while(getchar() != '\n');
    while(getchar() != '\n');
    int i, j;
    while(t--) {
        int n = 0;
        map<string, int> party, club, man;
        int pz, cz, mz;
        pz = 0, cz = 0, mz = 0;
        while(gets(s[n]) && s[n][0]) {
            int x = 0, idx = 0;
            for(i = 0; s[n][i]; ) {
                while(s[n][i] == ' ')   i++;
                idx = 0;
                while(s[n][i] && s[n][i] != ' ')
                    buf[idx++] = s[n][i++];
                buf[idx] = '\0';
                if(x == 0) {
                    man[buf] = ++mz;
                    mstr[mz] = buf;
                } else if(x == 1) {
                    if(party.find(buf) == party.end()) {
                        party[buf] = ++pz;
                        pstr[pz] = buf;
                    }
                } else {
                    if(club.find(buf) == club.end()) {
                        club[buf] = ++cz;
                        cstr[cz] = buf;
                    }
                }
                x++;
            }
            n++;
        }
        //<maxflow>
        e = 0;
        memset(head, -1, sizeof(head));
        //</maxflow>
        int manN, clubN, partyN;
        for(j = 0; j < n; j++) {
            int x = 0, idx = 0;
            for(i = 0; s[j][i]; ) {
                while(s[j][i] == ' ')   i++;
                idx = 0;
                while(s[j][i] && s[j][i] != ' ')
                    buf[idx++] = s[j][i++];
                buf[idx] = '\0';
                if(x == 0) {
                    manN = man[buf];
                } else if(x == 1) {
                    partyN = party[buf];
                    addEdge(cz+manN, cz+mz+partyN, 1);
                } else {
                    clubN = club[buf];
                    addEdge(clubN, cz+manN, 1);
                }
                x++;
            }
        }
        for(i = 1; i <= club.size(); i++)
            addEdge(0, i, 1);
        int source = 0, sink = cz+mz+pz+1;
        for(i = 1; i <= pz; i++)
            addEdge(cz+mz+i, sink, (cz-1)/2);
        int f = maxflow(source, sink);
        if(f != cz) {
            puts("Impossible.");
        } else {
            for(i = 1; i <= cz; i++) {
                for(j = head[i]; j != -1; j = edge[j].next) {
                    if(edge[j].v == 0) {
                        printf("%s %s\n", mstr[edge[j].y-cz].c_str(), cstr[edge[j].x].c_str());
                        break;
                    }
                }
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
/*
source(0) - club - people - party - sink
2

fred dinosaur jets jetsons
john rhinocerous jets rockets
mary rhinocerous jetsons rockets
ruth platypus rockets

fred dinosaur jets jetsons
john rhinocerous jets rockets
mary rhinocerous jetsons rockets
ruth platypus rockets
*/
