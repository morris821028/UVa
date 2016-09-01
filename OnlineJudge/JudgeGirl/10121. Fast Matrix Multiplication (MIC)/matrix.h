#define UINT unsigned long 
__attribute__ ((target(mic)))
void multiply(int N, UINT A[][2048], UINT B[][2048], UINT C[][2048]);
