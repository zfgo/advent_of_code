#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

typedef struct point 
{
    int x;
    int y;
    int z;
    bool in_circuit;
    int circuit[1000]; // index of other points in this point's circuit
} Point;

void make_circuits(Point **pts, int n_pts)
{
    // TODO
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <input_file>\n");
    assert(argc == 2);

    FILE *f;
    if ((f = fopen(argv[argc-1], "r")) == NULL)
    {
        exit(1);
    }

    int n_pts = 1000;
    int i = 0;
    Point pts[n_pts];

    while((fscanf(f, "%d,%d,%d\n", &pts[i].x, &pts[i].y, &pts[i].z)) == 3)
    {
        pts[i].in_circuit = false;
        ++i;
    }

    n_pts = i;

    fclose(f);
    return 0;
}
