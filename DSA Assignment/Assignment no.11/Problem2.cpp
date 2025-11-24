#include <iostream>
#include <string>
using namespace std;

class HashTable {
    struct Node {
        int roll;
        string name;
        Node *next;
        Node(int r, string n) { roll = r; name = n; next = NULL; }
    };
    static const int SIZE = 10;
    Node* table[SIZE];

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = NULL;
    }

    int hash(int key) {
        return key % SIZE;
    }

    void insert(int roll, string name) {
        int index = hash(roll);
        Node *newNode = new Node(roll, name);
        newNode->next = table[index];
        table[index] = newNode;
        cout << "\nInserted.";
    }

    void search(int roll) {
        int index = hash(roll);
        Node *temp = table[index];
        while (temp) {
            if (temp->roll == roll) {
                cout << "\nRecord Found!";
                cout << "\nRoll: " << temp->roll << "\nName: " << temp->name << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\nRecord Not Found!";
    }

    void display() {
        cout << "\n---- Hash Table ----\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " → ";
            Node *temp = table[i];
            while (temp) {
                cout << "[" << temp->roll << ", " << temp->name << "] → ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable HT;
    int ch, roll;
    string name;

    do {
        cout << "\n1.Insert\n2.Search\n3.Display\n4.Exit\nEnter choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Name: "; cin >> name;
                HT.insert(roll, name);
                break;
            case 2:
                cout << "Enter Roll to Search: "; cin >> roll;
                HT.search(roll);
                break;
            case 3:
                HT.display();
                break;
        }
    } while (ch != 4);
}
