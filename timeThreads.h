#ifndef TIME_THREADS
#define TIME_THREADS

#include <time.h>
#include <stdio.h>

#include "structures.h"
#include "calculating.h"

void timeMethods(int quanLaunchesMultiTreads, int quanLaunchesOneTread, 
                 vector* array, int sizeOfArray, int threadsQuan);

#endif