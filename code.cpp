#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int key;
    struct Node *next;
};

int hash(int key) {
    return key % SIZE;
}

int main() {
    struct Node *table[SIZE] = {NULL};
    struct Node *p, *newnode;
    int n, key, index, collisions = 0, i;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter keys:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &key);
        index = hash(key);

        printf("\n%d -> h(%d) = %d", key, key, index);

        if (table[index] != NULL) {
            collisions++;
            printf(" -> Collision! Chain: ");

            p = table[index];
            while (p->next != NULL) {
                printf("%d -> ", p->key);
                p = p->next;
            }
            printf("%d", p->key);
        }

        newnode = malloc(sizeof(struct Node));
        newnode->key = key;
        newnode->next = NULL;

        if (table[index] == NULL)
            table[index] = newnode;
        else
            p->next = newnode;

        printf(" -> Inserted\n");
    }

    printf("\nFinal Hash Table:\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        p = table[i];

        if (p == NULL)
            printf("NULL");
        else {
            while (p != NULL) {
                printf("%d", p->key);
                if (p->next != NULL)
                    printf(" -> ");
                p = p->next;
            }
        }
        printf("\n");
    }

    printf("\nTotal collisions = %d\n", collisions);

    return 0;
}
