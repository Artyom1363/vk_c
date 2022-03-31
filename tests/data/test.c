#include <stdio.h>
#include <stdlib.h> 

int main() {
    FILE* file;
    char *name = malloc(sizeof(char) * 19);
    name = "test_data.txt";
    file = fopen(name, "r");
    free(name);
    int a, b;
    fscanf(file, "%d %d", &a, &b);
    printf("scaned: %d %d\n", a, b);
    double d1, d2, d3;
    fscanf(file, "%lf %lf %lf", &d1, &d2, &d3);
    printf("scaned: %f %f %f\n", d1, d2, d3);
    return 0;
}