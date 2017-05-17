#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ITERATIONS 50

void benchmark();

void before();

void after();

int main() {
    struct timeval *start = (struct timeval *) malloc(sizeof(struct timeval));
    struct timeval *end = (struct timeval *) malloc(sizeof(struct timeval));

    before();
    for (int i = 0; i < ITERATIONS; i++) {
        gettimeofday(start, NULL);
        benchmark();
        gettimeofday(end, NULL);
        long time = (end->tv_sec-start->tv_sec)*1000L+(long)((end->tv_usec-start->tv_usec)*0.001);
        printf("execution time: %ld\n", time);
    }
    after();

    free(start);
    free(end);
    fflush(stdout);
    return 0;
}


