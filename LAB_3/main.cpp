#include <iostream>
#include <string>
using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;
};


Page* head = nullptr;
Page* tail = nullptr;
Page* current = nullptr;


void inputTime(int t[3]) {
    cout << "Enter time (Hour Minute Second): ";
    cin >> t[0] >> t[1] >> t[2];
}


void visitPage() {
    Page* newPage = new Page();
    cout << "Enter URL: ";
    cin >> newPage->url;
    cout << "Enter Title: ";
    cin >> newPage->title;
    inputTime(newPage->accessTime);

    newPage->next = nullptr;
    newPage->prev = nullptr;

    if (head == nullptr) {
        head = tail = current = newPage;
    }
    else {
        tail->next = newPage;
        newPage->prev = tail;
        tail = newPage;
        current = newPage;
    }
}


void goBack() {
    if (current && current->prev) {
        current = current->prev;
        cout << "Moved Back.\n";
    }
    else {
        cout << "No previous page.\n";
    }
}


void goForward() {
    if (current && current->next) {
        current = current->next;
        cout << "Moved Forward.\n";
    }
    else {
        cout << "No next page.\n";
    }
}


void deleteCurrent() {
    if (!current) return;

    Page* temp = current;

    if (current == head && current == tail) {
        head = tail = current = nullptr;
    }
    else if (current == head) {
        head = head->next;
        head->prev = nullptr;
        current = head;
    }
    else if (current == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        current = tail;
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
    }

    delete temp;
    cout << "Page deleted.\n";
}


void displayHistory() {
    if (!head) {
        cout << "History is empty.\n";
        return;
    }

    Page* temp = head;
    int i = 1;

    while (temp != nullptr) {
        cout << i++ << ". ";

        if (temp == current)
            cout << "[CURRENT] ";

        cout << temp->title << " (" << temp->url << ") ";

        cout << "Time: ";
        for (int j = 0; j < 3; j++) {
            cout << temp->accessTime[j];
            if (j < 2) cout << ":";
        }

        cout << endl;
        temp = temp->next;
    }
}


void clearHistory() {
    Page* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}


void menu() {
    int choice;

    do {
        cout << "\n--- Browser History Manager ---\n";
        cout << "1. Visit Page\n";
        cout << "2. Back\n";
        cout << "3. Forward\n";
        cout << "4. Delete Current Page\n";
        cout << "5. Display History\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: visitPage(); break;
        case 2: goBack(); break;
        case 3: goForward(); break;
        case 4: deleteCurrent(); break;
        case 5: displayHistory(); break;
        case 0:
            clearHistory();
            cout << "Exiting and memory cleared.\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
