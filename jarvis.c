#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 1000

typedef struct
{
    int x, y;
} Point;

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
    //  0 -> Collinear points
    //  1 -> Clockwise turn
    //  2 -> Counterclockwise turn
}

void jarvisMarch(Point points[], int n)
{
    if (n < 3)
    {
        printf("Convex hull is not possible\n");
        return;
    }

    int hull[MAX_POINTS];
    int hull_size = 0;

    int leftmost = 0;
    for (int i = 1; i < n; i++)
    {
        if (points[i].x < points[leftmost].x)
        {
            leftmost = i;
        }
    }

    int current = leftmost, next;
    do
    {
        hull[hull_size++] = current;
        next = (current + 1) % n;

        for (int i = 0; i < n; i++)
        {
            if (orientation(points[current], points[i], points[next]) == 1)
            {
                next = i;
            }
        }

        current = next;
    } while (current != leftmost);

    printf("Convex Hull:\n");
    for (int i = 0; i < hull_size; i++)
    {
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
    }
}

int main()
{
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);

    jarvisMarch(points, n);

    return 0;
}
