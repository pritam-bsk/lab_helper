#include <iostream>
using namespace std;

class Stack {
    int a[5], top;
public:
    Stack() { top = -1; }

    void push(int x) {
        if (top == 4) cout << "Overflow\n";
        else a[++top] = x;
    }

    void pop() {
        if (top == -1) cout << "Underflow\n";
        else cout << "Popped: " << a[top--] << endl;
    }

    void display() {
        if (top == -1) cout << "Empty\n";
        else for (int i = top; i >= 0; i--) cout << a[i] << " ";
        cout << endl;
    }
};

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();
    s.pop();
    s.display();
}

#include <iostream>
#include <stack>
using namespace std;

class Stack {
    stack<char> s;
public:
    void push(char c) { s.push(c); }
    void pop() { s.pop(); }
    char top() { return s.top(); }
    bool empty() { return s.empty(); }
};

int main() {
    string str;
    cin >> str;
    Stack s;
    bool ok = true;

    for (char c : str) {
        if (c == '(' || c == '{' || c == '[')
            s.push(c);
        else if (c == ')' || c == '}' || c == ']') {
            if (s.empty()) { ok = false; break; }
            char t = s.top();
            if ((c == ')' && t != '(') ||
                (c == '}' && t != '{') ||
                (c == ']' && t != '[')) {
                ok = false;
                break;
            }
            s.pop();
        }
    }

    if (!s.empty()) ok = false;
    cout << (ok ? "Balanced" : "Not Balanced");
}
#include <iostream>
using namespace std;

class Stack {
    int a[32], top;
public:
    Stack() { top = -1; }
    void push(int x) { a[++top] = x; }
    int pop() { return a[top--]; }
    bool empty() { return top == -1; }
};

int main() {
    int n;
    cin >> n;
    Stack s;

    if (n == 0) cout << 0;
    else {
        while (n) {
            s.push(n % 2);
            n /= 2;
        }
        while (!s.empty())
            cout << s.pop();
    }
}

#include <iostream>
#include <stack>
using namespace std;

class Stack {
    stack<char> s;
public:
    void push(char c) { s.push(c); }
    void pop() { s.pop(); }
    char top() { return s.top(); }
    bool empty() { return s.empty(); }
};

int priority(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int main() {
    string infix, postfix = "";
    cin >> infix;
    Stack s;

    for (char c : infix) {
        if (isalnum(c))
            postfix += c;
        else if (c == '(')
            s.push(c);
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && priority(s.top()) >= priority(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    cout << postfix;
}

#include <iostream>
using namespace std;

class Queue {
    int a[5], front, rear;
public:
    Queue() { front = 0; rear = -1; }

    void insert(int x) {
        if (rear == 4) cout << "Overflow\n";
        else a[++rear] = x;
    }

    void remove() {
        if (front > rear) cout << "Underflow\n";
        else cout << "Deleted: " << a[front++] << endl;
    }

    void display() {
        if (front > rear) cout << "Empty\n";
        else {
            for (int i = front; i <= rear; i++) cout << a[i] << " ";
            cout << endl;
        }
    }
};

int main() {
    Queue q;
    q.insert(10);
    q.insert(20);
    q.insert(30);
    q.display();
    q.remove();
    q.display();
}


#include <iostream>
using namespace std;

class Queue {
    int a[5], front, rear;
public:
    Queue() { front = rear = -1; }

    void insert(int x) {
        if ((rear + 1) % 5 == front) {
            cout << "Overflow\n";
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % 5;
        a[rear] = x;
    }

    void remove() {
        if (front == -1) {
            cout << "Underflow\n";
            return;
        }
        cout << "Deleted: " << a[front] << endl;
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % 5;
    }

    void display() {
        if (front == -1) {
            cout << "Empty\n";
            return;
        }
        int i = front;
        while (true) {
            cout << a[i] << " ";
            if (i == rear) break;
            i = (i + 1) % 5;
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    q.insert(10);
    q.insert(20);
    q.insert(30);
    q.display();
    q.remove();
    q.insert(40);
    q.display();
}


#include <iostream>
using namespace std;

class Queue {
    int a[10], front, rear;
public:
    Queue() { front = 0; rear = -1; }

    void add(int x) {
        if (rear == 9) cout << "Queue Full\n";
        else a[++rear] = x;
    }

    void serve() {
        if (front > rear) cout << "No customers\n";
        else cout << a[front++] << " is served first\n";
    }

    void next() {
        if (front > rear) cout << "No customers\n";
        else cout << "Next: " << a[front] << endl;
    }

    void display() {
        for (int i = front; i <= rear; i++)
            cout << a[i] << " ";
        cout << endl;
    }
};

int main() {
    Queue q;
    q.add(101);
    q.add(102);
    q.add(103);

    q.display();
    q.next();
    q.serve();
}

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Palindrome {
    string s;
    stack<char> st;
    queue<char> q;

public:
    Palindrome(string x) {
        s = x;
        for (char c : s) {
            st.push(c);
            q.push(c);
        }
    }

    bool check() {
        while (!st.empty()) {
            if (st.top() != q.front())
                return false;
            st.pop();
            q.pop();
        }
        return true;
    }
};

int main() {
    string s;
    cin >> s;

    Palindrome p(s);

    if (p.check())
        cout << "Palindrome";
    else
        cout << "Not a palindrome";
}
