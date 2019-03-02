#include <bits/stdc++.h>
using namespace std;

const unordered_map<string, int> table = {
	{"zero", 0}, {"um", 1}, {"dois", 2}, {"tres", 3}, {"quatro", 4}, {"cinco", 5}, {"seis", 6}, {"sete", 7}, {"oito", 8}, {"nove", 9},
	{"dez", 10}, {"onze", 11}, {"doze", 12}, {"treze", 13}, {"catorze", 14}, {"quatorze", 14}, {"quinze", 15}, {"dezasseis", 16},
	{"dezesseis", 16}, {"dezassete", 17}, {"dezessete", 17}, {"dezoito", 18}, {"dezanove", 19}, {"dezenove", 19}, {"vinte", 20},
	{"trinta", 30}, {"quarenta", 40}, {"cinquenta", 50}, {"sessenta", 60}, {"setenta", 70}, {"oitenta", 80}, {"noventa", 90},
	{"cem", 100}, {"cento", 100}, {"duzentos", 200}, {"trezentos", 300}, {"quatrocentos", 400}, {"quinhentos", 500},
	{"seiscentos", 600}, {"setecentos", 700}, {"oitocentos", 800}, {"novecentos", 900}, {"mil", 1000},
	{"milhao", 1000000}, {"milhoes", 1000000}, {"biliao", 1000000000}, {"bilioes", 1000000000},
	{"bilhao", 1000000000}, {"bilhoes", 1000000000}
};
int main() {
	int testcase;
	scanf("%d", &testcase);
	printf("%d\n", testcase);
	while (getchar() != '\n');
	while (testcase--) {
		char buf[65536];
		fgets(buf, 65536, stdin);
		char *token = strtok(buf, " \n");
		int64_t ret = 0;
		queue<int> Q;
		while (token) {
			auto it = table.find(token);
			if (it == table.end()) {
				token = strtok(NULL, " ");
				continue;
			}
			int64_t s = it->second;
			if (!Q.empty() && Q.front() < s) {
				int64_t b = 0;
				while (!Q.empty())
					b += Q.front(), Q.pop();
				ret += b * s;
			} else {
				Q.push(s);
			}
			token = strtok(NULL, " \n");
		}
		while (!Q.empty())
			ret += Q.front(), Q.pop();
		printf("%lld\n", ret);
	}
	return 0;
}
/*
12
quatro
vinte e tres
cento e vinte e sete
mil
*/
