#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

int calc2(int *nums, int n)
{
    int asc = false;
    int desc = false;

    for (int i = 1; i < n; ++i)
    {
        int diff = abs(nums[i] - nums[i-1]);
        if (diff > 3 || diff == 0)
            return 0;
        if (nums[i] > nums[i-1])
            asc = true;
        if (nums[i] < nums[i-1])
            desc = true;
    }
    if (asc && desc)
        return 0;

    return 1;
}

int calc(char *lines[], int n, int ln_len)
{
    int ans = 0; // (number of "safe lines")
    const char delim[] = " ";
    int *nums[n];

    for (int i = 0; i < n; ++i)
    {
        int j = 0;
        char *tok;
        tok = strtok(lines[i], delim);
        nums[i] = (int *)malloc(sizeof(int) * ln_len);

        while (tok != NULL)
        {
            nums[i][j++] = atoi(tok);
            tok = strtok(NULL, delim);
        }

        ans += calc2(nums[i], j);
    }

    for (int i = 0; i < n; ++i)
        free(nums[i]);

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
    int ln_len = 128;
    char *lines[n];
    for (i = 0; i < n; ++i)
    {
        lines[i] = (char *)malloc(sizeof(char) * ln_len);
    }

    i = 0;
    while((fgets(lines[i], ln_len, f)) != NULL)
        ++i;
    n = i;

    printf("Answer: %d\n", calc(lines, n, ln_len));

    fclose(f);
    return 0;
}
