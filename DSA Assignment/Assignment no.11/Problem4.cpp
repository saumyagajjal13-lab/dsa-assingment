#include <iostream>
#include <string>
using namespace std;

class HashTable {
    struct Node {
        int roll;
        string name;
        string course;
        Node* next;
        Node(int r, string n, string c) {
            roll = r;
            name = n;
            course = c;
            next = NULL;
        }
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

    void insert(int roll, string name, string course) {
        int index = hash(roll);
        Node* newNode = new Node(roll, name, course);
        newNode->next = table[index];
        table[index] = newNode;
        cout << "\nStudent Record Inserted.";
    }

    void search(int roll) {
        int index = hash(roll);
        Node* temp = table[index];
        while (temp) {
            if (temp->roll == roll) {
                cout << "\nRecord Found!\n";
                cout << "Roll: " << temp->roll << "\nName: " << temp->name << "\nCourse: " << temp->course << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\nRecord Not Found!";
    }

    void deleteRecord(int roll) {
        int index = hash(roll);
        Node* temp = table[index];
        Node* prev = NULL;

        while (temp) {
            if (temp->roll == roll) {
                if (prev) prev->next = temp->next;
                else table[index] = temp->next;
                delete temp;
                cout << "\nRecord Deleted!";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "\nRecord Not Found!";
    }

    void display() {
        cout << "\n----- STUDENT HASH TABLE -----\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " → ";
            Node* temp = table[i];
            while (temp) {
                cout << "[" << temp->roll << ", " << temp->name << ", " << temp->course << "] → ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    HashTable HT;
    int ch, roll;
    string name, course;

    do {
        cout << "\n1.Insert\n2.Search\n3.Delete\n4.Display\n5.Exit\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Course: "; cin >> course;
                HT.insert(roll, name, course);
                break;
            case 2:
                cout << "Enter Roll No to Search: "; cin >> roll;
                HT.search(roll);
                break;
            case 3:
                cout << "Enter Roll No to Delete: "; cin >> roll;
                HT.deleteRecord(roll);
                break;
            case 4:
                HT.display();
                break;
        }
    } while (ch != 5);
}
