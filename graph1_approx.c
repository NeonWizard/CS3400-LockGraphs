#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#include "cc_approx.h"

typedef struct __myarg_t {
	int thread;
	counter_t c;
} myarg_t;

void *oneMillion(void *arg) {
	myarg_t *m = (myarg_t *) arg;
	int thread = m->thread;
	counter_t *c = &m->c;

	for (int i=0; i<1000000; i++) {
		update(c, thread, 1);
	}

	return NULL;
}

int main() {
	printf("--- GRAPH1 APPROX ---\n\n");

	// time tracking stuff
	struct timeval tv;
	long start; long end;

	// timing results
	int results[4];

	for (int threads=1; threads<5; threads++) {
		gettimeofday(&tv, NULL);
		start = tv.tv_usec + tv.tv_sec*1000000;

		// -- MEATY CODE --
		// Shared counter_t
		counter_t shared_counter;
		init(&shared_counter, 1024);

		// Allocate #[threads] threads
		pthread_t *thread = malloc(sizeof(pthread_t)*threads);
		for (int i=0; i<threads; i++) {
			myarg_t args;
			args.thread = i; args.c = shared_counter;

			if (pthread_create(&thread[i], NULL, oneMillion, &args) != 0) {
				printf("ERROR!!! :^)");
				exit(1);
			}
		}
		// Join them
		for (int i=0; i<threads; i++) {
			pthread_join(thread[i], NULL);
		}

		gettimeofday(&tv, NULL);
		end = tv.tv_usec + tv.tv_sec*1000000;

		printf("Test with %i thread(s) complete.\n", threads);

		results[threads-1] = end-start;
	}

	printf("Results: %f, %f, %f, %f", results[0]/1000000.0, results[1]/1000000.0, results[2]/1000000.0, results[3]/1000000.0);

	return 0;
}
