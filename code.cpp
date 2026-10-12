
#include <stdio.h>

#define MAX 100

struct Item {
    int profit;
    int weight;
    float ratio;
};

void sortItems(struct Item a[], int n, int method) {
    int i, j;
    struct Item temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int swap = 0;

            if (method == 1 &&
                a[j].profit < a[j + 1].profit)
                swap = 1;

            if (method == 2 &&
                a[j].weight > a[j + 1].weight)
                swap = 1;

            if (method == 3 &&
                a[j].ratio < a[j + 1].ratio)
                swap = 1;

            if (swap) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

float knapsack(struct Item items[], int n,
               int capacity, int method) {
    struct Item a[MAX];
    float totalProfit = 0.0;
    int i;

    for (i = 0; i < n; i++)
        a[i] = items[i];

    sortItems(a, n, method);

    for (i = 0; i < n && capacity > 0; i++) {
        if (a[i].weight <= capacity) {
            capacity -= a[i].weight;
            totalProfit += a[i].profit;
        } else {
            totalProfit += a[i].ratio * capacity;
            capacity = 0;
        }
    }

    return totalProfit;
}

int main() {
    struct Item items[MAX];
    int n, capacity, i;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of items.\n");
        return 1;
    }

    printf("Enter profit and weight of each item:\n");

    for (i = 0; i < n; i++) {
        scanf("%d %d", &items[i].profit,
                        &items[i].weight);

        if (items[i].profit < 0 ||
            items[i].weight <= 0) {
            printf("Invalid profit or weight.\n");
            return 1;
        }

        items[i].ratio =
            (float)items[i].profit / items[i].weight;
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    if (capacity < 0) {
        printf("Invalid capacity.\n");
        return 1;
    }

    printf("\nMaximum profit using greedy methods:\n");

    printf("1. Maximum profit method: %.2f\n",
           knapsack(items, n, capacity, 1));

    printf("2. Minimum weight method: %.2f\n",
           knapsack(items, n, capacity, 2));

    printf("3. Profit/weight ratio method: %.2f\n",
           knapsack(items, n, capacity, 3));

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1000

struct Point {
    double x, y;
};

int compareX(const void *a, const void *b) {
    struct Point *p = (struct Point *)a;
    struct Point *q = (struct Point *)b;

    if (p->x < q->x) return -1;
    if (p->x > q->x) return 1;
    if (p->y < q->y) return -1;
    if (p->y > q->y) return 1;
    return 0;
}

int compareY(const void *a, const void *b) {
    struct Point *p = (struct Point *)a;
    struct Point *q = (struct Point *)b;

    if (p->y < q->y) return -1;
    if (p->y > q->y) return 1;
    return 0;
}

double distance(struct Point p1, struct Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;

    return sqrt(dx * dx + dy * dy);
}

double bruteForce(struct Point p[], int left, int right) {
    double minDist = INFINITY;
    int i, j;

    for (i = left; i <= right; i++) {
        for (j = i + 1; j <= right; j++) {
            double d = distance(p[i], p[j]);

            if (d < minDist)
                minDist = d;
        }
    }

    return minDist;
}

double closestPair(struct Point p[], int left, int right) {
    int n = right - left + 1;

    if (n <= 3)
        return bruteForce(p, left, right);

    int mid = left + (right - left) / 2;
    double midX = p[mid].x;

    double d1 = closestPair(p, left, mid);
    double d2 = closestPair(p, mid + 1, right);

    double minDist = (d1 < d2) ? d1 : d2;

    struct Point strip[MAX];
    int count = 0;
    int i, j;

    for (i = left; i <= right; i++) {
        if (fabs(p[i].x - midX) < minDist)
            strip[count++] = p[i];
    }

    qsort(strip, count, sizeof(struct Point), compareY);

    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (strip[j].y - strip[i].y >= minDist)
                break;

            double d = distance(strip[i], strip[j]);

            if (d < minDist)
                minDist = d;
        }
    }

    return minDist;
}

int main() {
    struct Point p[MAX];
    int n, i;

    printf("Enter number of points: ");
    scanf("%d", &n);

    if (n < 2 || n > MAX) {
        printf("Enter between 2 and %d points.\n", MAX);
        return 1;
    }

    printf("Enter x and y coordinates of each point:\n");

    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &p[i].x, &p[i].y);
    }

    qsort(p, n, sizeof(struct Point), compareX);

    double result = closestPair(p, 0, n - 1);

    printf("Minimum distance = %.4f\n", result);

    return 0;
}

