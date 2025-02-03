#include <stdio.h>
#define SIZE 8
int maxCrossSum(int arr[], int l, int m, int h)
{
    int sum=0;
    int leftSum=arr[m];
    for (int i=m; i>=l; i--)
    {
        sum+=arr[i];
        if (leftSum<sum)
        {
            leftSum=sum;
        }
    }
    sum=0;
    int maxCross = leftSum;
    int rightSum=arr[m+1];
    for (int i=m+1; i<=h; i++)
    {
        sum+=arr[i];
        if (rightSum<sum)
        {
            rightSum=sum;
        }
    }
    maxCross = (rightSum>0 ? maxCross+rightSum : maxCross);
    return (leftSum+rightSum);
}
int maxSum(int arr[], int l, int h)
{
    if (l>h)
    {
        return 0;
    }
    if (l==h)
    {
        return arr[l];
    }
    int mid = l+h;
    mid = mid/2;
    int leftSum = maxSum(arr, l, mid);
    int rightSum = maxSum(arr, mid+1, h);
    int crossSum = maxCrossSum(arr, l, mid, h);
    if (mid==3)
    {
        printf("Maximum Left Sum: %d\nMaximum Right Sum: %d\nMaximum Cross Sum: %d\n",leftSum,rightSum,crossSum);
    }
    if (leftSum>rightSum && leftSum>crossSum)
    {
        return leftSum;
    }
    if (rightSum>leftSum && rightSum>crossSum)
    {
        return rightSum;
    }
    return crossSum;
}

int maxSub(int arr[], int n)
{
    int x = maxSum(arr, 0, n-1);
    return x;
}

int main(void)
{
    printf("Enter Array of Integers: \n");
    int arr[] = {-3,2,5,6,7,1,-3,-2};
    for (int i=0; i<SIZE; i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
    int ans = maxSub(arr,SIZE);
    printf("Maximum Sum of Sub-Array: %d\n",ans);
}