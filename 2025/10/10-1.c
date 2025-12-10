#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct button 
{
    int btn_len;
    int btns[8];
} Button;

typedef struct machine 
{
    int n_lights;
    int *lights;
    int *lights_result;
    int n_btns;
    Button btns[16];
    int n_joltage;
    int joltages[16];
} Machine;

int check_lights(Machine m)
{
    int i = 0;
    while (m.lights[i] == m.lights_result[i] && i < m.n_lights)
        ++i;
    if (i == m.n_lights)
        return 1;

    return 0;
}

int calculate(Machine *machines, int n_machines)
{
    // need to calculate the minimum number of buttons that need to be pressed 
    // to get the machine's lights in the right configuration.
    // Do that for each machine, and then add up the minimum number of button
    // presses. 
    int ans = 0;
    for (int i = 0; i < n_machines; ++i)
    {
        Machine m = machines[i];

        for (int j = 0; j < n_btns; ++j)
        {
            for (int k = 0; k < n_btns; ++k)
            {
                if (j == k) 
                    continue;
            }   
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <input_file>\n");
    assert(argc == 2);

    FILE *f;

    if ((f = fopen(argv[argc-1], "r")) == NULL)
        exit(1);

    int n_lines = 4096;
    int line_size = 256;
    char **lines;
    int i, n_machines, n_reads;

    lines = (char **)malloc(sizeof(char *) * n_lines);
    for (i = 0; i < n_lines; ++i)
    {
        lines[i] = (char *)malloc(sizeof(char) * line_size);
    }

    i = 0;
    n_machines = 0;
    while ((fscanf(f, "%s\n", lines[i])) == 1)
    {
        if (lines[i][0] == '[')
        {
            ++n_machines;
        }
        ++i;
    }
    n_reads = i;

    Machine *machines = (Machine *)malloc(sizeof(Machine) * n_machines);

    int j = 0;
    int k = 0;
    const char c[2] = ",";
    char *tok = NULL;
    for (i = 0; i < n_reads-1; ++i)
    {
        switch (lines[i][0])
        {
        case '[':
            // defines the lights
            machines[j].n_lights = strlen(lines[i]) - 2;
            machines[j].lights = (int *)malloc(sizeof(int) * machines[j].n_lights);
            machines[j].lights_result = (int *)malloc(sizeof(int) * machines[j].n_lights);
            for (k = 0; k < machines[j].n_lights; ++k)
            {
                machines[j].lights_result[k] = lines[i][k+1] == '.' ? 0 : 1;
                machines[j].lights[k] = 0;
            }
            machines[j].n_btns = 0;
            machines[j].n_joltage = 0;
            break;
        case '(':
            // defines the buttons
            //printf("%ld\n", strlen(lines[i]));
            tok = strtok(&lines[i][1], c);
            k = 0;
            while (tok != NULL)
            {
                //printf("%s\n", tok);
                machines[j].btns[machines[j].n_btns].btns[k] = atoi(tok);
                //printf("%d\n", machines[j].btns[n_btns].btns[k]);
                ++k;
                tok = strtok(NULL, c);
            }
            machines[j].btns[machines[j].n_btns].btn_len = k;
            machines[j].n_btns++;
            break;
        case '{':
            // defines the joltages 
            tok = strtok(&lines[i][1], c);
            k = 0;
            while (tok != NULL)
            {
                //printf("%s\n", tok);
                machines[j].joltages[k] = atoi(tok);
                //printf("%d\n", machines[j].joltages[k]);
                ++k;
                tok = strtok(NULL, c);
            }
            machines[j].n_joltage = k;
            ++j;
            break;
        default:
            // should never be reached
            break;
        }
        //printf("%ld\n", strlen(lines[i]));
        //printf("%s\n", lines[i]);
    }
    // now that input is parsed, need to solve the problem 

    printf("Answer: %d\n", calculate(machines, n_machines));

    for (i = 0; i < n_machines; ++i)
    {
        free(machines[i].lights);
        free(machines[i].lights_result);
    }
    free(machines);

    for (i = 0; i < n_lines; ++i)
    {
        free(lines[i]);
    }
    free(lines);
    fclose(f);

    return 0;
}
