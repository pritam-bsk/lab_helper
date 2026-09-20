#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

/* Remove leading zeros */
void removeLeadingZeros(char *str)
{
    int i = 0;

    while (str[i] == '0' && str[i + 1] != '\0')
        i++;

    if (i > 0)
        memmove(str, str + i, strlen(str + i) + 1);
}

/* Add two positive integers represented as strings */
void add(char *a, char *b, char *result)
{
    int i = strlen(a) - 1;
    int j = strlen(b) - 1;
    int k = 0, carry = 0;

    char temp[MAX];

    while (i >= 0 || j >= 0 || carry)
    {
        int sum = carry;

        if (i >= 0)
            sum += a[i--] - '0';

        if (j >= 0)
            sum += b[j--] - '0';

        temp[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    for (int x = 0; x < k; x++)
        result[x] = temp[k - x - 1];

    result[k] = '\0';

    removeLeadingZeros(result);
}

/* Subtract b from a, assuming a >= b */
void subtract(char *a, char *b, char *result)
{
    int i = strlen(a) - 1;
    int j = strlen(b) - 1;
    int borrow = 0;
    int k = 0;

    char temp[MAX];

    while (i >= 0)
    {
        int diff = (a[i] - '0') - borrow;

        if (j >= 0)
            diff -= (b[j--] - '0');

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        temp[k++] = diff + '0';
        i--;
    }

    while (k > 1 && temp[k - 1] == '0')
        k--;

    for (int x = 0; x < k; x++)
        result[x] = temp[k - x - 1];

    result[k] = '\0';
}

/* Shift number left by appending zeros */
void shiftLeft(char *num, int zeros, char *result)
{
    int len = strlen(num);

    if (strcmp(num, "0") == 0)
    {
        strcpy(result, "0");
        return;
    }

    strcpy(result, num);

    for (int i = 0; i < zeros; i++)
        result[len + i] = '0';

    result[len + zeros] = '\0';
}

/* Karatsuba multiplication */
void karatsuba(char *x, char *y, char *result)
{
    int n, m;

    removeLeadingZeros(x);
    removeLeadingZeros(y);

    if (strcmp(x, "0") == 0 || strcmp(y, "0") == 0)
    {
        strcpy(result, "0");
        return;
    }

    /* For small numbers, perform normal multiplication */
    if (strlen(x) <= 4 || strlen(y) <= 4)
    {
        long long a = atoll(x);
        long long b = atoll(y);

        sprintf(result, "%lld", a * b);
        return;
    }

    /* Make both numbers the same length */
    n = strlen(x) > strlen(y) ? strlen(x) : strlen(y);

    char xx[MAX], yy[MAX];

    sprintf(xx, "%0*s", n, x);
    sprintf(yy, "%0*s", n, y);

    m = n / 2;

    char a[MAX], b[MAX], c[MAX], d[MAX];

    strncpy(a, xx, m);
    a[m] = '\0';

    strcpy(b, xx + m);

    strncpy(c, yy, m);
    c[m] = '\0';

    strcpy(d, yy + m);

    char p[MAX], q[MAX], r[MAX];
    char sum1[MAX], sum2[MAX];

    char middle[MAX];
    char part1[MAX], part2[MAX];

    /* p = ac */
    karatsuba(a, c, p);

    /* q = bd */
    karatsuba(b, d, q);

    /* r = (a+b)(c+d) */
    add(a, b, sum1);
    add(c, d, sum2);

    karatsuba(sum1, sum2, r);

    /* middle = r - p - q */
    char temp[MAX];

    subtract(r, p, temp);
    subtract(temp, q, middle);

    /* part1 = p * 10^(2m) */
    shiftLeft(p, 2 * m, part1);

    /* part2 = middle * 10^m */
    shiftLeft(middle, m, part2);

    /* result = part1 + part2 + q */
    add(part1, part2, temp);
    add(temp, q, result);

    removeLeadingZeros(result);
}

int main()
{
    char x[MAX], y[MAX];
    char result[MAX];

    printf("Enter first large number: ");
    scanf("%999s", x);

    printf("Enter second large number: ");
    scanf("%999s", y);

    karatsuba(x, y, result);

    printf("\nProduct = %s\n", result);

    return 0;
}

#include <stdio.h>

/* Count number of digits */
int countDigits(long long n)
{
    int count = 0;

    if (n == 0)
        return 1;

    while (n != 0)
    {
        count++;
        n /= 10;
    }

    return count;
}

/* Calculate 10^n */
long long power10(int n)
{
    long long result = 1;

    for (int i = 0; i < n; i++)
        result *= 10;

    return result;
}

/* Mid-square hash function */
int midSquareHash(long long key, int tableSize)
{
    long long square = key * key;

    int squareDigits = countDigits(square);
    int hashDigits = countDigits(tableSize - 1);

    /*
       Number of digits to remove from the right
       to reach the middle portion.
    */
    int start = (squareDigits - hashDigits) / 2;

    if (start < 0)
        start = 0;

    long long divisor = power10(start);

    long long middle = (square / divisor) %
                       power10(hashDigits);

    return middle % tableSize;
}

int main()
{
    int n;
    int tableSize;

    printf("Enter hash table size: ");
    scanf("%d", &tableSize);

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("\nMid-Square Hash Values:\n");

    for (int i = 0; i < n; i++)
    {
        long long key;

        printf("\nEnter key: ");
        scanf("%lld", &key);

        long long square = key * key;

        int hash = midSquareHash(key, tableSize);

        printf("Key       = %lld\n", key);
        printf("Square    = %lld\n", square);
        printf("Hash Value = %d\n", hash);
    }

    return 0;
}
