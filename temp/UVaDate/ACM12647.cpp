#include<stdio.h>
#include<string>
#include<math.h>
#include<stdlib.h>
#include<set>
#include<bitset>
#include<map>
#include<vector>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<queue>
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define REP(I, N) for (int I = 0; I < (N); ++I)
#define REPP(I, A, B) for (int I = (A); I < (B); ++I)
#define REPC(I, C) for (int I = 0; !(C); ++I)
#define RI(X) scanf("%d", &(X))
#define RII(X, Y) scanf("%d%d", &(X), &(Y))
#define RIII(X, Y, Z) scanf("%d%d%d", &(X), &(Y), &(Z))
#define DRI(X) int (X); scanf("%d", &X)
#define DRII(X, Y) int X, Y; scanf("%d%d", &X, &Y)
#define DRIII(X, Y, Z) int X, Y, Z; scanf("%d%d%d", &X, &Y, &Z)
#define RS(X) scanf("%s", (X))
#define CASET int ___T, case_n = 1; scanf("%d ", &___T); while (___T-- > 0)
#define MP make_pair
#define PB push_back
#define MS0(X) memset((X), 0, sizeof((X)))
#define MS1(X) memset((X), -1, sizeof((X)))
#define LEN(X) strlen(X)
#define F first
#define S second
using namespace std;
#define SIZE 100010
struct Point{
    int x,y;
    Point(int _x=0,int _y=0){x=_x;y=_y;}
    bool operator<(const Point& b)const{return x<b.x||(x==b.x&&y<b.y);}
    void scan(){scanf("%d%d",&x,&y);}
}line[SIZE][2],an[SIZE];
int balloon[SIZE];
struct data{
    Point p;
    int ty,id;
    data(Point _p=Point(),int _ty=0,int _id=0):p(_p),ty(_ty),id(_id){}
    bool operator<(const data& b)const{
        if(p.x==b.p.x){
            if(!ty){
                if(b.ty)return 1;
                return p.y>b.p.y;
            }
            else{
                if(ty==-1){
                    if(b.ty==1)return 1;
                    if(b.ty==0)return 0;
                    return p.y<b.p.y;
                }
                else{
                    if(b.ty!=1)return 0;
                    return p.y<b.p.y;
                }
            }
        }
        return p<b.p;
    }
}d[SIZE*4];
int dn;
int now_x;
struct Mdata{
    int id;
    Mdata(int _id=0):id(_id){}
    double get()const{
        if(id<=0)return -id;
        else{
            return line[id][0].y+(line[id][1].y-line[id][0].y)*1.*(now_x-line[id][0].x)/(line[id][1].x-line[id][0].x);
        }
    }
    bool operator<(const Mdata b)const{
        if(id==b.id)return 0;
        return get()<b.get();
    }
};
set<Mdata>H;
vector<int>e[SIZE];
int bfs[SIZE],v[SIZE];
void go(int x,int y){
    bfs[0]=x;
    v[0]=-1;
    for(int i=0,j=1;i<j;i++){
        x=bfs[i];
        REP(k,SZ(e[x])){
            if(e[x][k]<=0){
                if(v[i]<0)an[-e[x][k]]=Point(balloon[-e[x][k]],y);
                else an[-e[x][k]]=Point(v[i],y);
            }
            else{
                if(v[i]<0){
                    if(line[e[x][k]][0].y>line[e[x][k]][1].y)v[j]=line[e[x][k]][0].x;
                    else v[j]=line[e[x][k]][1].x;
                }
                else v[j]=v[i];
                bfs[j++]=e[x][k];
            }
        }
    }
}
int main(){
    int N,C;
    while(RII(N,C)==2){
        dn=0;
        REP(i,N+1)e[i]=vector<int>();

        REPP(i,1,N+1){
            REP(j,2)
                line[i][j].scan();
            if(line[i][1]<line[i][0])swap(line[i][0],line[i][1]);
            d[dn++]=data(line[i][0],0,i);
            d[dn++]=data(line[i][1],1,i);
        }
        REP(i,C){
            RI(balloon[i]);
            d[dn++]=data(Point(balloon[i]),-1,i);
        }
        sort(d,d+dn);
        REP(i,dn){
            now_x=d[i].p.x;
            if(d[i].ty==0){
                if(line[d[i].id][d[i].ty].y>line[d[i].id][d[i].ty^1].y){
                    set<Mdata>::iterator it=H.lower_bound(Mdata(-line[d[i].id][d[i].ty].y));
                    if(it!=H.end()&&it->id==d[i].id)it++;
                    if(it==H.end())e[0].PB(d[i].id);
                    else e[it->id].PB(d[i].id);
                }
                H.insert(Mdata(d[i].id));
            }
            else if(d[i].ty==1){
                H.erase(Mdata(d[i].id));
                if(line[d[i].id][d[i].ty].y>line[d[i].id][d[i].ty^1].y){
                    set<Mdata>::iterator it=H.lower_bound(Mdata(-line[d[i].id][d[i].ty].y));
                    if(it!=H.end()&&it->id==d[i].id)it++;
                    if(it==H.end())e[0].PB(d[i].id);
                    else e[it->id].PB(d[i].id);
                }
            }
            else{
                set<Mdata>::iterator it=H.lower_bound(Mdata(0));
                if(it==H.end())an[d[i].id]=Point(balloon[d[i].id],0);
                else e[it->id].PB(-d[i].id);
            }
        }
        go(0,0);
        for(int i=1;i<=N;i++){
            if(line[i][0].y==line[i][1].y)go(i,line[i][0].y);
        }
        REP(i,C){
            if(an[i].y==0)printf("%d\n",an[i].x);
            else printf("%d %d\n",an[i].x,an[i].y);
        }
}
return 0;
}
