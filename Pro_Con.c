#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
int count = 0;
sem_t sem;
void Producer(void);
void Consumer(void);
int main(void) {
	int i=0;
	pthread_t id[2];
	sem_init(&sem, 0, 1);
	pthread_create(&id[0], NULL, (void*)Producer, NULL);
	pthread_create(&id[1], NULL, (void*)Consumer, NULL);
	for(i = 0; i < 2; i++) {
		pthread_join(id[i],NULL);	
	}
	sem_destroy(&sem);
	pthread_exit(NULL);
}

void Producer(void) {
	int i = 0;
	for(i = 0; i < 25;) {
		sem_wait(&sem);
		if(count == 5) {
			sem_post(&sem);
			continue;
		}
		count++;
		printf("\nProducer is :%d\n", count);
		sem_post(&sem);
		i++;
	}
	pthread_exit(NULL);
}

void Consumer(void) {
	int i = 0;
	for(i = 0; i < 25;) {
		sem_wait(&sem);
		if(count == 0) {
			sem_post(&sem);
			continue;
		}
		count--;
		printf("\nConsumer is :%d\n", count);
		sem_post(&sem);
		i++;
	}
	pthread_exit(NULL);
}
