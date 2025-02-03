#include <stdio.h>
#define SIZE 5
int m = 60;
struct data
{
    int w;
    int p;
    float r;
    float r1;
}data[SIZE], temp;

int main(void)
{
    int rem = m;
    for (int i=0; i<SIZE; i++)
    {
        printf ("Enter Weight and Profit: - \n"); 
        scanf ("%d", &data[i].w);
        scanf ("%d", &data[i].p);
    }
    printf("Weight\tProfit\n");
    for (int i=0; i<SIZE; i++)
    {
        data[i].r = (float)data[i].p/data[i].w;
        printf("%d\t%d\n",data[i].w, data[i].p);
    }
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            if (data[i].r>data[j].r)
            {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    printf("Weight\tProfit\n");
    for (int i=0; i<SIZE; i++)
    {
        printf("%d\t%d\n",data[i].w, data[i].p);
    }
    int j=0;
    float Psum=0, Wsum=0;
    while (rem>0)
    {
        if (rem<data[j].w)
        {
            Wsum+=rem;
            data[j].r1 = rem/(float)data[j].w;
            Psum+=data[j].p*data[j].r1;
            rem=0;
        }
        else
        {
            rem-=data[j].w;
            Wsum+=data[j].w;
            Psum+=data[j].p;
            data[j].r1 = 1.00;
        }
        j++;
    }
    for(int i=j; i<SIZE; i++)
    {
        data[i].r1 = 0.00;
    }
    printf("Weight\tProfit\tRatio:\n");
    for (int i=0; i<SIZE; i++)
    {
        printf("%d\t%d\t%.2f\n",data[i].w,data[i].p,data[i].r1);
    }
    printf("Total Weight: %.2f\n",Wsum);
    printf("Total Profit: %.2f\n",Psum);
}