#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    try {
        if (b == 0)
            throw b;

        cout << "Result: " << (double)a / b;
    }
    catch (int x) {
        cout << "Exception: Division by zero!";
    }

    return 0;
}&& key < node->right->key) {
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


#include <iostream>
using namespace std;

int main() {
    int choice;
    cin >> choice;

    try {
        if (choice == 1)
            throw 10;
        else if (choice == 2)
            throw 3.14;
        else if (choice == 3)
            throw string("String Exception");
        else
            throw 'A';
    }
    catch (int x) {
        cout << "Integer exception: " << x;
    }
    catch (double x) {
        cout << "Double exception: " << x;
    }
    catch (string x) {
        cout << x;
    }
    catch (...) {
        cout << "Unknown exception caught!";
    }

    return 0;
}

#include <iostream>
using namespace std;

int main() {
    double a, b;
    char op;

    cin >> a >> op >> b;

    try {
        switch (op) {
            case '+': cout << a + b; break;
            case '-': cout << a - b; break;
            case '*': cout << a * b; break;
            case '/':
                if (b == 0)
                    throw "Division by zero!";
                cout << a / b;
                break;
            default:
                throw "Invalid operator!";
        }
    }
    catch (const char* msg) {
        cout << "Exception: " << msg;
    }

    return 0;
}

#include <iostream>
using namespace std;

int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int index;

    cin >> index;

    try {
        if (index < 0 || index >= 5)
            throw index;

        cout << "Element: " << a[index];
    }
    catch (int x) {
        cout << "Exception: Invalid index " << x;
    }

    return 0;
}


#include <iostream>
using namespace std;

int main() {
    int marks;
    cin >> marks;

    try {
        if (marks < 0 || marks > 100)
            throw marks;

        cout << "Grade: ";

        if (marks >= 90)
            cout << "A+";
        else if (marks >= 80)
            cout << "A";
        else if (marks >= 70)
            cout << "B";
        else if (marks >= 60)
            cout << "C";
        else if (marks >= 40)
            cout << "D";
        else
            cout << "F";
    }
    catch (int x) {
        cout << "Exception: Invalid marks " << x;
    }

    return 0;
}



