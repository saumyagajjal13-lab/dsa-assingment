#include <iostream>
#include <string>
using namespace std;

#define SIZE 15

class FacultyDB {
    struct Faculty {
        int id;
        string name;
        string dept;
        bool occupied;
        Faculty() { occupied = false; }
    } table[SIZE];

public:
    int hash(int id) {
        return id % SIZE;        // MOD FUNCTION
    }

    void insert(int id, string name, string dept) {
        int index = hash(id);
        int start = index;

        while (table[index].occupied) {
            index = (index + 1) % SIZE;
            if (index == start) {
                cout << "\nDatabase Full!";
                return;
            }
        }

        table[index].id = id;
        table[index].name = name;
        table[index].dept = dept;
        table[index].occupied = true;
        cout << "\nFaculty Added.";
    }

    void search(int id) {
        int index = hash(id);
        int start = index;

        while (table[index].occupied) {
            if (table[index].id == id) {
                cout << "\nFaculty Found!";
                cout << "\nID: " << table[index].id;
                cout << "\nName: " << table[index].name;
                cout << "\nDepartment: " << table[index].dept << endl;
                return;
            }
            index = (index + 1) % SIZE;
            if (index == start) break;
        }
        cout << "\nFaculty Not Found!";
    }

    void display() {
        cout << "\n---- Faculty Database ----\n";
        for (int i = 0; i < SIZE; i++) {
            if (table[i].occupied)
                cout << i << " → " << table[i].id << " | "
                     << table[i].name << " | " << table[i].dept << endl;
            else
                cout << i << " → [Empty]\n";
        }
    }
};

int main() {
    FacultyDB F;
    int ch, id;
    string name, dept;

    do {
        cout << "\n1.Add Faculty\n2.Search Faculty\n3.Display All\n4.Exit\nEnter choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter Faculty ID: "; cin >> id;
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Department: "; cin >> dept;
                F.insert(id, name, dept);
                break;
            case 2:
                cout << "Enter Faculty ID to Search: "; cin >> id;
                F.search(id);
                break;
            case 3:
                F.display();
                break;
        }
    } while (ch != 4);
}
