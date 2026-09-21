#include <stdio.h>

#define SIZE 100

int hashTable[SIZE];

int midSquareHash(int key)
{
    long long square = (long long)key * key;
    int start, digits = 2;
    long long divisor = 1;

    while (square >= 10000000)
        square /= 10;

    int length = 0;
    long long temp = square;

    while (temp > 0)
    {
        length++;
        temp /= 10;
    }

    start = (length - digits) / 2;

    for (int i = 0; i < start; i++)
        divisor *= 10;

    return (square / divisor) % 100;
}

int main()
{
    int n, key, index, pos;
    int collisions = 0;

    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter the keys:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &key);

        index = midSquareHash(key);
        pos = index;

        printf("\nKey %d:\n", key);
        printf("Square = %lld\n", (long long)key * key);
        printf("Initial hash index = %d\n", index);

        while (hashTable[pos] != -1)
        {
            printf("Collision at index %d\n", pos);
            collisions++;

            pos = (pos + 1) % SIZE;
            printf("Probing index %d\n", pos);
        }

        hashTable[pos] = key;
        printf("Inserted at index %d\n", pos);
    }

    printf("\n----- FINAL HASH TABLE -----\n");

    for (int i = 0; i < SIZE; i++)
    {
        if (hashTable[i] != -1)
            printf("Index %2d : %d\n", i, hashTable[i]);
    }

    printf("\nTotal number of collisions = %d\n", collisions);

    return 0;
}
