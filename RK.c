#include <stdio.h>
#include <string.h>

void rabinKarp(char T[], char P[], int d, int q)
{
    int n = strlen(T);
    int m = strlen(P);
    int h = 1;
    int p = 0;
    int t0 = 0;
    int i, s;

    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < m; i++)
    {
        p = (d * p + P[i]) % q;
        t0 = (d * t0 + T[i]) % q;
    }

    for (s = 0; s <= n - m; s++)
    {
        if (p == t0)
        {
            int match = 1;
            for (i = 0; i < m; i++)
            {
                if (P[i] != T[s + i])
                {
                    match = 0;
                    break;
                }
            }
            if (match)
                printf("Pattern occurs from index: %d\n", s + 1);
        }
        if (s < n - m)
        {
            t0 = (d * (t0 - T[s] * h) + T[s + m]) % q;
            if (t0 < 0)
            {
                t0 += q;
            }
        }
    }
}

int main()
{
    char T[] = "SAQSPAPGPGGAS";
    char P[] = "PGGA";
    int q = 29;
    int d = 256;
    rabinKarp(T, P, d, q);
    return 0;
}