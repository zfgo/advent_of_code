#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int fuel_req(int *m, int n)
{
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans += (m[i] / 3) - 2;
    }
    return ans;
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <input>\n");
    assert(argc == 2);
    FILE *f = NULL;
    if ((f = fopen(argv[argc-1], "r")) == NULL)
    {
        exit(1);
    }

    int n = 1000;
    int i = 0;
    int m[n];

    while ((fscanf(f, "%d\n", &m[i])) == 1)
    {
        ++i;
    }

    n = i;
    printf("Fuel requirement: %d\n", fuel_req(m, n));

    fclose(f);
    return 0;
}
