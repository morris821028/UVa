#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	char servant[8][16] = {"Saber", "Lancer",
		"Archer", "Rider", "Caster", "Assassin", 
		"Berserker"};
	char c;
	int cnt[8] = {}, mx = 0, assign = 0;
	while ((c = getchar()) != EOF) {
		if ('a' <= c && c <= 'z')
			cnt[(c - 'a')%7]++;
		if ('A' <= c && c <= 'Z')
			cnt[(c - 'A')%7]++;
	}
	for (int i = 0; i < 7; i++) {
		if (cnt[i] > mx)
			mx = cnt[i], assign = i;
	}
	puts(servant[assign]);
	return 0;
}
