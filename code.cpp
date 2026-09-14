#include <stdio.h>

#define SIZE 10

int hash(int key) {
    return key % SIZE;
}

void insert(int a[], int key) {
    int i, index = hash(key);

    for (i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;
        if (a[pos] == -1) {
            a[pos] = key;
            return;
        }
    }

    printf("Hash table is full\n");
}

void display(int a[]) {
    int i;
    for (i = 0; i < SIZE; i++)
        printf("%d : %d\n", i, a[i]);
}

int main() {
    int a[SIZE], n, key, i;

    for (i = 0; i < SIZE; i++)
        a[i] = -1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(a, key);
    }

    printf("\nHash Table:\n");
    display(a);

    return 0;
}

Sample Input

Enter number of elements: 6
Enter elements: 25 32 42 17 52 62

Sample Output

Hash Table:
0 : -1
1 : -1
2 : 32
3 : 42
4 : 52
5 : 25
6 : 62
7 : 17
8 : -1
9 : -1

---

2. Matrix Multiplication Using Divide and Conquer

Normally, matrix multiplication uses three nested loops.

For two "n × n" matrices:

[
C[i][j] = \sum_{k=0}^{n-1} A[i][k]B[k][j]
]

The normal algorithm has:

[
T(n)=O(n^3)
]

Divide and Conquer divides each matrix into four submatrices.

Suppose:

[
A =
\begin{bmatrix}
A_{11} & A_{12}\
A_{21} & A_{22}
\end{bmatrix}
]

and

[
B =
\begin{bmatrix}
B_{11} & B_{12}\
B_{21} & B_{22}
\end{bmatrix}
]

Then:

[
C_{11}=A_{11}B_{11}+A_{12}B_{21}
]

[
C_{12}=A_{11}B_{12}+A_{12}B_{22}
]

[
C_{21}=A_{21}B_{11}+A_{22}B_{21}
]

[
C_{22}=A_{21}B_{12}+A_{22}B_{22}
]

The process continues recursively until the matrix becomes "1 × 1".

---

Divide and Conquer Recurrence

For ordinary divide-and-conquer matrix multiplication:

[
T(n)=8T(n/2)+O(n^2)
]

Therefore:

[
T(n)=O(n^3)
]

So ordinary divide-and-conquer matrix multiplication does not improve the asymptotic complexity over the standard algorithm.

---

C Program: Matrix Multiplication Using Divide and Conquer

This version assumes "n" is a power of 2, such as "2, 4, 8, 16...".

:::writing{variant="document" id="74106" title="Matrix Multiplication Using Divide and Conquer in C"}

#include <stdio.h>

#define MAX 64

void add(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int P1[MAX][MAX], P2[MAX][MAX], P3[MAX][MAX], P4[MAX][MAX];
    int P5[MAX][MAX], P6[MAX][MAX], P7[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];
    int i, j, k = n / 2;

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    for (i = 0; i < k; i++)
        for (j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }

    multiply(A11, B11, T1, k);
    multiply(A12, B21, T2, k);
    add(T1, T2, C11, k);

    multiply(A11, B12, T1, k);
    multiply(A12, B22, T2, k);
    add(T1, T2, C12, k);

    multiply(A21, B11, T1, k);
    multiply(A22, B21, T2, k);
    add(T1, T2, C21, k);

    multiply(A21, B12, T1, k);
    multiply(A22, B22, T2, k);
    add(T1, T2, C22, k);

    for (i = 0; i < k; i++)
        for (j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n, i, j;

    printf("Enter matrix size: ");
    scanf("%d", &n);

    printf("Enter first matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter second matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    multiply(A, B, C, n);

    printf("Result:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}

#include <stdio.h>

#define SIZE 10

int hash(int key) {
    return key % SIZE;
}

void insert(int a[], int key) {
    int i, index = hash(key);

    for (i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;
        if (a[pos] == -1) {
            a[pos] = key;
            return;
        }
    }

    printf("Hash table is full\n");
}

void display(int a[]) {
    int i;
    for (i = 0; i < SIZE; i++)
        printf("%d : %d\n", i, a[i]);
}

int main() {
    int a[SIZE], n, key, i;

    for (i = 0; i < SIZE; i++)
        a[i] = -1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(a, key);
    }

    printf("\nHash Table:\n");
    display(a);

    return 0;
}

Sample Input

Enter number of elements: 6
Enter elements: 25 32 42 17 52 62

Sample Output

Hash Table:
0 : -1
1 : -1
2 : 32
3 : 42
4 : 52
5 : 25
6 : 62
7 : 17
8 : -1
9 : -1

---

2. Matrix Multiplication Using Divide and Conquer

Normally, matrix multiplication uses three nested loops.

For two "n × n" matrices:

[
C[i][j] = \sum_{k=0}^{n-1} A[i][k]B[k][j]
]

The normal algorithm has:

[
T(n)=O(n^3)
]

Divide and Conquer divides each matrix into four submatrices.

Suppose:

[
A =
\begin{bmatrix}
A_{11} & A_{12}\
A_{21} & A_{22}
\end{bmatrix}
]

and

[
B =
\begin{bmatrix}
B_{11} & B_{12}\
B_{21} & B_{22}
\end{bmatrix}
]

Then:

[
C_{11}=A_{11}B_{11}+A_{12}B_{21}
]

[
C_{12}=A_{11}B_{12}+A_{12}B_{22}
]

[
C_{21}=A_{21}B_{11}+A_{22}B_{21}
]

[
C_{22}=A_{21}B_{12}+A_{22}B_{22}
]

The process continues recursively until the matrix becomes "1 × 1".

---

Divide and Conquer Recurrence

For ordinary divide-and-conquer matrix multiplication:

[
T(n)=8T(n/2)+O(n^2)
]

Therefore:

[
T(n)=O(n^3)
]

So ordinary divide-and-conquer matrix multiplication does not improve the asymptotic complexity over the standard algorithm.

---

C Program: Matrix Multiplication Using Divide and Conquer

This version assumes "n" is a power of 2, such as "2, 4, 8, 16...".

:::writing{variant="document" id="74106" title="Matrix Multiplication Using Divide and Conquer in C"}

#include <stdio.h>

#define MAX 64

void add(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n) {
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int P1[MAX][MAX], P2[MAX][MAX], P3[MAX][MAX], P4[MAX][MAX];
    int P5[MAX][MAX], P6[MAX][MAX], P7[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];
    int i, j, k = n / 2;

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    for (i = 0; i < k; i++)
        for (j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }

    multiply(A11, B11, T1, k);
    multiply(A12, B21, T2, k);
    add(T1, T2, C11, k);

    multiply(A11, B12, T1, k);
    multiply(A12, B22, T2, k);
    add(T1, T2, C12, k);

    multiply(A21, B11, T1, k);
    multiply(A22, B21, T2, k);
    add(T1, T2, C21, k);

    multiply(A21, B12, T1, k);
    multiply(A22, B22, T2, k);
    add(T1, T2, C22, k);

    for (i = 0; i < k; i++)
        for (j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n, i, j;

    printf("Enter matrix size: ");
    scanf("%d", &n);

    printf("Enter first matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter second matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    multiply(A, B, C, n);

    printf("Result:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
