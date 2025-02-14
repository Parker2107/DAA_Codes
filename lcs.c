#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1001

void computeLCSLength(char *str1, char *str2, int m, int n, int dp[MAX][MAX]) 
{
    for (int i = 0; i <= m; i++) 
    {
        for (int j = 0; j <= n; j++) 
        {
            if (i == 0 || j == 0) 
            {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) 
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else 
            {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
}

void findLCSCombinations(char *str1, char *str2, int i, int j, int dp[MAX][MAX], char *currentLCS, int index) 
{
    if (i == 0 || j == 0) 
    {
        currentLCS[index] = '\0';
        printf("%s\n", currentLCS);
        return;
    }

    if (str1[i - 1] == str2[j - 1]) 
    {
        currentLCS[index] = str1[i - 1];
        findLCSCombinations(str1, str2, i - 1, j - 1, dp, currentLCS, index - 1);
    } else 
    {

        if (dp[i - 1][j] == dp[i][j]) 
        {
            findLCSCombinations(str1, str2, i - 1, j, dp, currentLCS, index);
        }
        if (dp[i][j - 1] == dp[i][j]) 
        {
            findLCSCombinations(str1, str2, i, j - 1, dp, currentLCS, index);
        }
    }
}

int main(void) 
{
    char str1[MAX], str2[MAX];

    fgets(str1, MAX, stdin);
    fgets(str2, MAX, stdin);

    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    int m = strlen(str1);
    int n = strlen(str2);
    int dp[MAX][MAX];

    computeLCSLength(str1, str2, m, n, dp);

    char currentLCS[MAX];
    printf("\n");

    findLCSCombinations(str1, str2, m, n, dp, currentLCS, dp[m][n] - 1);
    printf("The length of the Longest Common Subsequence is: %d\n", dp[m][n]);

    return 0;
}