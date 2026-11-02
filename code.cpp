
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



#include <stdio.h>

struct Item {
    int weight;
    int profit;
    float ratio;
};

int main() {
    int n, capacity;
    float totalProfit = 0;

    struct Item item[100], temp;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    // Input weight and profit
    for (int i = 0; i < n; i++) {
        printf("Enter weight and profit of item %d: ", i + 1);
        scanf("%d %d", &item[i].weight,
                        &item[i].profit);

        item[i].ratio =
            (float)item[i].profit / item[i].weight;
    }

    // Sort items by profit/weight ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (item[i].ratio < item[j].ratio) {
                temp = item[i];
                item[i] = item[j];
                item[j] = temp;
            }
        }
    }

    // Greedy selection
    for (int i = 0; i < n; i++) {

        if (capacity == 0)
            break;

        if (item[i].weight <= capacity) {

            // Take the complete item
            capacity -= item[i].weight;
            totalProfit += item[i].profit;

            printf("Taken full item: %d\n", i + 1);
        }
        else {

            // Take fractional part
            float fraction =
                (float)capacity / item[i].weight;

            totalProfit += item[i].profit * fraction;

            printf("Taken fraction of item %d: %.2f\n",
                   i + 1, fraction);

            capacity = 0;
        }
    }

    printf("\nMaximum Profit = %.2f\n", totalProfit);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

// Structure of AVL Tree node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Find height of node
int height(struct Node *n) {
    if (n == NULL)
        return 0;

    return n->height;
}

// Find maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
struct Node* newNode(int key) {
    struct Node* node =
        (struct Node*)malloc(sizeof(struct Node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

// Calculate balance factor
int getBalance(struct Node *n) {
    if (n == NULL)
        return 0;

    return height(n->left) - height(n->right);
}

// Right rotation (LL case)
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left),
                        height(y->right));

    x->height = 1 + max(height(x->left),
                        height(x->right));

    return x;
}

// Left rotation (RR case)
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left),
                        height(x->right));

    y->height = 1 + max(height(y->left),
                        height(y->right));

    return y;
}

// Insert a node
struct Node* insert(struct Node* node, int key) {

    // Normal BST insertion
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);

    else if (key > node->key)
        node->right = insert(node->right, key);

    else
        return node;

    // Update height
    node->height = 1 + max(height(node->left),
                           height(node->right));

    // Find balance factor
    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find minimum value node
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Delete a node
struct Node* deleteNode(struct Node* root, int key) {

    // Normal BST deletion
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {

        // Node with zero or one child
        if (root->left == NULL ||
            root->right == NULL) {

            struct Node *temp = root->left ?
                                root->left : root->right;

            // No child
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            // One child
            else {
                *root = *temp;
            }

            free(temp);
        }

        // Node with two children
        else {
            struct Node* temp =
                minValueNode(root->right);

            root->key = temp->key;

            root->right =
                deleteNode(root->right, temp->key);
        }
    }

    // If tree becomes empty
    if (root == NULL)
        return root;

    // Update height
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // Calculate balance factor
    int balance = getBalance(root);

    // LL Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 &&
        getBalance(root->left) < 0) {

        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 &&
        getBalance(root->right) > 0) {

        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {

        printf("\n\n--- AVL TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &key);

                root = insert(root, key);

                printf("Node inserted successfully.\n");
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &key);

                root = deleteNode(root, key);

                printf("Deletion operation completed.\n");
                break;

            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
