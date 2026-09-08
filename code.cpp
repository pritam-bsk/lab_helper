#include <iostream>
using namespace std;

class ExamRecord {
    int *marks, n, id;

public:
    ExamRecord(int i, int s) {
        id = i;
        n = s;
        marks = new int[n];
    }

    ~ExamRecord() {
        delete[] marks;
    }

    void input() {
        cout << "Enter marks: ";
        for (int *p = marks; p < marks + n; p++)
            cin >> *p;
    }

    void display() {
        cout << "Student " << id << ": ";
        for (int *p = marks; p < marks + n; p++)
            cout << *p << " ";
        cout << "\n";
    }

    int calculateResult() {
        int sum = 0;
        for (int *p = marks; p < marks + n; p++)
            sum += *p;
        return sum;
    }

    void calculateResult(int maxMarks, int &total, float &percentage) {
        total = calculateResult();
        percentage = (float)total / maxMarks * 100;
    }

    ExamRecord operator+(ExamRecord &x) {
        ExamRecord temp(0, n);
        for (int i = 0; i < n; i++)
            temp.marks[i] = marks[i] + x.marks[i];
        return temp;
    }

    friend void findTopper(ExamRecord **, int);
};

void findTopper(ExamRecord **a, int n) {
    int pos = 0;
    for (int i = 1; i < n; i++)
        if (a[i]->calculateResult() > a[pos]->calculateResult())
            pos = i;

    cout << "Topper: Student " << a[pos]->id << "\n";
}

int main() {
    int n, s;
    cout << "Enter students and subjects: ";
    cin >> n >> s;

    ExamRecord **a = new ExamRecord*[n];

    for (int i = 0; i < n; i++) {
        a[i] = new ExamRecord(i + 1, s);
        a[i]->input();
    }

    for (int i = 0; i < n; i++) {
        a[i]->display();
        cout << "Total: " << a[i]->calculateResult() << "\n";
        int total;
        float percentage;
        a[i]->calculateResult(s * 100, total, percentage);
        cout << "Percentage: " << percentage << "%\n";
    }

    findTopper(a, n);

    if (n >= 2) {
        ExamRecord c = *a[0] + *a[1];
        cout << "Combined marks of Student 1 and 2:\n";
        c.display();
    }

    for (int i = 0; i < n; i++)
        delete a[i];
    delete[] a;
}


#include <iostream>
using namespace std;

class Warehouse {
    int n;
    int *qty;
    float *price;

public:
    Warehouse(int x) {
        n = x;
        qty = new int[n];
        price = new float[n];
    }

    ~Warehouse() {
        delete[] qty;
        delete[] price;
    }

    void input() {
        for (int i = 0; i < n; i++)
            cin >> *(qty + i) >> *(price + i);
    }

    float calculateValue(int i) {
        return *(qty + i) * *(price + i);
    }

    float calculateValue() {
        float total = 0;
        for (int i = 0; i < n; i++)
            total += calculateValue(i);
        return total;
    }

    Warehouse operator+(Warehouse &w) {
        Warehouse temp(n);
        for (int i = 0; i < n; i++) {
            temp.qty[i] = qty[i] + w.qty[i];
            temp.price[i] = price[i];
        }
        return temp;
    }

    friend void compareStock(Warehouse &, Warehouse &);
};

void compareStock(Warehouse &a, Warehouse &b) {
    if (a.calculateValue() > b.calculateValue())
        cout << "Warehouse 1 has greater value\n";
    else if (a.calculateValue() < b.calculateValue())
        cout << "Warehouse 2 has greater value\n";
    else
        cout << "Both warehouses have equal value\n";
}

int main() {
    int n;
    cout << "Enter number of products: ";
    cin >> n;

    Warehouse *w1 = new Warehouse(n);
    Warehouse *w2 = new Warehouse(n);

    cout << "Enter quantity and price for Warehouse 1:\n";
    w1->input();

    cout << "Enter quantity and price for Warehouse 2:\n";
    w2->input();

    cout << "Warehouse 1 total value: " << w1->calculateValue() << "\n";
    cout << "Warehouse 2 total value: " << w2->calculateValue() << "\n";

    compareStock(*w1, *w2);

    Warehouse w3 = *w1 + *w2;
    cout << "Combined warehouse value: " << w3.calculateValue() << "\n";

    delete w1;
    delete w2;
}


#include <iostream>
using namespace std;

class VehicleFleet {
    int id;
    float *fuel;

public:
    VehicleFleet(int x) {
        id = x;
        fuel = new float[5];
        cout << "Constructor: Vehicle " << id << "\n";
    }

    ~VehicleFleet() {
        cout << "Destructor: Vehicle " << id << "\n";
        delete[] fuel;
    }

    void input() {
        for (float *p = fuel; p < fuel + 5; p++)
            cin >> *p;
    }

    float calculateFuel() {
        float s = 0;
        for (float *p = fuel; p < fuel + 5; p++)
            s += *p;
        return s;
    }

    float calculateFuel(int a, int b) {
        float s = 0;
        for (int i = a - 1; i < b; i++)
            s += *(fuel + i);
        return s;
    }

    VehicleFleet operator+(VehicleFleet &v) {
        VehicleFleet temp(0);
        for (int i = 0; i < 5; i++)
            temp.fuel[i] = fuel[i] + v.fuel[i];
        return temp;
    }

    friend void compareVehicles(VehicleFleet &, VehicleFleet &);
};

void compareVehicles(VehicleFleet &a, VehicleFleet &b) {
    if (a.calculateFuel() > b.calculateFuel())
        cout << "Vehicle 1 consumed more fuel\n";
    else if (a.calculateFuel() < b.calculateFuel())
        cout << "Vehicle 2 consumed more fuel\n";
    else
        cout << "Both consumed equal fuel\n";
}

int main() {
    int n;
    cout << "Enter number of vehicles: ";
    cin >> n;

    VehicleFleet **v = new VehicleFleet*[n];

    for (int i = 0; i < n; i++) {
        v[i] = new VehicleFleet(i + 1);
        cout << "Enter 5-day fuel consumption: ";
        v[i]->input();
    }

    for (int i = 0; i < n; i++)
        cout << "Vehicle " << i + 1 << " total: "
             << v[i]->calculateFuel() << "\n";

    if (n >= 2) {
        compareVehicles(*v[0], *v[1]);
        VehicleFleet x = *v[0] + *v[1];
        cout << "Combined 5-day consumption: ";
        for (int i = 1; i <= 5; i++)
            cout << x.calculateFuel(i, i) << " ";
        cout << "\n";
    }

    for (int i = 0; i < n; i++)
        delete v[i];
    delete[] v;
}


#include <iostream>
using namespace std;

class ElectricityUsage {
    int n;
    float *units;

public:
    ElectricityUsage(int x) {
        n = x;
        units = new float[n];
    }

    ~ElectricityUsage() {
        delete[] units;
    }

    void input() {
        for (float *p = units; p < units + n; p++)
            cin >> *p;
    }

    float calculateBill(float rate) {
        return *units * rate;
    }

    float calculateBill(float rate, int count) {
        float total = 0;
        for (int i = 0; i < count && i < n; i++)
            total += *(units + i);
        return total * rate;
    }

    ElectricityUsage operator+(ElectricityUsage &e) {
        ElectricityUsage temp(n);
        for (int i = 0; i < n; i++)
            temp.units[i] = units[i] + e.units[i];
        return temp;
    }

    float total() {
        float s = 0;
        for (float *p = units; p < units + n; p++)
            s += *p;
        return s;
    }

    friend void compareUsage(ElectricityUsage &, ElectricityUsage &);
};

void compareUsage(ElectricityUsage &a, ElectricityUsage &b) {
    if (a.total() > b.total())
        cout << "Group 1 consumed more electricity\n";
    else if (a.total() < b.total())
        cout << "Group 2 consumed more electricity\n";
    else
        cout << "Both groups consumed equal electricity\n";
}

int main() {
    int n;
    float rate;

    cout << "Enter number of consumers: ";
    cin >> n;

    ElectricityUsage *a = new ElectricityUsage(n);
    ElectricityUsage *b = new ElectricityUsage(n);

    cout << "Enter units for Group 1: ";
    a->input();

    cout << "Enter units for Group 2: ";
    b->input();

    cout << "Enter rate per unit: ";
    cin >> rate;

    cout << "Group 1 bill: " << a->calculateBill(rate, n) << "\n";
    cout << "Group 2 bill: " << b->calculateBill(rate, n) << "\n";

    compareUsage(*a, *b);

    ElectricityUsage c = *a + *b;
    cout << "Combined bill: " << c.calculateBill(rate, n) << "\n";

    delete a;
    delete b;
}


#include <iostream>
using namespace std;

class Patient {
    int id, n;
    int *health;

public:
    Patient(int i, int x) {
        id = i;
        n = x;
        health = new int[n];
    }

    ~Patient() {
        delete[] health;
    }

    void input() {
        for (int *p = health; p < health + n; p++)
            cin >> *p;
    }

    int calculateScore(int x) {
        return x;
    }

    int calculateScore(int a, int b, int c) {
        return a + b + c;
    }

    int total() {
        int s = 0;
        for (int *p = health; p < health + n; p++)
            s += *p;
        return s;
    }

    Patient operator+(Patient &p) {
        Patient temp(0, n);
        for (int i = 0; i < n; i++)
            temp.health[i] = health[i] + p.health[i];
        return temp;
    }

    friend void findHealthiest(Patient **, int);
};

void findHealthiest(Patient **p, int n) {
    int pos = 0;

    for (int i = 1; i < n; i++)
        if (p[i]->total() > p[pos]->total())
            pos = i;

    cout << "Healthiest patient: " << p[pos]->id << "\n";
    cout << "Overall score: " << p[pos]->total() << "\n";
}

int main() {
    int n, sessions;

    cout << "Enter number of patients and sessions: ";
    cin >> n >> sessions;

    Patient **p = new Patient*[n];

    for (int i = 0; i < n; i++) {
        p[i] = new Patient(i + 1, sessions);
        cout << "Enter health readings: ";
        p[i]->input();
        cout << "Score: " << p[i]->total() << "\n";
    }

    findHealthiest(p, n);

    if (n >= 2) {
        Patient x = *p[0] + *p[1];
        cout << "Combined health readings: ";
        x.input();
    }

    for (int i = 0; i < n; i++)
        delete p[i];
    delete[] p;
}
