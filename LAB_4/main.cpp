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
private:
    MoneyBundle* top;

public:
    MoneyStack() : top(nullptr) {}

    void push(string sn, string type, int c100, int c50, int c20) {
        MoneyBundle* newNode = new MoneyBundle;
        newNode->serialNumber = sn;
        newNode->currencyType = type;
        newNode->billCounts[0] = c100;
        newNode->billCounts[1] = c50;
        newNode->billCounts[2] = c20;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top == nullptr) return;
        MoneyBundle* temp = top;
        top = top->next;
        delete temp;
    }

    void display() {
        if (top == nullptr) {
            cout << "Safe is empty." << endl;
            return;
        }
        MoneyBundle* temp = top;
        while (temp != nullptr) {
            cout << "[" << temp->serialNumber << " | " << temp->currencyType
                << " | 100s:" << temp->billCounts[0] << " 50s:" << temp->billCounts[1]
                << " 20s:" << temp->billCounts[2] << "]" << endl;
            temp = temp->next;
        }
    }

    bool isEmpty() { return top == nullptr; }
};

class CustomerQueue {
private:
    Customer queue[5];
    int front, rear, size;
    const int capacity = 5;

public:
    CustomerQueue() : front(0), rear(-1), size(0) {}

    bool isFull() { return size == capacity; }
    bool isEmpty() { return size == 0; }

    void enqueue(string name, string type) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear].customerName = name;
        queue[rear].transactionType = type;
        size++;
    }

    void dequeue() {
        if (isEmpty()) return;
        front = (front + 1) % capacity;
        size--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No customers in line." << endl;
            return;
        }
        int count = 0;
        int i = front;
        while (count < size) {
            cout << "(" << queue[i].customerName << " - " << queue[i].transactionType << ") ";
            i = (i + 1) % capacity;
            count++;
        }
        cout << endl;
    }
};

int main() {
    MoneyStack safe;
    CustomerQueue line;
    int choice;

    while (true) {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Receive Money (Push)\n2. New Customer (Enqueue)\n3. Process Transaction\n4. Display Status\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string sn, ct;
            int b1, b2, b3;
            cout << "Serial: "; cin >> sn;
            cout << "Currency: "; cin >> ct;
            cout << "Counts (100 50 20): "; cin >> b1 >> b2 >> b3;
            safe.push(sn, ct, b1, b2, b3);
        }
        else if (choice == 2) {
            string name, type;
            cout << "Customer Name: "; cin >> name;
            cout << "Transaction (Deposit/Withdraw): "; cin >> type;
            line.enqueue(name, type);
        }
        else if (choice == 3) {
            if (line.isEmpty()) {
                cout << "Error: No customers." << endl;
            }
            else if (safe.isEmpty()) {
                cout << "Error: No money bundles." << endl;
            }
            else {
                line.dequeue();
                safe.pop();
                cout << "Transaction processed successfully." << endl;
            }
        }
        else if (choice == 4) {
            cout << "\n--- Current Safe (Stack) ---" << endl;
            safe.display();
            cout << "\n--- Waiting Customers (Queue) ---" << endl;
            line.display();
        }
        else if (choice == 5) {
            break;
        }
    }
    return 0;
}