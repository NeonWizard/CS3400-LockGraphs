#ifndef CC_APPROX_H
#define CC_APPROX_H

typedef struct __counter_t {
	int global; // global count
	pthread_mutex_t glock; // global lock
	int local[NUMCPUS]; // local count (per cpu)
	pthread_mutex_t llock[NUMCPUS]; // ... and locks
	int threshold; // update frequency
} counter_t;

void init(counter_t *c, int threshold);
void update(counter_t *c, int threadID, int amt);
int get(counter_t *c);

#endif // CC_APPROX_H
