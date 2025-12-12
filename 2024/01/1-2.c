#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int calc(int *l1, int *l2, int n)
{
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int sim = 0;
        for (int j = 0; j < n; ++j)
        {
            if (l1[i] == l2[j])
                ++sim;
        }
        ans += l1[i] * sim;
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

    printf("Answer: %d\n", calc(l1, l2, n));

    fclose(f);

    return 0;
}
