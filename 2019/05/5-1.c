#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

int run(int *cmnds, int n)
{
    int ip = 0;
    while (ip < n)
    {
        //printf("opcode : %d, ip: %d\n", cmnds[ip], ip);
        //print_prog(cmnds, n);
        int oc = cmnds[ip] % 100;       // opcode (rightmost 2 digits)
        //printf("opcode: %d\n", oc);
        int params = cmnds[ip] / 100;   // associated parameters
        int bufsiz = 512;
        char buf[bufsiz];
        int tmp = 0;

        switch (oc)
        {
            case ADD:
                tmp = 0;
                for (int i = 0; i < 2; ++i)
                {
                    if (params & 1)
                        tmp += cmnds[ip+i+1];
                    else 
                        tmp += cmnds[cmnds[ip+i+1]];
                    params /= 10;
                }
                cmnds[cmnds[ip+3]] = tmp;
                ip += 4;
                break;
            case MULT:
                tmp = 1;
                for (int i = 0; i < 2; ++i)
                {
                    if (params & 1)
                        tmp *= cmnds[ip+i+1];
                    else 
                        tmp *= cmnds[cmnds[ip+i+1]];
                    params /= 10;
                }
                cmnds[cmnds[ip+3]] = tmp;
                ip += 4;
                break;
            case IN:
                if (fgets(buf, bufsiz, stdin) != NULL)
                {
                    sscanf(buf, "%d\n", &tmp);
                }
                cmnds[cmnds[ip+1]] = tmp;
                ip += 2;
                break;
            case OUT:
                if (params & 1)
                    printf("OUT: %d\n", cmnds[ip+1]);
                else 
                    printf("OUT: %d\n", cmnds[cmnds[ip+1]]);
                ip += 2;
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

    int bufsiz = 4096;
    char buf[bufsiz];
    while(fgets(buf, bufsiz, f))
        ;

    int n = 1024;
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

    run(init_cmnds, n);

    fclose(f);
    return 0;
}
