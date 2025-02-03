#include <stdio.h>
#include <math.h>
int max;
long long karatsuba(long long x, long long y) 
{

    if (x < 10 || y < 10) 
    {
        return x * y;
    }

    int numDigits = (int)log10(x > y ? x : y) + 1;
    printf("Maximum Length: %d\n",numDigits);
    int half = numDigits / 2;

    long long power = pow(10, half);
    long long xHigh = x / power;
    long long xLow = x % power;
    long long yHigh = y / power;
    long long yLow = y % power;

    long long z0 = karatsuba(xLow, yLow);
    long long z2 = karatsuba(xHigh, yHigh);
    long long z1 = karatsuba(xHigh + xLow, yHigh + yLow) - z2 - z0;

    return (z2 * power * power) + (z1 * power) + z0;
}

int main() {
    long long x, y;

    scanf("%lld %lld", &x, &y);

    printf("Product: %lld\n", karatsuba(x, y));

    return 0;
}