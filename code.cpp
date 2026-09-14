#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    return value % TABLE_SIZE;
}

HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

void insert(HashTable* table, const char* key, int value) {
    unsigned int bucket_index = hash(key);
    Node* current = table->buckets[bucket_index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    Node* new_node = malloc(sizeof(Node));
    new_node->key = strdup(key); 
    new_node->value = value;
    new_node->next = table->buckets[bucket_index];
    table->buckets[bucket_index] = new_node;
}

int search(HashTable* table, const char* key, int* out_value) {
    unsigned int bucket_index = hash(key);
    Node* current = table->buckets[bucket_index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *out_value = current->value;
            return 1;
        }
        current = current->next;
    }
    return 0; 
}

void print_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* current = table->buckets[i];
        while (current != NULL) {
            printf("[%s: %d] -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    HashTable* my_table = create_table();

    insert(my_table, "apple", 100);
    insert(my_table, "banana", 250);
    insert(my_table, "orange", 400);
    insert(my_table, "grapes", 120);

    printf("--- Current Hash Table Structure ---\n");
    print_table(my_table);

    printf("\n--- Searching for keys ---\n");
    int val;
    if (search(my_table, "banana", &val)) {
        printf("Found banana! Value is %d\n", val);
    } else {
        printf("Banana not found.\n");
    }

    return 0;
}




#include <stdio.h>
#include <stdlib.h>

void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiply(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int T1[k][k], T2[k][k];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    multiply(k, A11, B11, T1);
    multiply(k, A12, B21, T2);
    add(k, T1, T2, C11);

    multiply(k, A11, B12, T1);
    multiply(k, A12, B22, T2);
    add(k, T1, T2, C12);

    multiply(k, A21, B11, T1);
    multiply(k, A22, B21, T2);
    add(k, T1, T2, C21);

    multiply(k, A21, B12, T1);
    multiply(k, A22, B22, T2);
    add(k, T1, T2, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main() {
    int n;
    printf("Enter matrix size: ");
    scanf("%d", &n);
    int A[n][n], B[n][n], C[n][n];
    printf("Enter first matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    printf("Enter second matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    multiply(n, A, B, C);
    printf("Result:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}
