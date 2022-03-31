#include <stdio.h>

int main() {
    FILE* file;
    file = fopen("test_data.txt", "w");
    int a = 1, b = 2;
    fprintf(file, "%d %d\n", a, b);
    // printf("scaned: %d %d\n", a, b);
    double d1 = 1.0, d2 = 2.0, d3 = 3.0;
    fprintf(file, "%lf %lf %lf", d1, d2, d3);
    //printf("scaned: %d %d %d\n", d1, d2, d3);
    return 0;
}