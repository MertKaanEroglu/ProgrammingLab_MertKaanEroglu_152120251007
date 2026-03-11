#include <iostream>
using namespace std;

struct Node {
    string songName;
    Node* next;
};

Node* head = NULL;

void addSong(string name) {
    Node* newNode = new Node();

    newNode->songName = name;
    newNode->next = head;

    head = newNode;

    cout << "Song added successfully.\n";
}

void displaySongs() {
    Node* temp = head;
    int i = 1;

    if (temp == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    while (temp != NULL) {
        cout << i << ". " << temp->songName << endl;
        temp = temp->next;
        i++;
    }
}

void searchSong(string name) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->songName == name) {
            cout << "Song found!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Song not found.\n";
}

int main() {

    int choice;
    string name;

    do {
        cout << "\n--- Music Playlist Menu ---\n";
        cout << "1. Add Song\n";
        cout << "2. Search Song\n";
        cout << "3. List Songs\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1:
            cout << "Enter song name: ";
            getline(cin, name);
            addSong(name);
            break;

        case 2:
            cout << "Enter song to search: ";
            getline(cin, name);
            searchSong(name);
            break;

        case 3:
            displaySongs();
            break;

        case 4:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}