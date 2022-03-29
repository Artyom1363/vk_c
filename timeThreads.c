#include "timeThreads.h"

void timeMethods(int quanWithMultiThreads, int quanWithOneTread, 
                 vector* start, vectorsForThreads* vectorsThreadsStart, int threadsQuan) {

    for (int i = 0; i < quanWithMultiThreads; ++i) {
        struct timespec begin, end;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &begin);

        buildTreads(vectorsThreadsStart, threadsQuan);

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed = end.tv_sec - begin.tv_sec;
        elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
        printf("Time by %d threads:%f\n", threadsQuan, elapsed);
    }

    for (int i = 0; i < quanWithOneTread; ++i) {
        struct timespec begin, end;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &begin);

        buildOneTread(start);

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed = end.tv_sec - begin.tv_sec;
        elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
        printf("Time by one thread:%f\n", elapsed);
    }
    printf("End of testing!\n");
}