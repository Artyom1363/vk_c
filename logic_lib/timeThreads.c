#include "timeThreads.h"
#include "structures.h"
#include "calculating.h"



void timeMethods(int quanLaunchesMultiTreads, int quanLaunchesOneTread, 
                 vector* array, int sizeOfArray, int threadsQuan, int dimension) {
    
    vector* initial = createVector(dimension);

    for (int i = 0; i < quanLaunchesMultiTreads; ++i) {
        struct timespec begin, end;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &begin);

        vector* bestVect = buildThreads(array, sizeOfArray, 
                                        initial, threadsQuan,
                                        dimension);
        // printf("best vector:\n");
        deleteVector(bestVect);

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed = end.tv_sec - begin.tv_sec;
        elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
        printf("Time by %d threads:%f\n", threadsQuan, elapsed);
    }

    for (int i = 0; i < quanLaunchesOneTread; ++i) {
        struct timespec begin, end;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &begin);

        vector* bestVect = buildOneThread(array, sizeOfArray, 
                                          initial, dimension);
        deleteVector(bestVect);

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed = end.tv_sec - begin.tv_sec;
        elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
        printf("Time by one thread:%f\n", elapsed);
    }
    deleteVector(initial);
    printf("End of testing!\n");
}