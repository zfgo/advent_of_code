#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <input_file>\n");
    assert(argc == 2);

    FILE *f;
    if ((f = fopen(argv[argc-1], "r")) == NULL)
        exit(1);


    char *in[5];
    int j = 0;
    for (int i = 0; i < 5; ++i)
    {
        in[i] = (char *)malloc(sizeof(char) * 4096);
    }

    while (fscanf(f, "%s\n", &in[j++]) == 1);

    fclose(f);


    return 0;
}
