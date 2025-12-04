#include <stdlib.h>
#include <stdio.h>

typedef struct instruction
{
    char dir;   /* L or R */
    int num;    /* 0 - 99 */
} Instruction;

int get_password(Instruction ins_list[], int ct)
{
    int start = 50;
    int zero_ct = 0;

    for (int i = 0; i < ct; ++i)
    {
        // turning right means we add the number 
        // turning left means we subtract the number 
        // if > 99 or < 0, then we do % 100

        switch (ins_list[i].dir)
        {
            case 'L':
                start -= ins_list[i].num;
                break;
            case 'R':
                start += ins_list[i].num;
                break;
            default:
                fprintf(stderr, "Error: reached default case (impossible): %c %d\n", ins_list[i].dir, ins_list[i].num);
                break;
        }
        if ((start %= 100) == 0)
        {
            ++zero_ct;
        }
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

    // turn the dial using the Instructions and count how many times it lands on 0
    // then that count is the answer 
    printf("Password: %d\n", get_password(ins_list, ct));

    return 0;
}
