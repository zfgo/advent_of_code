/* intended to be a copy of 5-1 just for messing around
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PRINT 0

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
    {
        if (i == 0)
            printf("oc: ");
        else
            printf("prm: ");
        printf("%d, ", cmds[i]);
    }
    printf("prm: ");
    printf("%d\n", cmds[n-1]);
#endif
}
        
void print_prog(int *cmds, int n)
{
    for (int i = 0; i < n-1; ++i)
        printf("%d, ", cmds[i]);
    printf("%d\n", cmds[n-1]);
}

/*
 * PARAMETER MODES
 *
 * Position Mode (0):
 *      - the mode we have been working with so far
 *      - <opcode>,<comma separated list of memory adresses>
 * Immediate Mode (1):
 *      - opcode is >100 
 *      - 2 least significant (rightmost) digits are the opcode 
 *      - digits going from right to left (hundreds place, thousands place, ten 
  *        thousands place, etc.) tell us whether to use immediate mode or 
  *        position mode 
 */
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
            //printf("params: %d, args[%d]: %d\n", params, i, args[i]);
        }
        params /= 10;
    }
}

int run(int *cmds, int n)
{
    int ip = 0;
    while (ip < n)
    {
        //printf("opcode : %d, ip: %d\n", cmds[ip], ip);
        //print_prog(cmds, n);
        int oc = cmds[ip] % 100;       // opcode (rightmost 2 digits)
        //printf("opcode: %d\n", oc);
        int params = cmds[ip] / 100;   // associated parameters
        int bufsiz = 512;
        char buf[bufsiz];
        int n_args = 8;
        int *args = (int *)malloc(sizeof(int) * n_args);

        switch (oc)
        {
            case ADD:   // 4 params: oc, in1, in2, out
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 2);
                cmds[cmds[ip+3]] = args[0] + args[1];
                ip += 4;
                break;
            case MULT:  // 4 params: oc, in1, in2, out
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 2);
                cmds[cmds[ip+3]] = args[0] * args[1];
                ip += 4;
                break;
            case IN:
                if (fgets(buf, bufsiz, stdin) != NULL)
                {
                    sscanf(buf, "%d\n", &args[0]);
                }
                cmds[cmds[ip+1]] = args[0];
                ip += 2;
                break;
            case OUT:
                print_instr(oc, &cmds[ip], 2);
                get_args(cmds, ip, args, 1);
                printf("> OUT: %d\n", args[0]);
                ip += 2;
                break;
            case HALT:
                return cmds[0];
            default:
                fprintf(stderr, "Error: Reached default case\n");
                break;
        }
    }
    return cmds[0];
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

    int bufsiz = 4096;
    char buf[bufsiz];
    while(fgets(buf, bufsiz, f))
        ;

    int n = 1024;
    int i = 0;
    int init_cmds[n];
    char delim[] = ",";
    char *tok;

    tok = strtok(buf, delim);
    while (tok != NULL)
    {
        init_cmds[i] = atoi(tok);
        tok = strtok(NULL, delim);
        ++i;
    }
    n = i;

    run(init_cmds, n);

    fclose(f);
    return 0;
}
