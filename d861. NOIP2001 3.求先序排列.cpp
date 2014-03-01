#include<stdio.h>
#include<string.h>
int pos_tail, top;
char pos[100], in[100], pre[100];
void print(int from, int end) {
    int i;
    if(from > end) return;
    else {
    	pos_tail--;
        for(i = 0; in[i] != '\0'; i++)
            if(pos[pos_tail] == in[i]) {                     
            	print(i+1, end);
                print(from, i-1);
                pre[top++] = in[i];
                break;
            }
    }
}
main() {
	while(scanf("%s %s",in, pos) == 2) {
        pos_tail = strlen(in), top = 0;
        print(0, strlen(in)-1);
        int i;
        for(i = top-1; i >= 0; i--)
            printf("%c",pre[i]);
        puts("");
    }
   return 0;
}
