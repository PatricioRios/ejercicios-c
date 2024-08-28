#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string50.c"
#include "rand.c"
#include "boolconst.c"


typedef struct {
    double x;
    double y;
} point;

typedef struct {
    double i;
    double j;
} vector;

point newPoint(double x, double y) {
    point p = {x, y};  // Use initializer list for cleaner assignment
    return p;
}

vector getVector(point p1, point p2) {
    vector v;
    v.i = p2.x - p1.x;  // Calculate vector components based on point differences
    v.j = p2.y - p1.y;
    return v;
}

int main() {
    point p1 = newPoint(3, 4);
    point p2 = newPoint(2, 5);

    vector v = getVector(p1, p2);

    printf("Point p1: (%.2f, %.2f)\n", p1.x, p1.y);  // Optional: Print point coordinates
    printf("Point p2: (%.2f, %.2f)\n", p2.x, p2.y);

    printf("Vector: (%.2f, %.2f)\n", v.i, v.j);

    return 0;
}
