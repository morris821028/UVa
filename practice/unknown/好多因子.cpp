#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct Prime_data {
    int p, power[33], max;
}P[5200];
struct Backtrack {
    char div[33];
    int next[33];
}B[1601];
int pt = 0;
void P_Sieve() {
    char mark[100000] = {};
    int a, b;
    P[pt++].p = 2;
    for(a = 3; a <= 50000; a += 2)
        if(mark[a] == 0) {
            P[pt++].p = a;
            for(b = 3; a*b <= 50000; b += 2)
                mark[a*b] = 1;
        }
}
void Build() {
    register int a, b;
    register long long t;
    for(a = 0; a < pt; a++) {
        t = P[a].p, b = 1, P[a].power[b] = P[a].p;
        while(t*P[a].p < 2147483647) {
            t *=P[a].p, b++;
            P[a].power[b] = t;
        }
        P[a].max = b;
    }
    for(a = 2; a<= 1600; a++)
        for(b = 1; b <= 32; b++)
            B[a].div[b] = (a%b == 0), B[a].next[b] = a/b;
}
int Min(int a, int b) {
    return (a < b)? a : b;
}
int Calc_Divisors(int N) {
    if(N == 1) return 1;
    register int a, C = 1, t;
    for(a = 0; a < pt && N !=1 && P[a].p*P[a].p <= N; a++)
        if(N%P[a].p == 0) {
            t = 2, N /= P[a].p;
            while(N%P[a].p == 0)
                t++, N /= P[a].p;
            C *= t;
        }
    if(N != 1)    C *= 2;
    return C;
}
int P_Judge(int N) {
    register int a, sq = (int)sqrt(N);
    for(a = 0; a < pt && P[a].p < sq; a++)
        if(N%P[a].p ==0)
            return 0;
    return 1;
}
/*****************************************************************/
int Bdiv[33], Blimit[33], flag = 0, find, Maxdiv;
int U, L, arrange[33], skip, finds;
int check(int guess) {
    if(guess < U) {
        int a = U/guess + (U%guess != 0), b = L/guess;
        if(a < b) {
            int Max = 2, t, tn;
            b = (b-a > 200)? a+200 : b;
            for(; a<=b; a++) {
                tn = Calc_Divisors(guess*a);
                if(tn > Max) Max = tn, t = a;
            }
            return    guess * t;
        }
    }
    return guess;
}
void Backtrack_arrange(int N, int index, int a, int guess) {

    if(guess > finds || skip != 0) return ;
    if(index == N) {
        int C = check(guess);
        if(C == guess && C >= U) {
            if(C < finds) {
                finds = C, flag = 1; /*找到一組成立的*/
           }
        }
        else if(guess < C) {
            skip = C;
        }
        return ;
    }
    for(; a < pt; a++) {
        arrange[index] = P[a].p;
        if(Bdiv[index] <= P[a].max) {
            if((long long)guess*P[a].power[Bdiv[index]] > finds) return;
            Backtrack_arrange(N, index+1, a+1, guess*P[a].power[Bdiv[index]]);
        }
        if(guess > finds || skip != 0) return ;
    }
}
void Backtrack_div(int a, int index, int N, int guess, int L) {
    if(N == 1) {
        Backtrack_arrange(index, 0, 0, 1);
        return ;
    }
    if(guess >= finds || skip != 0) {return ;}
    int b = a;
    for(; a>=2; a--) {
        if(B[N].div[a] == 1) {
            Bdiv[index] = a-1;
            if((long long)guess * P[index].power[Bdiv[index]] > finds) {continue ;}
            Backtrack_div(Min(Blimit[index+1], b-a+1)
            , index+1, B[N].next[a], guess*P[index].power[Bdiv[index]], L);
            if(guess >= finds || skip != 0)
                {return ;}
        }
    }
}
int test(int N, int L) {
    int a;
    for(a = 0; a < 33 && P[a].p <= L; a++)
        Blimit[a] =(int) (log10(L) / log10(P[a].p));

    flag = 0, skip = 0, finds = L;
    Backtrack_div(Blimit[0], 0, N, 1, L);

    if(flag && N > Maxdiv) {
        Maxdiv = N, find = finds;
    }

    if(skip) {
        a = Calc_Divisors(skip);
        return a+1;
    }
    else return N+1;
}

main() {
    P_Sieve();
    Build();
    int a, T, t;
    scanf("%d", &T);
        while(T--) {
            scanf("%d %d", &U, &L);
            Maxdiv = 1, find = L;
            if(L-U <= 100000) {
                for(a = U; a<=L; a++) {
                    t = Calc_Divisors(a);
                    if(t > Maxdiv) Maxdiv = t, find = a;
                }
            }
            else {
                for(a = 3; a <= 1600; a = test(a, L)) ;
            }
            printf("Between %d and %d, %d has a maximum of %d divisors.\n", U, L, find, Maxdiv);
        }
    return 0;
}
/*

100

74793917 104025250

40464784 44814746

77665342 81477574

*/
