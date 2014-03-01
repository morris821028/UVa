#include <stdio.h>

void mergeSort(int, int[]);
void merge(int, int, int[], int[], int[]);

int main() {
	char ch;
	int i, n;
	int numbers[500000];
	
	n = 0;
	while(ch = getchar())
		if(ch == -1)
			break;
		else if(ch == ' ')
			n++;
		else
			numbers[n] = numbers[n]*10+ch-'0';
	
	mergeSort(n, numbers);
	
	for(i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	
	return 0;
}

void mergeSort(int n, int numbers[]) {
	if(n <= 1)
		return ;

	int index, r, l, m;
	
	m = n/2;
	
	int left[m], right[n-m];

	index = r = l = 0;
	while(index < m)
		left[l++] = numbers[index++];
	while(index < n)
		right[r++] = numbers[index++];

	mergeSort(l, left);
	mergeSort(r, right);
	merge(l, r, left, right, numbers);
}

void merge(int l_max, int r_max, int left[], int right[], int numbers[]) {
	int index, l, r;

	index = l = r = 0;
	while(l < l_max&&r < r_max)
		if(left[l] < right[r])
			numbers[index++] = left[l++];
		else
			numbers[index++] = right[r++];

	while(l < l_max)
		numbers[index++] = left[l++];
	while(r < r_max)
		numbers[index++] = right[r++];
}

