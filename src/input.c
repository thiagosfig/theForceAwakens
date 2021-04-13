#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int i, j;
    int t;
    int n;
    int k;
    time_t x;

    srand((unsigned)time(&x));

    t = 1 + rand() % 1;
    printf("%d\n", t);

    for (i = 0; i < t; i++)
    {
        // n = 1 + rand() % 500;
        // k = 0 + rand() % n / 2;
        n = 500;
        k = 250;
        printf("%d %d\n", n, k);
        for (j = 0; j <= n; j++)
        {
            printf("%d\n", 1 + rand() % 10);
        }
    }

    return 0;
}