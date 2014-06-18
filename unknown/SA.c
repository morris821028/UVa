#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxL 1000002
void Merge(int, int, int);
void MergeSort(int, int);

struct xy_change_rank{
	int index, v;
}Data[MaxL], X[MaxL];
char S[MaxL], Ss[MaxL], base_rank[256];
int s2[25]={1}, rank[MaxL], SA[MaxL], L;

void MergeSort(int l, int h) {
    if(l < h) {
        int m = (l+h)/2;
        MergeSort(l  ,m);
        MergeSort(m+1,h);
        Merge(l,m,h);
    }
}
void Merge(int l, int m, int h) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0;
    while(In1 <= m && In2 <= h)
        if(Data[In1].v <= Data[In2].v)
             X[Top++] = Data[In1++];
       else  X[Top++] = Data[In2++];
    while(In1 <= m)   X[Top++] = Data[In1++];
    while(In2 <= h)   X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++)
        Data[b] = X[a];
}
void Doubling_Algorithm() {
    int a, b, C, temp;
    int Queue[MaxL] = {-1};
    char Mask[MaxL];

    L=strlen(S);
    for(a = 0; a < L; a++)
        rank[a] = base_rank[S[a]],
        Mask[a] = 0,
        Data[a].v = rank[a],
        Data[a].index = a;

    MergeSort(0, L-1);
    for(a = 0; s2[a] < L; a++) {
        temp = Data[0].v, C = 1;
        for(b = 0; b < L; b++) {
            if(Data[b].v != temp || Mask[b] == 1)
                Queue[C] = b-1, temp = Data[b].v, C++, Mask[b] = 1;
            rank[Data[b].index] = C;
        }
        Queue[C] = L-1, C++;
        for(b = 0; b < L; b++) {
            if(Data[b].index + s2[a] < L)
                Data[b].v = rank[Data[b].index + s2[a]];
            else Data[b].v = 0;
        }
        for(b = 1; b < C; b++)
            MergeSort(Queue[b-1]+1, Queue[b]);
    }
    for(a = 0; a < L; a++)
        SA[a] = Data[a].index;
}

main() {
    int a, N;
    for(a=1;a<25;a++)   s2[a] = s2[a-1]*2;
    for(a='a';a<='z';a++)   base_rank[a] = a-'a'+1;
    while(scanf("%d", &N) == 1) {
       // scanf("%s", S);
        Doubling_Algorithm();
    }
    return 0;
}
