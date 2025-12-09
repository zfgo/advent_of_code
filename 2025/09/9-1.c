#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct point 
{
    long long int x;
    long long int y;
} Point;

long long int calc_area(Point pts[], int n_pts)
{
    long long int area;
    long long int max_area = 0;

    for (int i = 0; i < n_pts; ++i)
    {
        for (int j = 0; j < n_pts; ++j)
        {
            area = llabs((pts[i].x - pts[j].x + 1) * (pts[i].y - pts[j].y + 1));
            if (area > max_area)
                max_area = area;
        }
    }
    return max_area;
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <input_file>\n");
    assert(argc == 2);

    FILE *f;

    if ((f = fopen(argv[argc-1], "r")) == NULL)
        exit(1);

    int n_pts = 512;
    int i = 0;
    Point pts[n_pts];

    while ((fscanf(f, "%Ld,%Ld\n", &pts[i].x, &pts[i].y)) == 2)
    {
        ++i;
    }
    n_pts = i;

    printf("Largest area: %Ld\n", calc_area(pts, n_pts));

    fclose(f);

    return 0;
}
