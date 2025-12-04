#include <stdlib.h>
#include <stdio.h>

typedef struct instruction
{
    char dir;   /* L or R */
    int num;    /* 0 - 99 */
} Instruction;

typedef struct mark
{
    int num;
    struct mark *prev;
    struct mark *next;
} Mark;

int get_password(Instruction ins_list[], int ct, Mark *dial)
{
    int zero_ct = 0;

    for (int i = 0; i < ct; ++i)
    {
        // turning right means we add the number 
        // turning left means we subtract the number 
        // need to calculate the number of times that the dial is hits 0
        // if > 99 or < 0, then we do % 100

        switch (ins_list[i].dir)
        {
            case 'L':
                for (int j = 0; j < ins_list[i].num; ++j)
                {
                    dial = dial->prev;
                    if (dial->num == 0)
                    {
                        ++zero_ct;
                    }
                }
                break;
            case 'R':
                for (int j = 0; j < ins_list[i].num; ++j)
                {
                    dial = dial->next;
                    if (dial->num == 0)
                    {
                        ++zero_ct;
                    }
                }
                break;
            default:
                fprintf(stderr, "Error: reached default case (impossible): %c %d\n", ins_list[i].dir, ins_list[i].num);
                break;
        }
        //printf("%c %d location: %d zero_ct: %d\n", ins_list[i].dir, ins_list[i].num, loc, zero_ct);
    }

    return zero_ct;
}

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

    // make list of instructions (input is 4269 lines)
    Instruction ins_list[4300];
    int ct = 0;
    char dir;
    int num;

    // read from file 
    while (fscanf(f, "%c%d\n", &dir, &num) == 2)
    {
        // printf("%c %d\n", dir, num);
        ins_list[ct].dir = dir;
        ins_list[ct].num = num;
        ++ct;
    }
    fclose(f);

    // make Dial 
    Mark *dial;
    Mark *first;
    Mark *prev;
    Mark *m; 

    for (int i = 0; i <= 99; ++i)
    {
        m = (Mark *)malloc(sizeof(Mark));
        m->num = i;

        if (i == 0)
        {
            first = m;
        }

        if (i > 0)
        {
            prev->next = m;
            m->prev = prev;
        }

        prev = m;

        if (i == 50)
        {
            dial = m;
        }
    }

    first->prev = m;
    m->next = first;
    

    // turn the dial using the Instructions and count how many times it lands on 0
    // then that count is the answer 
    printf("Password: %d\n", get_password(ins_list, ct, dial));

    m->next->prev = NULL;
    while (m->prev != NULL)
    {
        prev = m->prev;
        free(m);
        m = prev;
    }
    free(m);

    return 0;
}
