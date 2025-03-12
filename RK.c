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

    // Compute h = d^(m-1) % q
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Compute hash values for pattern and first window of text
    for (i = 0; i < m; i++)
    {
        p = (d * p + P[i]) % q;
        t0 = (d * t0 + T[i]) % q;
    }

    // Pattern matching
    for (s = 0; s <= n - m; s++)
    {
        // If hash values match, check characters one by one
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
                printf("Pattern occurs from index: %d\n", s);
        }

        // Compute hash for next window
        if (s < n - m)
        {
            t0 = (d * (t0 - T[s] * h) + T[s + m]) % q;

            // Ensure non-negative hash
            if (t0 < 0)
                t0 += q;
        }
    }
}

// Driver function
int main()
{
    char T[] = "ABCCDDAEFG";
    char P[] = "CDD";
    int q = 101; // Prime number for mod operation
    int d = 256;
    rabinKarp(T, P, d, q);
    return 0;
}