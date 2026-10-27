#include <iostream>
using namespace std;
template <class T>
T maximum(T a, T b, T c) {
    return max(a, max(b, c));
}
template <class T>
T minimum(T a, T b, T c) {
    return min(a, min(b, c));
}
template <class T>
T square(T a) {
    return a * a;
}
int main() {
    int a = 3, b = 7, c = 5;
    float x = 2.5, y = 4.5, z = 1.5;
    double p = 3.2, q = 1.8, r = 5.6;
    cout << "Integer: " << maximum(a,b,c) << " " << minimum(a,b,c) << " " << square(a) << endl;
    cout << "Float: " << maximum(x,y,z) << " " << minimum(x,y,z) << " " << square(x) << endl;
    cout << "Double: " << maximum(p,q,r) << " " << minimum(p,q,r) << " " << square(p) << endl;

    return 0;
}



#include <iostream>
using namespace std;
template <class T>
class Queue {
    T a[5];
    int f, r;
public:
    Queue() { f = r = -1; }
    void enqueue(T x) {
        if (r == 4) {
            cout << "Overflow\n";
            return;
        }
        if (f == -1) f = 0;
        a[++r] = x;
    }
    void dequeue() {
        if (f == -1 || f > r) {
            cout << "Underflow\n";
            return;
        }
        cout << "Removed: " << a[f++] << endl;
        if (f > r) f = r = -1;
    }
    void front() {
        if (f == -1) cout << "Queue empty\n";
        else cout << "Front: " << a[f] << endl;
    }
    void display() {
        if (f == -1) {
            cout << "Queue empty\n";
            return;
        }
        for (int i = f; i <= r; i++)
            cout << a[i] << " ";
        cout << endl;
    }
};

int main() {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();
    q.front();
    q.dequeue();
    q.display();

    Queue<char> c;
    c.enqueue('A');
    c.enqueue('B');
    c.enqueue('C');
    c.display();
    c.front();
    c.dequeue();
    c.display();

    return 0;
}




#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
template <class T>
class Polynomial {
    vector<T> a;
public:
    Polynomial(vector<T> v) : a(v) {}
    Polynomial operator+(const Polynomial& p) {
        vector<T> v(max(a.size(), p.a.size()), 0);
        for (int i = 0; i < a.size(); i++) v[i] += a[i];
        for (int i = 0; i < p.a.size(); i++) v[i] += p.a[i];
        return Polynomial(v);
    }
    Polynomial operator-(const Polynomial& p) {
        vector<T> v(max(a.size(), p.a.size()), 0);
        for (int i = 0; i < a.size(); i++) v[i] += a[i];
        for (int i = 0; i < p.a.size(); i++) v[i] -= p.a[i];
        return Polynomial(v);
    }
    Polynomial operator*(const Polynomial& p) {
        vector<T> v(a.size() + p.a.size() - 1, 0);
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < p.a.size(); j++)
                v[i + j] += a[i] * p.a[j];
        return Polynomial(v);
    }
    T evaluate(T x) {
        T result = 0;
        for (int i = a.size() - 1; i >= 0; i--)
            result = result * x + a[i];
        return result;
    }
    void display() {
        bool first = true;
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a[i] == 0) continue;
            if (!first) cout << (a[i] > 0 ? " + " : " - ");
            else if (a[i] < 0) cout << "-";
            T c = a[i] < 0 ? -a[i] : a[i];
            if (i == 0 || c != 1) cout << c;
            if (i > 0) cout << "x";
            if (i > 1) cout << "^" << i;
            first = false;
        }
        if (first) cout << "0";
        cout << endl;
    }
};

int main() {
    Polynomial<int> p({5, 2, 3});
    Polynomial<int> q({1, 4});
    cout << "P(x) = ";
    p.display();
    cout << "Q(x) = ";
    q.display();
    cout << "Addition: ";
    (p + q).display();
    cout << "Subtraction: ";
    (p - q).display();
    cout << "Multiplication: ";
    (p * q).display();
    cout << "P(2) = " << p.evaluate(2) << endl;

    Polynomial<double> r({5.5, 2.5, 3.5});
    cout << "Floating polynomial: ";
    r.display();
    cout << "R(2) = " << r.evaluate(2.0) << endl;

    return 0;
}
