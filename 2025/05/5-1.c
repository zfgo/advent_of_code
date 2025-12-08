#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct range 
{
    long long int min;
    long long int max;
} Range;

int fresh_calculator(Range *ranges, int n_ranges,  long long int *ids, int n_ids)
{
    int score = 0;
    for (int i = 0; i < n_ids; ++i)
    {
        for (int j = 0; j < n_ranges; ++j)
        {
            if (ids[i] >= ranges[j].min && ids[i] <= ranges[j].max)
            {
                ++score;
                break;
            }
        }
    }
    return score;
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <ranges_file> <ids_file>\n");
    assert(argc == 3);

    FILE *f_ranges;
    FILE *f_ids;

    if ((f_ranges = fopen(argv[1], "r")) == NULL || (f_ids = fopen(argv[2], "r")) == NULL)
    {
        exit(1);
    }

    int n_ranges = 177;
    int n_ids = 1000;
    int i = 0;
    long long int min, max;

    Range ranges[n_ranges];
    long long int ids[n_ids];

    while ((fscanf(f_ranges, "%Ld-%Ld\n", &min, &max)) == 2)
    {
        ranges[i].min = min;
        ranges[i].max = max;
        ++i;
    }

    i = 0;
    while ((fscanf(f_ids, "%Ld\n", &ids[i++])) == 1);

    printf("Answer: %d\n", fresh_calculator(ranges, n_ranges, ids, n_ids));

    fclose(f_ranges);
    fclose(f_ids);

    return 0;
}
