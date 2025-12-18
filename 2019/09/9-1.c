#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define PRINT       1
#define PRINTPROG   1
#define PRINTARGS   1
#define PRINTIP     1

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
 * Relative Mode (2):
 *      - 
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
    ARB = 9, 
    HALT = 99
} OP_CODE;

void print_prog(long long *cmds, int n)
{
#if PRINTPROG
    for (int i = 0; i < n-1; ++i)
        printf("%d: %lld, ", i, cmds[i]);
    printf("%d: %lld\n", n-1, cmds[n-1]);
#endif
}

void print_instr(int oc, long long *cmds, int n)
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
        case ARB: 
            printf("ARB: ");
            break;
        default:
            fprintf(stderr, "Error: print_instr default case\n");
            break;
    }
    if (n == 1)
    {
        printf("oc: %lld\n", cmds[0]);
        return;
    }
    for (int i = 0; i < n-1; ++i)
    {
        if (i == 0)
            printf("oc: ");
        printf("%lld, ", cmds[i]);
    }
    printf("%lld\n", cmds[n-1]);
#endif
}

void get_args(long long *cmds, int ip, long long *args, int n, long long rb)
{
    int params = cmds[ip] / 100;
#if PRINTARGS
    printf("args: ");
#endif
    for (int i = 0; i < n; ++i)
    {
        if (params % 10 == 1)       // position mode 
            args[i] = cmds[ip+i+1];
        else if (params % 10 == 0)  // immediate mode
            args[i] = cmds[cmds[ip+i+1]];
        else if (params % 10 == 2)  // relative mode
            args[i] = cmds[ip+i] + rb;
#if PRINTARGS
        printf("%lld, ", args[i]);
#endif
        params /= 10;
    }
#if PRINTARGS
    printf("\n");
#endif
}

void alloc_mem(long long **cmds, int n)
{
    *cmds = (long long *)malloc(sizeof(long long) * n);
}

void free_mem(long long *cmds)
{
    free(cmds);
}

// double the memory 
void realloc_mem(long long **cmds, int *n)
{
    *n *= 2;
    *cmds = (long long *)realloc(cmds, sizeof(long long) * *n);
}

void assign(long long *cmds, int addr, long long val, int *n)
{
    int len = *n;
    if (addr < len)
    {
        cmds[addr] = val;
        return;
    }
    else 
    {
        realloc_mem(&cmds, n);
        assign(cmds, addr, val, n);
    }
}

int run(long long *cmds, int n)
{
    int ip = 0;
    long long rb = 0;
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
        long long *args = (long long *)malloc(sizeof(long long) * n_args);

        switch (oc)
        {
            case ADD:   // 4 params: oc, in1, in2, out
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 2, rb);
                assign(cmds, cmds[ip+3], args[0]+args[1], &n);
                //cmds[cmds[ip+3]] = args[0] + args[1];
                ip += 4;
                break;
            case MULT:  // 4 params: oc, in1, in2, out
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 2, rb);
                assign(cmds, cmds[ip+3], args[0]*args[1], &n);
                //cmds[cmds[ip+3]] = args[0] * args[1];
                ip += 4;
                break;
            case IN:    // 2 params: oc, out
                print_instr(oc, &cmds[ip], 2);
                if (fgets(buf, bufsiz, stdin) != NULL)
                {
                    sscanf(buf, "%lld\n", &args[0]);
                }
                assign(cmds, cmds[ip+1], args[0], &n);
                //cmds[cmds[ip+1]] = args[0];
                ip += 2;
                break;
            case OUT:   // 2 params: oc, in
                print_instr(oc, &cmds[ip], 2);
                get_args(cmds, ip, args, 1, rb);
                printf("> OUT: %lld\n", args[0]);
                ip += 2;
                break;
            case JIT:   // 3 params: oc, in1, out
                print_instr(oc, &cmds[ip], 3);
                get_args(cmds, ip, args, 2, rb);
                if (args[0])
                {
                    ip = args[1];
                    break;
                }
                ip += 3;
                break;
            case JIF:   // 3 params: oc, in1, out
                print_instr(oc, &cmds[ip], 3);
                get_args(cmds, ip, args, 2, rb);
                if (args[0] == 0)
                {
                    ip = args[1];
                    break;
                }
                ip += 3;
                break;
            case LT:    // 4 params: oc, in1, in2, out
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 3, rb);

                if (args[0] < args[1])
                {
                    assign(cmds, cmds[ip+3], 1, &n);
                    //cmds[cmds[ip+3]] = 1;
                }
                else 
                {
                    assign(cmds, cmds[ip+3], 0, &n);
                    //cmds[cmds[ip+3]] = 0;
                }
                ip += 4;
                break;
            case EQ:    // 4 params: oc, in1, in2, out
                print_instr(oc, &cmds[ip], 4);
                get_args(cmds, ip, args, 3, rb);
                if (args[0] == args[1])
                {
                    assign(cmds, cmds[ip+3], 1, &n);
                    //cmds[cmds[ip+3]] = 1;
                }
                else 
                {
                    assign(cmds, cmds[ip+3], 0, &n);
                    //cmds[cmds[ip+3]] = 0;
                }
                ip += 4;
                break;
            case ARB:   // 2 params: oc, out
                print_instr(oc, &cmds[ip], 2);
                get_args(cmds, ip, args, 2, rb);
                rb += args[0];
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
    long long *cmds;
    alloc_mem(&cmds, n);
    int i = 0;
    char delim[] = ",";
    char *tok;
    char *end;

    tok = strtok(buf, delim);
    while (tok != NULL)
    {
        cmds[i] = atoll(tok);
        tok = strtok(NULL, delim);
        ++i;
    }
    n = i;

    run(cmds, n);

    free_mem(cmds);
    fclose(f);
    return 0;
}
