void init(int len[3]) {
    len[0] = len[1] = len[2] = 0;
}
void add(int len[3], int i) {
    len[2] += i;
    len[1] += len[2]/12, len[2] %= 12;
    len[0] += len[1]/3, len[1] %= 3;
}
void sum(int lena[3], int lenb[3], int lenc[3]) {
    lenc[2] = lena[2] + lenb[2];
    lenc[1] = lena[1] + lenb[1] + lenc[2]/12, lenc[2] %= 12;
    lenc[0] = lena[0] + lenb[0] + lenc[1]/3, lenc[1] %= 3;
}
void diff(int lena[3], int lenb[3], int lenc[3]) {
    lenc[2] = lena[2] - lenb[2];
    lenc[1] = lena[1] - lenb[1] - (lenc[2] < 0);
    if (lenc[2] < 0) lenc[2] += 12;
    lenc[0] = lena[0] - lenb[0] - (lenc[1] < 0);
    if (lenc[1] < 0) lenc[1] += 3;
}
