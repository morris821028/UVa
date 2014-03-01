#include <stdio.h>
char sor[60];
int n, j, idx, M, E, p, x, z, y;
char * k;
int main()
{
	scanf("%d",&n);
	gets(sor);
	while(n--)
	{
		j = idx = p = M = E = x = z = y = 0;
		k = gets(sor);
		int symbol1[50] = {0}, symbol2[50] = {0}, symbol3[50] = {0};
		while(*k && (*k == 'M' || *k == 'E' || *k == '?') )
		{
			symbol1[idx] = symbol2[idx] = symbol3[idx] = j;
			if((*k) == 'M') { M = j; symbol1[idx] = -1; }
			if((*k) == 'E') { E = j; symbol2[idx] = -1; }
			k++;
			j++;
			idx++;
		}
		symbol3[idx] = -1;
		if((*k) != '\0' || M + 1 == E)
		{
			puts("no-theorem");
			continue;
		}
		for(j = 0; symbol1[j] != -1 && j < 50; j++)
		{
			if(sor[symbol1[j]] != '?') p = 1;
			x++;
		}
		if(symbol1[j-1] + 1 != M) p = 1;
		for(j = j + 1; symbol2[j] != -1 && j < 50; j++)
		{
			if(sor[symbol2[j]] != '?') p = 1;
			y++;
		}
		if(symbol2[j-1] + 1 != E) p = 1;
		for(j = j + 1; symbol3[j] != -1 && j < 50; j++)
		{
			if(sor[symbol3[j]] != '?') p = 1;
			z++;
		}
		if(p)	puts("no-theorem");
		else {
			if(x + y == z)
				puts("theorem");
			else puts("no-theorem");
		}
	}
	return 0;
}
