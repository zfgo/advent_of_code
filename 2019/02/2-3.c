#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PRINT 1

typedef enum op_code
{
    ADD = 1,
    MULT = 2,
    IN = 3,
    OUT = 4,
    JIT = 5,
    JIF = 6,
    LT = 7,
    EQ = 8,
    HALT = 99
} OP_CODE;

void print_prog(int *cmnds, int n)
{
    for (int i = 0; i < n-1; ++i)
        printf("%d, ", cmnds[i]);
    printf("%d\n", cmnds[n-1]);
}

void print_instr(int oc, int *cmds, int n)
{
#if PRINT
    switch (oc)
    {
        case ADD:
            printf("ADD: ");
            break;
        case MULT:
            printf("MULT: ");
            break;
        case IN:
            printf("IN: ");
            break;
        case OUT:
            printf("OUT: ");
            break;
        case JIT:
            printf("JIT: ");
            break;
        case JIF:
            printf("JIF: ");
            break;
        case LT:
            printf("LT: ");
            break;
        case EQ:
            printf("EQ: ");
            break;
        case HALT:
            printf("HALT: ");
            break;
        default:
            fprintf(stderr, "Error: print_instr default case\n");
            break;
    }
    for (int i = 0; i < n-1; ++i)
        printf("%d, ", cmds[i]);
    printf("%d\n", cmds[n-1]);
#endif
}

void get_args(int *cmds, int ip, int *args, int n)
{
    int params = cmds[ip] / 100;
    for (int i = 0; i < n; ++i)
    {
        if (params & 1)
        {
            args[i] = cmds[ip+i+1];
            //printf("params&1: %d, args[%d]: %d\n", params, i, args[i]);
        }
        else
        {
            args[i] = cmds[cmds[ip+i+1]];
            printf("params: %d, args[%d]: %d\n", params, i, args[i]);
        }
        params /= 10;
    }
}

int run(int *cmds, int n)
{
    int ip = 0;
    while (ip < n) 
    {
        print_prog(cmds, n);
        int oc = cmds[ip] % 100;
        int n_args = 8;
        int *args = (int *)malloc(sizeof(int) * n_args);
        switch (oc)
        {
            case ADD:   // 4 params: oc, in1, in2, out
                //print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 3);
                printf("%d = %d + %d\n", args[0] + args[1], args[0], args[1]);
                printf("args[2]: %d\n", args[2]);
                cmds[cmds[ip+3]] = args[0] + args[1];
                ip += 4;
                break;
            case MULT:  // 4 params: oc, in1, in2, out
                //print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 3);
                printf("%d = %d * %d\n", args[0] * args[1], args[0], args[1]);
                printf("args[2]: %d\n", args[2]);
                cmds[cmds[ip+3]] = args[0] * args[1];
                ip += 4;
                break;
            case HALT:
                return cmds[0];
            default:
                //fprintf(stderr, "Error: Default case\n");
                break;
        }
    }
    return cmds[0];
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

    //cmnds[1] = 12;
    //cmnds[2] = 2;
    printf("Answer: %d\n", run(cmnds, n));

    fclose(f);
    return 0;
}

