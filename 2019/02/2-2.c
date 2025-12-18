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
    int ip;
    for (ip = 0; ip < n; ip += 4)
    {
         //print_prog(cmnds, n);
        switch (cmnds[ip])
        {
            case ADD:
                cmnds[cmnds[ip+3]] = cmnds[cmnds[ip+1]] + cmnds[cmnds[ip+2]];
                break;
            case MULT:
                cmnds[cmnds[ip+3]] = cmnds[cmnds[ip+1]] * cmnds[cmnds[ip+2]];
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

void copy_memory(int *dest, int *src, int n)
{
    for (int i = 0; i < n; ++i)
    {
        dest[i] = src[i];
    }
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
    int init_cmnds[n];
    char delim[] = ",";
    char *tok;

    tok = strtok(buf, delim);
    while (tok != NULL)
    {
        init_cmnds[i] = atoi(tok);
        tok = strtok(NULL, delim);
        ++i;
    }
    n = i;

    int noun = 0;
    int verb = 0;
    int ans = 19690720;

    int *cmnds;
    if ((cmnds = (int *)malloc(sizeof(int) * n)) == NULL)
    {
        fclose(f);
        exit(EXIT_FAILURE);
    }

    for (noun = 0; noun < 100; ++noun)
    {
        for (verb = 0; verb < 100; ++verb)
        {
            copy_memory(cmnds, init_cmnds, n);
            cmnds[1] = noun;
            cmnds[2] = verb;
            if (run(cmnds, n) == ans)
            {
                ans = noun * 100 + verb;
                printf("Answer: %d\n", ans);
                fclose(f);
                return 0;
            }
        }
    }

    fclose(f);
    return 0;
}

