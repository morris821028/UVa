#include <stdio.h>

void swap(int*, int*);
int cmp(int, int);
void quickSort(int, int, int[]);

int main() {
	int i, n;
	int numbers[500000];
	
	n = 0;
	while(scanf("%d", &numbers[n]) == 1) n++;
	
	quickSort(0, n-1, numbers);
	
	for(i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	
	return 0;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int cmp(int a, int b) {
	return (a >= b);
}

void quickSort(int left, int right, int numbers[]) {
	int i, j, s;

    if(left < right) {
        s = (left+right)/2;
        i = left;
        j = right+1;

		swap(&numbers[left], &numbers[s]);
        while(1) {
            while(!cmp(numbers[++i], numbers[left])&&i < right);
            while(cmp(numbers[--j], numbers[left])&&j > left);
            if(i >= j)
				break;
            swap(&numbers[i], &numbers[j]);
        }
        swap(&numbers[left], &numbers[j]);

        quickSort(left, j-1, numbers);
        quickSort(j+1, right, numbers);
    }
}

