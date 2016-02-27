#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int eratosthenes(int lastNumber) {   // initialize   
char* isPrime = new char[lastNumber+1];   
for (int i = 0; i <= lastNumber; i++)     
isPrime[i] = 1;   // find all non-primes   
for (long long i = 2; i*i <= lastNumber; i++)     
if (isPrime[i])       
for (long long j = i*i; j <= lastNumber; j += i)         
isPrime[j] = 0;   // sieve is complete, count primes  
 int found = 0;   for (int i = 2; i <= lastNumber; i++)     
 found += isPrime[i];   delete[] isPrime;   r
 return found; 
}

int main() {
	printf("%d\n", eratosthenes(1, 1000000000));
	return 0;
}

