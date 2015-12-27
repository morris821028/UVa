#include <stdio.h>
#include <string.h>

struct string_count
{
	char seen[80];
	int count;
};

int compare_and_add(char *string, struct string_count strings[]);
void sort(struct string_count strings[]);
void print(struct string_count strings[]);

int main()
{
	struct string_count strings[1001];
	for( int i=0 ; i<1001 ; i++ )
		strings[i].count = 0;

	char tmp[101];
	while(scanf("%s",tmp)==1)
		printf("%d\n",compare_and_add(tmp,strings));

	print(strings);
	sort(strings);
	print(strings);

	return 0;
}
