#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum op_code
{
    ADD = 1,
    MULT = 2,
    HALT = 99
} OP_CODE;

void print_prog(int *cmnds, int n)
{
    for (int i = 0; i < n-1; ++i)
        printf("%d, ", cmnds[i]);
    printf("%d\n", cmnds[n-1]);
}

int run(int *cmnds, int n)
{
    for (int i = 0; i < n; i += 4)
    {
         //print_prog(cmnds, n);
        switch (cmnds[i])
        {
            case ADD:
                cmnds[cmnds[i+3]] = cmnds[cmnds[i+1]] + cmnds[cmnds[i+2]];
                break;
            case MULT:
                cmnds[cmnds[i+3]] = cmnds[cmnds[i+1]] * cmnds[cmnds[i+2]];
                break;
            case HALT:
                return cmnds[0];
            default:
                fprintf(stderr, "Error: Reached default case\n");
                break;
        }
    }
    return cmnds[0];
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <input>\n");
    assert(argc == 2);
    FILE *f = NULL;
    if ((f = fopen(argv[argc-1], "r")) == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int bufsiz = 512;
    char buf[bufsiz];
    while(fgets(buf, bufsiz, f))
        ;

    int n = 512;
    int i = 0;
    int cmnds[n];
    char delim[] = ",";
    char *tok;

    tok = strtok(buf, delim);
    while (tok != NULL)
    {
        cmnds[i] = atoi(tok);
        tok = strtok(NULL, delim);
        ++i;
    }
    n = i;

    cmnds[1] = 12;
    cmnds[2] = 2;
    printf("Answer: %d\n", run(cmnds, n));

    fclose(f);
    return 0;
}
