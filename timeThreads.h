#ifndef TIME_THREADS
#define TIME_THREADS

#include <time.h>
#include <stdio.h>

#include "structures.h"
#include "calculating.h"

void timeMethods(int quanWithMultiThreads, int quanWithOneTread, 
                 vector* start, vectorsForThreads* vectorsThreadsStart, int threadsQuan);

#endif