#include<stdio.h>
#include<stdlib.h>

char Num[10][5] = {
    {4,3,0,3,4},/*0*/
    {0,1,0,1,0},/*1*/
    {4,1,4,2,4},/*2*/
    {4,1,4,1,4},/*3*/
    {0,3,4,1,0},/*4*/
    {4,2,4,1,4},/*5*/
    {4,2,4,3,4},/*6*/
    {4,1,0,1,0},/*7*/
    {4,3,4,3,4},/*8*/
    {4,3,4,1,4}/*9*/
                    };
char type[17][6] = {
    {"    "},{"   |"},{"|   "},{"|  |"},{" -- "},
    {"|\\ |"},{"| \\|"},{"| \\ "},{"  - "},{"|/\\|"},
    {"| / "},{" -\\ "},{" \\/ "},{" /\\ "},{"  / "},
    {" /  "},{"|\\/|"}
    };
char ALetter[26][5] = {
    {4,3,4,3,0},{4,3,4,3,4},{4,2,0,2,4},{4,3,0,3,4},{4,2,4,2,4},/*ABCDE*/
    {4,2,4,2,0},{4,2,4,3,4},{0,3,4,3,0},{0,1,0,1,0},{0,1,0,3,4},/*FGHIJ*/
    {0,10,4,3,0},{0,2,0,2,4},{0,16,0,3,0},{0,5,0,6,0},{4,3,0,3,4},/*KLMNO*/
    {4,3,4,2,0},{4,3,0,3,11},{4,3,4,7,0},{4,2,4,1,4},{4,3,0,1,4},/*PQRST*/
    {0,3,0,3,4},{0,3,0,12,0},{0,3,0,9,0},{0,12,0,13,0},{0,3,4,1,4},/*UVWXY*/
    {4,14,0,15,4}/*z*/
                    };
void PrintALetter(char s[], int n) {
    int a, b, c, tn, t;
    for(a = 0; a < 5; a++) {
        if(a == 0 || a == 2 || a == 4) tn = 1;
        else tn = n;
        for(t = 0; t < tn; t++) {
            for(b = 0; s[b]; b++) {
                if(s[b] == ' ') {putchar(' ');continue;}
                printf("%c", type[ALetter[s[b] - 'A'][a]][0]);
                if(a == 0 || a == 2 || a == 4) {
                    for(c = 0; c < n; c++)
                        printf("%c", type[ALetter[s[b] - 'A'][a]][1]);
                    for(c = 0; c < n; c++)
                        printf("%c", type[ALetter[s[b] - 'A'][a]][2]);
                }
                else if(a == 1 || s[b] == 'V'){
                    for(c = 0; c < t; c++)    putchar(' ');
                    putchar(type[ALetter[s[b] - 'A'][a]][1]);
                    for(; c < n-1; c++) putchar(' ');
                    for(c = 0; c < n-t-1; c++)    putchar(' ');
                    putchar(type[ALetter[s[b] - 'A'][a]][2]);
                    for(; c < n-1; c++) putchar(' ');
                }
                else {
                    for(c = 0; c < n-t-1; c++)    putchar(' ');
                    putchar(type[ALetter[s[b] - 'A'][a]][1]);
                    for(; c < n-1; c++) putchar(' ');
                    for(c = 0; c < t; c++)    putchar(' ');
                    putchar(type[ALetter[s[b] - 'A'][a]][2]);
                    for(; c < n-1; c++) putchar(' ');
                }
                printf("%c", type[ALetter[s[b] - 'A'][a]][3]);
                if(s[b+1] != '\0') putchar(' ');
            }
            puts("");
        }
    }
}           
void PrintNum(char s[], int n) {
    int a, b, c, tn;
    for(a = 0; a < 5; a++) {
        if(a == 0 || a == 2 || a == 4) tn = 1;
        else tn = n;
        while(tn--) {
            for(b = 0; s[b]; b++) {
                if(s[b] == ' ') {putchar(' ');continue;}
                printf("%c", type[Num[s[b] - '0'][a]][0]);
                for(c = 0; c < n; c++)
                    printf("%c%c", type[Num[s[b] - '0'][a]][1], type[Num[s[b] - '0'][a]][2]);
                printf("%c", type[Num[s[b] - '0'][a]][3]);
                if(s[b+1] != '\0') putchar(' ');
            }
            puts("");
        }
    }
}
main() {
    int n = 2;
    PrintNum("0123456789", n);
        PrintALetter("ABCDE", n);
        PrintALetter("FGHIJ", n);
        PrintALetter("KLMNO", n);
        PrintALetter("PQRST", n);
        PrintALetter("UVWXY", n);
        PrintALetter("Z", n);
    system("pause");
    return 0;
}
