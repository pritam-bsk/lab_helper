#include <stdio.h>

#define TABLE_SIZE 10

int hashTable[TABLE_SIZE];

int hashFunction(int key)
{
    return key % TABLE_SIZE;
}

void initialize()
{
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = -1;
}

void insert(int key)
{
    int index, i = 0, newIndex;

    index = hashFunction(key);

    printf("\nInserting %d:", key);
    printf("\n  Hash value = %d %% %d = %d", key, TABLE_SIZE, index);

    while (hashTable[(index + i) % TABLE_SIZE] != -1)
    {
        newIndex = (index + i) % TABLE_SIZE;

        printf("\n  Collision at index %d", newIndex);
        i++;

        if (i == TABLE_SIZE)
        {
            printf("\nHash table is full!");
            return;
        }

        newIndex = (index + i) % TABLE_SIZE;
        printf("\n  Probing index %d", newIndex);
    }

    newIndex = (index + i) % TABLE_SIZE;
    hashTable[newIndex] = key;

    printf("\n  Key %d inserted at index %d\n", key, newIndex);
}

void display()
{
    int i;

    printf("\n\nFinal Hash Table:\n");
    printf("-----------------\n");

    for (i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i] == -1)
            printf("Index %d : EMPTY\n", i);
        else
            printf("Index %d : %d\n", i, hashTable[i]);
    }
}

int main()
{
    int n, i, key;
    int collisions = 0;

    initialize();

    printf("Enter number of keys: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter key %d: ", i + 1);
        scanf("%d", &key);

        int index = hashFunction(key);

        /* Count collisions before insertion */
        while (hashTable[index] != -1)
        {
            collisions++;
            index = (index + 1) % TABLE_SIZE;
        }

        insert(key);
    }

    display();

    printf("\nTotal number of collisions = %d\n", collisions);

    return 0;
}



#include <stdio.h>

#define MAX 100

void add(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX])
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiply(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX])
{
    int i, j, k;

    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = n / 2;

    int A11[MAX][MAX], A12[MAX][MAX];
    int A21[MAX][MAX], A22[MAX][MAX];

    int B11[MAX][MAX], B12[MAX][MAX];
    int B21[MAX][MAX], B22[MAX][MAX];

    int C11[MAX][MAX], C12[MAX][MAX];
    int C21[MAX][MAX], C22[MAX][MAX];

    int P1[MAX][MAX], P2[MAX][MAX];
    int P3[MAX][MAX], P4[MAX][MAX];
    int P5[MAX][MAX], P6[MAX][MAX];
    int P7[MAX][MAX], P8[MAX][MAX];

    /* Divide matrices into submatrices */
    for (i = 0; i < mid; i++)
    {
        for (j = 0; j < mid; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    /* Recursive multiplications */
    multiply(mid, A11, B11, P1);
    multiply(mid, A12, B21, P2);
    multiply(mid, A11, B12, P3);
    multiply(mid, A12, B22, P4);
    multiply(mid, A21, B11, P5);
    multiply(mid, A22, B21, P6);
    multiply(mid, A21, B12, P7);
    multiply(mid, A22, B22, P8);

    /* Calculate result submatrices */
    add(mid, P1, P2, C11);
    add(mid, P3, P4, C12);
    add(mid, P5, P6, C21);
    add(mid, P7, P8, C22);

    /* Combine submatrices */
    for (i = 0; i < mid; i++)
    {
        for (j = 0; j < mid; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }
}

int main()
{
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n, i, j;

    printf("Enter order of square matrices: ");
    scanf("%d", &n);

    printf("\nEnter elements of Matrix A:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter elements of Matrix B:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    multiply(n, A, B, C);

    printf("\nResultant Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d\t", C[i][j]);

        printf("\n");
    }

    return 0;
}
