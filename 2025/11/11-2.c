#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define DAC "dac"
#define FFT "fft"
#define OUT "out"
#define SVR "svr"
#define N 604

typedef struct node 
{
    char id[4];
    int hash;
    int n_nbrs;
    struct node **nbrs;
    int visited;
} Node;

int hash(char *w)
{
    return w[0] * 26 * 26 + w[1] * 26 + w[2];
}

long long int calc(Node *src, Node *dest, Node *exclude)
{
    //printf("src id: %s; dest id: %s\n", src->id, dest->id);
    // count number of paths from src to dest
    printf("src: %s, dest: %s\n", src->id, dest->id);
    if (src->hash == dest->hash)
        return 1;

    long long int ans = 0;
    for (int i = 0; i < src->n_nbrs; ++i)
    {
        if (exclude == NULL)
        {
            ans += calc(src->nbrs[i], dest, exclude);
            continue;
        }
        else 
        {
            if (src->nbrs[i]->hash == exclude->hash)
                continue;
            ans += calc(src->nbrs[i], dest, exclude);
        }
    }

    return ans;
}

int main(int argc, char *argv[])
{
    printf("Usage: ./a.out <input>\n");
    assert(argc == 2);

    FILE *f;
    if ((f = fopen(argc[argv-1], "r")) == NULL)
        exit(1);

    int n_lns = 604;
    int longest_ln = 100;
    int i = 0;
    char lines[n_lns][longest_ln];

    while (fgets(lines[i], sizeof(lines[i]), f))
    {
        //printf("%s", lines[i]);
        ++i;
    }
    n_lns = i;
    int n_nodes = i;
    int svr_id, dac_id, fft_id;
    int n_hash = 'z' * 26 * 26 + 'z' * 26 + 'z';
    printf("n hash %d\n", n_hash);
    Node nodes[n_nodes+1];

    for (i = 0; i < n_nodes; ++i)
    {
        char tmp[4];
        strncpy(tmp, lines[i], 3);
        tmp[3] = '\0';
        int h = hash(tmp);
        printf("h %d\n", h);
        strcpy(nodes[i].id, tmp);
        nodes[i].id[3] = '\0';
        nodes[i].hash = h;
        //printf("%s\n", nodes[i].id);

        nodes[i].n_nbrs = ((strlen(lines[i]) - 1) / 4) - 1;
        nodes[i].nbrs = (Node **)malloc(sizeof(Node *) * nodes[i].n_nbrs);
        nodes[i].visited = 0;
        //printf("%d\n", nodes[i].n_nbrs);
        if (nodes[i].hash == hash(SVR))
            svr_id = i;
        if (nodes[i].hash == hash(DAC))
            dac_id = i;
        if (nodes[i].hash == hash(FFT))
            fft_id = i;
    }

    // "out" node
    int out_h = hash(OUT);
    //int aaa_h = hash("aaa");
    //printf("aaa_h %d\n", aaa_h);
    strcpy(nodes[n_nodes].id, OUT);
    nodes[n_nodes].n_nbrs = 0;
    nodes[n_nodes].nbrs = NULL;
    nodes[n_nodes].hash = out_h;

    for (i = 0; i < n_nodes; ++i)
    {
        char id[4];
        for (int j = 0; j < nodes[i].n_nbrs; ++j)
        {
            strncpy(id, lines[i]+((j+1)*4)+1, 3);
            id[3] = '\0';
            if (strcmp(id, OUT) == 0)
            {
                nodes[i].nbrs[j] = &nodes[n_nodes];
                continue;
            }
            //printf("%s\n", id);
            for (int k = 0; k < n_nodes; ++k)
            {
                if (strcmp(id, nodes[k].id) == 0)
                {
                    nodes[i].nbrs[j] = &nodes[k];
                    break;
                }
            }
        }
    }

    long long int ans =  calc(&nodes[svr_id], &nodes[dac_id], &nodes[fft_id]) * calc(&nodes[dac_id], &nodes[fft_id], NULL) * calc(&nodes[fft_id], &nodes[out_h], &nodes[dac_id]);
    ans += calc(&nodes[svr_id], &nodes[fft_id], &nodes[dac_id]) * calc(&nodes[fft_id], &nodes[dac_id], NULL) * calc(&nodes[dac_id], &nodes[out_h], &nodes[fft_id]);
    printf("Answer: %Ld\n", ans);
    
    for (i = 0; i < n_nodes; ++i)
    {
        /*
        printf("%s:\n", nodes[i].id);
        for (int l = 0; l < nodes[i].n_nbrs; ++l)
        {
            printf("\t%s\n", nodes[i].nbrs[l]->id);
        }
        */
        free(nodes[i].nbrs);
    }
    fclose(f);

    return 0;
}
