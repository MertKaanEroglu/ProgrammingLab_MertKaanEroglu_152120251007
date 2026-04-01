#include <iostream>
#include <string>

using namespace std;



struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string customerName;
    string transactionType;
};


class MoneyStack {
    MoneyBundle* top = nullptr;
public:
    void push(string sn, string type, int c100, int c50, int c20) {
        MoneyBundle* newNode = new MoneyBundle{ sn, type, {c100, c50, c20}, top };
        top = newNode;
        cout << "Para destesi kasaya eklendi: " << sn << endl;
    }
    void pop() {
        if (!top) return;
        MoneyBundle* temp = top;
        top = top->next;
        delete temp;
    }

};


class CustomerQueue {
    Customer arr[5];
    int front = -1, rear = -1, size = 5;
public:
    bool isFull() { return (rear + 1) % size == front; }
    bool isEmpty() { return front == -1; }

    void enqueue(string name, string trans) {
        if (isFull()) { cout << "Sira dolu!" << endl; return; }
        if (isEmpty()) front = 0;
        rear = (rear + 1) % size;
        arr[rear] = { name, trans };
    }
    void dequeue() {
        if (isEmpty()) return;
        if (front == rear) front = rear = -1;
        else front = (front + 1) % size;
    }
};