#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *prefixTable(char *p)
{
    int m = strlen(p);
    int *LPS = (int *)malloc(m * sizeof(int));
    LPS[0] = 0;
    int k = 0;
    for (int q = 1; q < m; q++)
    {
        while (k > 0 && p[k] != p[q])
        {
            k = LPS[k];
        }
        if (p[k] == p[q])
        {
            k++;
        }
        LPS[q] = k;
    }
    printf("Prefix Table: ");
    for (int i = 0; i < m; i++)
    {
        printf("%d ", LPS[i]);
    }
    printf("\n");
    return LPS;
}

void matcher(char *t, char *p)
{
    int n = strlen(t);
    int m = strlen(p);
    int *LPS = prefixTable(p);
    int q = 0;
    for (int i = 0; i < n; i++)
    {
        while (q > 0 && p[q] != t[i])
        {
            q = LPS[q - 1];
        }
        if (p[q] == t[i])
        {
            q++;
        }
        if (q == m)
        {
            printf("Pattern matches starting at %d\n", i - m + 2);
            q = LPS[q - 1];
        }
    }
}
int main(void)
{
    char *t = "SAQSPAPGPGGAS";
    char *p = "PGGA";
    matcher(t, p);
    return 1;
}