#include <iostream>
#include <string>
using namespace std;

#define SIZE 20

class HashTable {
    struct Student {
        int roll;
        string name;
        bool occupied;
        Student() { roll = 0; occupied = false; }
    };
    Student table[SIZE];

public:
    int hash(int key) {
        return key % SIZE;
    }

    void insert(int roll, string name) {
        int index = hash(roll);
        int start = index;

        while (table[index].occupied) {
            index = (index + 1) % SIZE;
            if (index == start) {
                cout << "\nHash Table Full!";
                return;
            }
        }

        table[index].roll = roll;
        table[index].name = name;
        table[index].occupied = true;
        cout << "\nRecord inserted.";
    }

    void search(int roll) {
        int index = hash(roll);
        int start = index;

        while (table[index].occupied) {
            if (table[index].roll == roll) {
                cout << "\nRecord Found!";
                cout << "\nRoll: " << table[index].roll;
                cout << "\nName: " << table[index].name << endl;
                return;
            }
            index = (index + 1) % SIZE;
            if (index == start) break;
        }
        cout << "\nRecord not found!";
    }

    void display() {
        cout << "\n----- Hash Table -----\n";
        for (int i = 0; i < SIZE; i++) {
            if (table[i].occupied)
                cout << i << " → " << table[i].roll << " | " << table[i].name << endl;
            else
                cout << i << " → [Empty]\n";
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
                cout << "Enter Roll No: ";
                cin >> roll;
                cout << "Enter Name: ";
                cin >> name;
                HT.insert(roll, name);
                break;
            case 2:
                cout << "Enter Roll to Search: ";
                cin >> roll;
                HT.search(roll);
                break;
            case 3:
                HT.display();
                break;
        }
    } while (ch != 4);
}
