#include <iostream>
using namespace std;
main()
{
	int i,t[]={1,2,3};
	do
	{
		for(i=0;i<3;i++)printf("%d",t[i]);
		puts("");
	}while(next_permutation(t,t+3));
	system("pause");
}
