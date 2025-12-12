#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int cmp(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

int calc(int *l1, int *l2, int n)
{
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans += abs(l1[i] - l2[i]);
    }

    return ans;
}

int main(int argc, char *argv[])
{
    assert(argc == 2);
    FILE *f;
    if ((f = fopen(argv[argc-1], "r")) == NULL)
        exit(1);

    int n = 1000;
    int i = 0;
    int l1[n];
    int l2[n];

    while ((fscanf(f, "%d   %d\n", &l1[i], &l2[i])) == 2)
        ++i;
    n = i;

    qsort((void *)l1, n, sizeof(l1[0]), cmp);
    qsort((void *)l2, n, sizeof(l2[0]), cmp);

    printf("Answer: %d\n", calc(l1, l2, n));

    fclose(f);

    return 0;
}
