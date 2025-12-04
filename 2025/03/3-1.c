#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    if (argc != 2)  /* need to have a file */
    {
        fprintf(stderr, "Usage: ./a.out <input_file>\n");
        return 1;
    }

    // open file, argv[argc-1] is the file name
    FILE *f;

    if ((f = fopen(argv[argc-1], "r")) == NULL)
    {
        fprintf(stderr, "Error: couldn't read file %s\n", argv[argc-1]);
        return 1;
    }

    char *joltage[256];
    int i = 0;
    char num[128];

    while (fscanf(f, "%s\n", num) == 1)
    {
        joltage[i++] = num;
        printf("%d\n", joltage[i-1]);
    }
    fclose(f);

    return 0;
}
