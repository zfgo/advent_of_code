#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct range 
{
    long long int min;
    long long int max;
} Range;

int compare(const void *a, const void *b)
{
    Range *ra = (Range *)a;
    Range *rb = (Range *)b;

    if (ra->min < rb->min)
        return -1;
    return 1;
}

long long int fresh_calculator_v2(Range *ranges, int n_ranges)
{
    long long int score = 0;
    long long int last_max = ranges[0].min - 2;
    int i = 0;

    while (i < n_ranges)
    {
        if (last_max < ranges[i].min)
        {
            score += (ranges[i].max - ranges[i].min) + 1;
            last_max = ranges[i].max;
            ++i;
        }
        else if (last_max > ranges[i].max)
        {
            ++i;
        }
        else if (last_max >= ranges[i].min)
        {
            score += ranges[i].max - last_max;
            last_max = ranges[i].max;
            ++i;
        }
    }

    return score;
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <ranges_file>\n");
    assert(argc == 2);

    FILE *f_ranges;

    if ((f_ranges = fopen(argv[1], "r")) == NULL)
    {
        exit(1);
    }

    int n_ranges = 177;
    int i = 0;
    long long int min, max;

    Range ranges[n_ranges];

    while ((fscanf(f_ranges, "%Ld-%Ld\n", &min, &max)) == 2)
    {
        ranges[i].min = min;
        ranges[i].max = max;
        ++i;
    }

    qsort(ranges, n_ranges, sizeof(Range), compare);

    printf("Answer: %Ld\n", fresh_calculator_v2(ranges, n_ranges));
    fclose(f_ranges);

    return 0;
}
