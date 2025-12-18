#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PRINT       0
#define PRINTPROG   0
#define PRINTARGS   0
#define PRINTIP     0

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

void print_prog(int *cmds, int n)
{
#if PRINTPROG
    for (int i = 0; i < n-1; ++i)
        printf("%d: %d, ", i, cmds[i]);
    printf("%d: %d\n", n-1, cmds[n-1]);
#endif
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
    if (n == 1)
    {
        printf("oc: %d\n", cmds[0]);
        return;
    }
    for (int i = 0; i < n-1; ++i)
    {
        if (i == 0)
            printf("oc: ");
        printf("%d, ", cmds[i]);
    }
    printf("%d\n", cmds[n-1]);
#endif
}

void get_args(int *cmds, int ip, int *args, int n)
{
    int params = cmds[ip] / 100;
#if PRINTARGS
    printf("args: ");
#endif
    for (int i = 0; i < n; ++i)
    {
        if (params & 1)
            args[i] = cmds[ip+i+1];
        else
            args[i] = cmds[cmds[ip+i+1]];
#if PRINTARGS
        printf("%d, ", args[i]);
#endif
        params /= 10;
    }
#if PRINTARGS
    printf("\n");
#endif
}

int run(int *cmds, int n)
{
    int ip = 0;
    while (ip < n)
    {
#if PRINTIP
        printf("ip: %d\n", ip);
#endif
        print_prog(cmds, n);
        int oc = cmds[ip] % 100;       // opcode (rightmost 2 digits)
        int bufsiz = 512;   // needed for "OUT"
        char buf[bufsiz];   // needed for "OUT"
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
            case IN:    // 2 params: oc, out
                print_instr(oc, &cmds[ip], 2);
                if (fgets(buf, bufsiz, stdin) != NULL)
                {
                    sscanf(buf, "%d\n", &args[0]);
                }
                cmds[cmds[ip+1]] = args[0];
                ip += 2;
                break;
            case OUT:   // 2 params: oc, in
                print_instr(oc, &cmds[ip], 2);
                get_args(cmds, ip, args, 1);
                printf("> OUT: %d\n", args[0]);
                ip += 2;
                break;
            case JIT:   // 4 params: oc, in1, in2, out
                print_instr(oc, &cmds[ip], 3);
                get_args(cmds, ip, args, 2);
                if (args[0])
                {
                    ip = args[1];
                    break;
                }
                ip += 3;
                break;
            case JIF:
                print_instr(oc, &cmds[ip], 3);
                get_args(cmds, ip, args, 2);
                if (args[0] == 0)
                {
                    ip = args[1];
                    break;
                }
                ip += 3;
                break;
            case LT:
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 3);
                if (args[0] < args[1])
                    cmds[cmds[ip+3]] = 1;
                else 
                    cmds[cmds[ip+3]] = 0;
                ip += 4;
                break;
            case EQ:
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 3);
                if (args[0] == args[1])
                    cmds[cmds[ip+3]] = 1;
                else 
                    cmds[cmds[ip+3]] = 0;
                ip += 4;
                break;
            case HALT:
                print_instr(oc, &cmds[ip], 1);
                free(args);
                return cmds[0];
            default:
                fprintf(stderr, "Error: Reached default case, returning cmds[0]\n");
                return cmds[0];
        }
    }
    fprintf(stderr, "Error: Instruction pointer > n\n");
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
