#include <stdio.h>
#define $ int
#define E return
#define W(...) while(__VA_ARGS__)
#define SF(x) scanf("%d", &x)
#define AC(...) printf("%d %d\n", __VA_ARGS__)
$ G($ W, $ WW) {
    E WW ? G(WW, W%WW) : W;
}
$ M($ W, $ WW) {
    $ A[] = {W, WW};
    E A[W < WW];
}
main() {
    $ W, WW;
    $ (*F[])($,$) = {G,M};
    W(SF(W), ~SF(WW))
    AC((*F)(W, WW), (*(F+1))(W, WW));
}
