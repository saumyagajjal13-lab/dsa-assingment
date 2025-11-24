#include <iostream>
#include <string>
using namespace std;

#define SIZE 20

class FacultyDB {
    struct Faculty {
        int id;
        string name;
        string department;
        string qualification;
        bool occupied;
        bool deleted;
        Faculty() {
            occupied = false;
            deleted = false;
        }
    } table[SIZE];

    int hash(int id) {
        return id % SIZE;   // MOD HASH FUNCTION
    }

public:
    void insert(int id, string name, string dept, string qualification) {
        int index = hash(id);
        int start = index;

        while (table[index].occupied && !table[index].deleted) {
            index = (index + 1) % SIZE;
            if (index == start) {
                cout << "\nDatabase Full!";
                return;
            }
        }

        table[index].id = id;
        table[index].name = name;
        table[index].department = dept;
        table[index].qualification = qualification;
        table[index].occupied = true;
        table[index].deleted = false;
        cout << "\nFaculty Added Successfully.";
    }

    void search(int id) {
        int index = hash(id);
        int start = index;

        while (table[index].occupied) {
            if (table[index].id == id && !table[index].deleted) {
                cout << "\nFaculty Found!\n"
                     << "ID: " << table[index].id << "\nName: " << table[index].name
                     << "\nDepartment: " << table[index].department
                     << "\nQualification: " << table[index].qualification << endl;
                return;
            }
            index = (index + 1) % SIZE;
            if (index == start) break;
        }
        cout << "\nFaculty Not Found!";
    }

    void deleteRecord(int id) {
        int index = hash(id);
        int start = index;

        while (table[index].occupied) {
            if (table[index].id == id && !table[index].deleted) {
                table[index].deleted = true;
                cout << "\nRecord Deleted Successfully!";
                return;
            }
            index = (index + 1) % SIZE;
            if (index == start) break;
        }
        cout << "\nRecord Not Found!";
    }

    void display() {
        cout << "\n------ FACULTY DATABASE ------\n";
        for (int i = 0; i < SIZE; i++) {
            if (table[i].occupied && !table[i].deleted) {
                cout << i << " → " << table[i].id << " | " << table[i].name
                     << " | " << table[i].department
                     << " | " << table[i].qualification << endl;
            } else {
                cout << i << " → [EMPTY]\n";
            }
        }
    }
};

int main() {
    FacultyDB F;
    int ch, id;
    string name, dept, qualification;

    do {
        cout << "\n1.Add Faculty\n2.Search Faculty\n3.Delete Faculty\n4.Display All\n5.Exit\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Enter Faculty ID: "; cin >> id;
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Department: "; cin >> dept;
                cout << "Enter Qualification: "; cin >> qualification;
                F.insert(id, name, dept, qualification);
                break;
            case 2:
                cout << "Enter Faculty ID to Search: "; cin >> id;
                F.search(id);
                break;
            case 3:
                cout << "Enter Faculty ID to Delete: "; cin >> id;
                F.deleteRecord(id);
                break;
            case 4:
                F.display();
                break;
        }
    } while (ch != 5);
}
