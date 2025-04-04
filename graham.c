#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int x, y;
} Point;

Point p0;

void swap(Point *p1, Point *p2)
{
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
    // 0 -> p, q and r are collinear
    // 1 -> Clockwise
    // 2 -> Counterclockwise
}

int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

void convexHull(Point points[], int n)
{
    if (n < 3)
    {
        printf("Convex hull is not possible\n");
        return;
    }

    // Find the bottom point
    int minY = points[0].y, minIndex = 0;
    for (int i = 1; i < n; i++)
    {
        if ((points[i].y < minY) || (points[i].y == minY && points[i].x < points[minIndex].x))
        {
            minY = points[i].y;
            minIndex = i;
        }
    }
    swap(&points[0], &points[minIndex]);
    p0 = points[0];

    // Sort the remaining points based on polar angle with p0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    int m = 1;
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    if (m < 3)
    {
        printf("Convex hull is not possible\n");
        return;
    }

    Point stack[m];
    int top = 0;
    stack[top++] = points[0];
    stack[top++] = points[1];
    stack[top++] = points[2];

    for (int i = 3; i < m; i++)
    {
        while (top > 1 && orientation(stack[top - 2], stack[top - 1], points[i]) != 2)
            top--;
        stack[top++] = points[i];
    }

    printf("Convex Hull:\n");
    for (int i = 0; i < top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main()
{
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
