
#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (wt[i - 1] <= w) {
                dp[i][w] = max(
                    val[i - 1] + dp[i - 1][w - wt[i - 1]],
                    dp[i - 1][w]
                );
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int wt[n], val[n];

    printf("Enter weights: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }

    printf("Enter profits: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    printf("Maximum Profit = %d\n",
           knapsack(W, wt, val, n));

    return 0;
}



#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int LCS(char s1[], char s2[]) {
    int n = strlen(s1);
    int m = strlen(s2);

    int dp[n + 1][m + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {

            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            }
            else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
            }
        }
    }

    return dp[n][m];
}

int main() {
    char s1[100], s2[100];

    printf("Enter first string: ");
    scanf("%99s", s1);

    printf("Enter second string: ");
    scanf("%99s", s2);

    printf("Length of LCS = %d\n", LCS(s1, s2));

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
    int id;
} Point;

Point bestA, bestB;
double bestDist = INFINITY;

// Sort points according to x-coordinate
int compareX(const void *a, const void *b) {
    Point *p = (Point *)a;
    Point *q = (Point *)b;

    if (p->x < q->x) return -1;
    if (p->x > q->x) return 1;
    return (p->y > q->y) - (p->y < q->y);
}

// Sort points according to y-coordinate
int compareY(const void *a, const void *b) {
    Point *p = (Point *)a;
    Point *q = (Point *)b;

    if (p->y < q->y) return -1;
    if (p->y > q->y) return 1;
    return (p->x > q->x) - (p->x < q->x);
}

// Calculate squared distance
double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return dx * dx + dy * dy;
}

// Update closest pair
void update(Point a, Point b) {
    double d = dist(a, b);

    if (d < bestDist) {
        bestDist = d;
        bestA = a;
        bestB = b;
    }
}

// Divide and Conquer function
double closestPair(Point px[], int l, int r,
                   Point py[], Point temp[]) {

    int n = r - l + 1;

    // Base case: at most 3 points
    if (n <= 3) {
        double d = INFINITY;

        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                update(px[i], px[j]);

                double cur = dist(px[i], px[j]);

                if (cur < d)
                    d = cur;
            }
        }

        return d;
    }

    // Divide
    int mid = (l + r) / 2;
    double midX = (px[mid].x + px[mid+1].x) / 2.0;

    // Divide Py into left and right according to IDs
    int leftCount = 0;
    int rightCount = mid + 1;

    for (int i = l; i <= r; i++) {
        if (py[i].id <= mid)
            temp[leftCount++ + l] = py[i];
        else
            temp[rightCount++] = py[i];
    }

    // Copy partitioned points back
    for (int i = l; i <= r; i++)
        py[i] = temp[i];

    // Conquer
    double dl = closestPair(px, l, mid, py, temp);
    double dr = closestPair(px, mid+1, r, py, temp);

    double d = (dl < dr) ? dl : dr;

    // Combine: collect points in the middle strip
    int k = 0;

    for (int i = l; i <= r; i++) {
        double dx = py[i].x - midX;

        if (dx * dx < d)
            temp[k++] = py[i];
    }

    // Check at most next 7 points
    for (int i = 0; i < k; i++) {
        for (int j = i + 1;
             j < k && j <= i + 7; j++) {

            double dy = temp[j].y - temp[i].y;

            if (dy * dy >= d)
                break;

            update(temp[i], temp[j]);

            double cur = dist(temp[i], temp[j]);

            if (cur < d)
                d = cur;
        }
    }

    return d;
}

int main() {
    int n;

    printf("Enter number of points: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("At least 2 points are required.\n");
        return 0;
    }

    Point *px = malloc(n * sizeof(Point));
    Point *py = malloc(n * sizeof(Point));
    Point *temp = malloc(n * sizeof(Point));

    if (!px || !py || !temp) {
        printf("Memory allocation failed.\n");
        free(px);
        free(py);
        free(temp);
        return 1;
    }

    printf("Enter coordinates (x y):\n");

    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &px[i].x, &px[i].y);
    }

    // Sort by x-coordinate
    qsort(px, n, sizeof(Point), compareX);

    // Assign unique IDs based on sorted positions
    for (int i = 0; i < n; i++) {
        px[i].id = i;
        py[i] = px[i];
    }

    // Sort by y-coordinate
    qsort(py, n, sizeof(Point), compareY);

    // Find closest pair
    closestPair(px, 0, n-1, py, temp);

    printf("\nClosest pair of points:\n");

    printf("(%.2lf, %.2lf)\n", bestA.x, bestA.y);
    printf("(%.2lf, %.2lf)\n", bestB.x, bestB.y);

    printf("\nMinimum distance = %.4lf\n",
           sqrt(bestDist));

    free(px);
    free(py);
    free(temp);

    return 0;
}
