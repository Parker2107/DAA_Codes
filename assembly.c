#include <stdio.h>
#define NUM_STATIONS 6

int min(int a, int b) 
{
    return (a < b) ? a : b;
}

int assemblyLineScheduling(int a[2][NUM_STATIONS], int t[2][NUM_STATIONS - 1], int e[2], int x[2]) {

    int T1[NUM_STATIONS], T2[NUM_STATIONS];
    
    T1[0] = e[0] + a[0][0];
    T2[0] = e[1] + a[1][0];
    
    for (int i = 1; i < NUM_STATIONS; i++) 
    {
        T1[i] = min(T1[i - 1] + a[0][i], T2[i - 1] + t[1][i - 1] + a[0][i]);
        T2[i] = min(T2[i - 1] + a[1][i], T1[i - 1] + t[0][i - 1] + a[1][i]);
    }
    
    return min(T1[NUM_STATIONS - 1] + x[0], T2[NUM_STATIONS - 1] + x[1]);
}

int main() 
{
    int a[2][NUM_STATIONS] = {{7,9,3,4,8,4}, {8,5,6,4,5,7}}; // Processing times at stations
    int t[2][NUM_STATIONS - 1] = {{2,3,1,3,4}, {2,1,2,2,1}}; // Transfer times between stations
    int e[2] = {2, 4}; // Entry times
    int x[2] = {3, 2};  // Exit times
    
    int minTime = assemblyLineScheduling(a, t, e, x);
    printf("Minimum time to complete assembly: %d\n", minTime);
    
    return 0;
}
