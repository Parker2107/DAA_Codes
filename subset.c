#include <stdio.h>

#define MAX 100

int n, target;
int subset[MAX], arr[MAX];

void sumOfSubsets(int index, int currentSum, int remainingSum) 
{
    if (currentSum == target) 
    {
        printf("Subset found: ");
        for (int i = 0; i < index; i++) 
        {
            if (subset[i]) 
            {
                printf("%d ", arr[i]);
            }
        }
        printf("\n");
        return;
    }

    if (index == n || currentSum > target || currentSum + remainingSum < target) 
    {
        return;
    }
    subset[index] = 1;
    sumOfSubsets(index + 1, currentSum + arr[index], remainingSum - arr[index]);
    
    subset[index] = 0;
    sumOfSubsets(index + 1, currentSum, remainingSum - arr[index]);
}

int main() 
{
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements: ");
    int totalSum = 0;
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
        totalSum += arr[i];
    }

    printf("Enter the target sum: ");
    scanf("%d", &target);

    printf("Subsets with sum %d:\n", target);
    sumOfSubsets(0, 0, totalSum);

    return 0;
}