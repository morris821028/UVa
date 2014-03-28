#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
int main() {
	vector<string> D;
	char c;
	char token[1024];
	int cnt = 0;
	while(c = getchar()) {
		if(c == '0')
			break;
		else {
			if((c <= 'z' && c >= 'a') || (c >= 'A' && c <= 'Z')) {
				token[cnt++] = c;
			} else {
				if(cnt > 0) {
					token[cnt] = '\0';
					string str = token;
					int findf = 0;
					for(int i = D.size()-1; i >= 0; i--) {
						if(str == D[i]) {
							printf("%d", D.size() - i);
							string tmp = str;
							for(int j = i+1; j < D.size(); j++)
								D[j-1] = D[j];
							D[D.size()-1] = tmp;
							findf = 1;
							break;
						}
					}
					if(!findf) {
						printf("%s", token);
						D.push_back(token);
					}
					cnt = 0;
					putchar(c);
				} else {
					putchar(c);
				}
			}
		}
	}
	return 0;
}
/*
During the journey John asked his teacher for permission
to go off by himself so that he could buy something he
really needed. By all means the teacher Steve let him go,
for he wanted to sit down and relax his aching feet.
Twenty minutes passed easily, but there was still no
sign of John. So the teacher started to look for him. He
asked a passer-by Jane there whether she saw a little boy
in a blue suit or not, and she just shook her head. As
the teacher was feeling helpless and becoming worried, he
saw John coming toward him, wearing a toy suit and holding
a space gun in his hands.
John told his teacher later that his brother who was a
soldier and loved our country best influenced what he had
done.
0
*/
