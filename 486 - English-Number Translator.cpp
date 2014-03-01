#include<stdio.h>
#include<string.h>
#define MAX 1000
char table[32][10] = {"negative", "zero", "one", "two", "three",
"four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
"twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
"eighteen", "nineteen","twenty", "thirty", "forty", "fifty", "sixty",
"seventy", "eighty", "ninety", "hundred", "thousand", "million"};
int number[32] = {-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
30,40,50,60,70,80,90,100,1000,1000000};

int recursion(int x[] , int low , int upp , int m)
{
  if(low == upp)
  return x[low];
  if(low > upp)
  {
  if(m == 1)
  return 1;
  else
  return 0;
  }
  int i , max = 0 , loc;
  for(i=low;i<=upp;i++)
  if(x[i] > max)
  {
  max = x[i];
  loc = i;
  }
  return max*recursion(x,low,loc-1,1) + recursion(x,loc+1,upp,2);
}

int main()
{
  char line[MAX] , part[MAX];
  int num[MAX];
  char *str;
  int len,i,size;
  while(gets(line)!=NULL)
  {
  size = 0;
  for(str=line;sscanf(str,"%s%n",part,&len)==1;str+=len)
  {
  for(i=0;i<32;i++)
  if(!strcmp(part,table[i]))
  {
  num[size++] = number[i];
  break;
  }
  }
  if(num[0] == -1)
  printf("-%d\n",recursion(num,1,size-1,0));
  else
  printf("%d\n",recursion(num,0,size-1,0));
  }
  return 0;
}
