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
	printf("\n--- GRAPH2 ---\n\n");

	// time tracking stuff
	struct timeval tv;
	long start; long end;

	// timing results
	int results[11];

	for (int af=0; af<11; af++) {
		gettimeofday(&tv, NULL);
		start = tv.tv_usec + tv.tv_sec*1000000;

		// -- MEATY CODE --
		// Shared counter_t
		counter_t shared_counter;
		init(&shared_counter, (1 << af)); // (1 << af) == (2^af)

		// Allocate #[threads] threads
		pthread_t thread[4];
		for (int i=0; i<4; i++) {
			myarg_t args;
			args.thread = i; args.c = shared_counter;

			if (pthread_create(&thread[i], NULL, oneMillion, &args) != 0) {
				printf("ERROR!!! :^)");
				exit(1);
			}
		}
		// Join them
		for (int i=0; i<4; i++) {
			pthread_join(thread[i], NULL);
		}

		gettimeofday(&tv, NULL);
		end = tv.tv_usec + tv.tv_sec*1000000;

		printf("Test with approximation factor [%i] complete.\n", (1 << af));

		results[af] = end-start;
	}

	printf("\nResults: ");
	for (int i=0; i<11; i++) {
		if (i != 10) {
			printf("%f, ", results[i]/1000000.0);
		} else {
			printf("%f\n", results[i]/1000000.0);
		}
	}

	return 0;
}
