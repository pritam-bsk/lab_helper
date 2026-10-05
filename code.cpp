#include <stdio.h>

int main() {
    int n, i;
    int min, max, small, large;
    int comparisons = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n % 2 != 0) {
        printf("Enter a positive even number of elements.\n");
        return 0;
    }

    int a[n];

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if (a[0] < a[1]) {
        min = a[0];
        max = a[1];
    } else {
        min = a[1];
        max = a[0];
    }

    comparisons++;

    for (i = 2; i < n; i += 2) {
        comparisons++;

        if (a[i] < a[i+1]) {
            small = a[i];
            large = a[i+1];
        } else {
            small = a[i+1];
            large = a[i];
        }

        if (small < min) {
            min = small;
            comparisons++;
        } else {
            comparisons++;
        }

        if (large > max) {
            max = large;
            comparisons++;
        } else {
            comparisons++;
        }
    }

    printf("Minimum = %d\n", min);
    printf("Maximum = %d\n", max);
    printf("Total comparisons = %d\n", comparisons);

    return 0;
}
