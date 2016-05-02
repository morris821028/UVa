all:
	gcc -std=c99 -O2 -fopenmp -lpthread prefixsum-openmp.c secret.c -o prefixsum-openmp
	gcc -std=c99 -O2 -fopenmp -lpthread prefixsum-openmp.c secret.c -S
	gcc -std=c99 -O2 -fopenmp prefixsum-pthread.c secret.c -o prefixsum-pthread
