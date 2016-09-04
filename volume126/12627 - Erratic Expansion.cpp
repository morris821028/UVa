#include <iostream>
using namespace std;

long long k, a, b, tot;
long long idx[31] = {1};

long long solve(long long k, long long i){
    if (!i) return 0;
    if (!k) return 1;
    if (i > (1LL << k-1))
        return (solve(k-1, i-(1LL << k-1)) + 2 * idx[k-1]);
    return 2 * solve(k-1, i);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int cas, n = 0;
    cin >> cas;
    for (int i = 1; i < 30; ++i)
        idx[i] = 3 * idx[i-1];
    while (++n <= cas){
        cin >> k >> a >> b;
        tot = solve(k, b) - solve(k, a-1);
        cout << "Case " << n  << ": "<< tot << '\n';
    }
    return 0;
}
