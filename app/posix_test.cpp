#include <iostream>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex_counter;

void*
print_counter(void* id)
{
	for (int i = 0; i < 500; ++i)
	{
		pthread_mutex_lock(&mutex_counter);
		counter++;
		printf("%d\n", counter);
		pthread_mutex_unlock(&mutex_counter);
	}

	pthread_exit(nullptr);
}

int
main(int argc, char const *argv[])
{

	// create and run the threads
	pthread_t threads[2];
	pthread_create(&threads[0], nullptr, print_counter, nullptr);
	pthread_create(&threads[1], nullptr, print_counter, nullptr);

	// wait for the threads to finish
	pthread_join(threads[0], nullptr);
	pthread_join(threads[1], nullptr);

	return 0;
}
