#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include "ll.h"

typedef struct __myarg_t {
	int inserts;
	list_t *L;
} myarg_t;

void *varInsert(void *arg) {
	myarg_t *m = (myarg_t *) arg;
	int inserts = m->inserts;
	list_t *L = m->L;

	for (int i=0; i<inserts; i++) {
		List_Insert(L, i);
	}

	return NULL;
}

int main() {
	printf("\n--- GRAPH3 LIST ---\n\n");

	// time tracking stuff
	struct timeval tv;
	long start; long end;

	// timing results
	int results[5];

	for (int x=0; x<5; x++) {
		gettimeofday(&tv, NULL);
		start = tv.tv_usec + tv.tv_sec*1000000;

		// -- MEATY CODE --
		// Shared counter_t
		list_t shared_list;
		List_Init(&shared_list);

		// Allocate 4 threads
		pthread_t threads[4];

		for (int i=0; i<4; i++) {
			myarg_t *args = (myarg_t*)malloc(sizeof(myarg_t));
			args->inserts = (x+1)*10000; args->L = &shared_list;

			if (pthread_create(&threads[i], NULL, varInsert, args) != 0) {
				printf("ERROR!!! :^)");
				exit(1);
			}
		}
		// Join them
		for (int i=0; i<4; i++) {
			pthread_join(threads[i], NULL);
		}

		gettimeofday(&tv, NULL);
		end = tv.tv_usec + tv.tv_sec*1000000;

		printf("Test with [%i0k] inserts complete.\n", (x+1));

		results[x] = end-start;
	}

	printf("\nResults: ");
	for (int i=0; i<5; i++) {
		if (i != 4) {
			printf("%f, ", results[i]/1000000.0);
		} else {
			printf("%f\n", results[i]/1000000.0);
		}
	}

	return 0;
}
