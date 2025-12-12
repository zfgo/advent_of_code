#include <stdio.h>
int main(void)
{
    for (int i = 0; i < 10; ++i)
    {
        printf("i: %d\n", i);
        i = 4;
        printf("i = 4: %d\n", i);

    }
    return 0;
}
