#include <iostream>
using namespace std;

class Stack {
    int *arr;
    int top;
    int size;

public:
    Stack(int n) {
        size = n;
        arr = new int[size];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == size - 1;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack is full." << endl;
            return;
        }

        arr[++top] = value;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Popped element: " << arr[top--] << endl;
    }

    void peek() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Top element: " << arr[top] << endl;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Stack: ";

        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";

        cout << endl;
    }
};

int main() {
    int n;

    cout << "Enter stack size: ";
    cin >> n;

    Stack s(n);

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();
    s.peek();

    s.pop();
    s.display();

    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;
    cout << "Is stack full? " << (s.isFull() ? "Yes" : "No") << endl;

    return 0;
}

#include <iostream>
using namespace std;

class Stack {
    int *arr;
    int top;
    int size;

public:
    Stack(int n) {
        size = n;
        arr = new int[size];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        if (top == size - 1)
            return;

        arr[++top] = value;
    }

    int pop() {
        if (top == -1)
            return -1;

        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    int n;

    cout << "Enter number of integers: ";
    cin >> n;

    Stack s(n);

    cout << "Enter " << n << " integers: ";

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        s.push(value);
    }

    cout << "Reverse order: ";

    while (!s.isEmpty())
        cout << s.pop() << " ";

    cout << endl;

    return 0;
}


#include <iostream>
using namespace std;

class Queue {
    int *arr;
    int front;
    int rear;
    int size;

public:
    Queue(int n) {
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    ~Queue() {
        delete[] arr;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return rear == size - 1;
    }

    void insert(int value) {
        if (isFull()) {
            cout << "Queue is full." << endl;
            return;
        }

        if (front == -1)
            front = 0;

        arr[++rear] = value;
    }

    void remove() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Deleted element: " << arr[front] << endl;

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Queue: ";

        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";

        cout << endl;
    }

    void search(int value) {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        for (int i = front; i <= rear; i++) {
            if (arr[i] == value) {
                cout << value << " found at position "
                     << i - front + 1 << endl;
                return;
            }
        }

        cout << value << " not found in the queue." << endl;
    }
};

int main() {
    Queue q(5);

    q.insert(10);
    q.insert(20);
    q.insert(30);
    q.insert(40);

    q.display();

    q.search(30);
    q.search(50);

    q.remove();

    q.display();

    return 0;
}

#include <iostream>
using namespace std;

class CircularQueue {
    int *arr;
    int front;
    int rear;
    int size;

public:
    CircularQueue(int n) {
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % size == front;
    }

    void insert(int value) {
        if (isFull()) {
            cout << "Queue is full." << endl;
            return;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % size;
        }

        arr[rear] = value;
    }

    void remove() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Deleted element: " << arr[front] << endl;

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % size;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Queue: ";

        int i = front;

        while (true) {
            cout << arr[i] << " ";

            if (i == rear)
                break;

            i = (i + 1) % size;
        }

        cout << endl;
    }
};

int main() {
    CircularQueue q(5);

    q.insert(10);
    q.insert(20);
    q.insert(30);
    q.insert(40);

    q.display();

    q.remove();
    q.remove();

    q.display();

    q.insert(50);
    q.insert(60);

    q.display();

    q.insert(70);

    q.display();

    return 0;
}

#include <iostream>
using namespace std;

class LinkedList {
    struct Node {
        int data;
        Node *next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node *head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insertBeginning(int value) {
        Node *newNode = new Node(value);

        newNode->next = head;
        head = newNode;
    }

    void insertEnd(int value) {
        Node *newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node *temp = head;

        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
    }

    void display() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head;

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    int countNodes() {
        int count = 0;
        Node *temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        return count;
    }

    ~LinkedList() {
        Node *temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    } 
};

int main() {
    LinkedList list;

    list.insertBeginning(20);
    list.insertBeginning(10);

    list.insertEnd(30);
    list.insertEnd(40);

    cout << "Linked List: ";
    list.display();

    cout << "Total nodes: " << list.countNodes() << endl;

    return 0;
}

#include <iostream>
using namespace std;

class LinkedList {
    struct Node {
        int data;
        Node *next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node *head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insertEnd(int value) {
        Node *newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node *temp = head;

        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
    }

    void insertAtPosition(int value, int position) {
        if (position < 1) {
            cout << "Invalid position." << endl;
            return;
        }

        Node *newNode = new Node(value);

        if (position == 1) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *temp = head;

        for (int i = 1; i < position - 1 && temp != nullptr; i++)
            temp = temp->next;

        if (temp == nullptr) {
            delete newNode;
            cout << "Invalid position." << endl;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    void display() {
        Node *temp = head;

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    ~LinkedList() {
        Node *temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);
    list.insertEnd(40);

    cout << "Original List: ";
    list.display();

    int position, value;

    cout << "Enter position: ";
    cin >> position;

    cout << "Enter value: ";
    cin >> value;

    list.insertAtPosition(value, position);

    cout << "Updated List: ";
    list.display();

    return 0;
}





#include <iostream>
using namespace std;

class LinkedList {
    struct Node {
        int data;
        Node *next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node *head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insertEnd(int value) {
        Node *newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node *temp = head;

        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
    }

    void reverse() {
        Node *previous = nullptr;
        Node *current = head;
        Node *next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }

    void display() {
        Node *temp = head;

        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }

        cout << "NULL" << endl;
    }

    ~LinkedList() {
        Node *temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);
    list.insertEnd(40);

    cout << "Original: ";
    list.display();

    list.reverse();

    cout << "Reversed: ";
    list.display();

    return 0;
}
