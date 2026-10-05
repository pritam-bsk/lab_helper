#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p = (Point *)a;
    Point *q = (Point *)b;

    if (p->x != q->x)
        return p->x - q->x;
    return p->y - q->y;
}

int cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) -
           (b.y - a.y) * (c.x - a.x);
}

void mergeHull(Point p[], int l, int m, int r, Point h[], int *k) {
    Point temp[1000];
    int n = 0, i;

    for (i = l; i <= r; i++)
        temp[n++] = p[i];

    for (i = 0; i < n; i++) {
        while (*k >= 2 && cross(h[*k - 2], h[*k - 1], temp[i]) <= 0)
            (*k)--;

        h[(*k)++] = temp[i];
    }
}

void convexHull(Point p[], int l, int r, Point h[], int *k) {
    if (l == r) {
        h[(*k)++] = p[l];
        return;
    }

    int m = (l + r) / 2;

    convexHull(p, l, m, h, k);
    convexHull(p, m + 1, r, h, k);
}

int main() {
    int n, i, k = 0;
    Point p[1000], hull[1000], temp[1000];
    
    printf("Enter number of points: ");
    scanf("%d", &n);

    printf("Enter the points:\n");
    for (i = 0; i < n; i++)
        scanf("%d %d", &p[i].x, &p[i].y);

    qsort(p, n, sizeof(Point), compare);

    convexHull(p, 0, n - 1, hull, &k);

    k = 0;

    for (i = 0; i < n; i++) {
        while (k >= 2 && cross(temp[k - 2], temp[k - 1], p[i]) <= 0)
            k--;
        temp[k++] = p[i];
    }

    int lower = k;

    for (i = n - 2; i >= 0; i--) {
        while (k > lower && cross(temp[k - 2], temp[k - 1], p[i]) <= 0)
            k--;
        temp[k++] = p[i];
    }

    k--;

    printf("\nConvex Hull:\n");
    for (i = 0; i < k; i++)
        printf("(%d, %d)\n", temp[i].x, temp[i].y);

    return 0;
}
