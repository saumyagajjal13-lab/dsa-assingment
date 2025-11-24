#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

struct Faculty {
    int id;
    string name;
    string department;
    string subject;
    int experience;
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<list<Faculty>> table;

    int hashFunction(int id) {
        return id % TABLE_SIZE;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    void insertFaculty(int id, string name, string dept, string subj, int exp) {
        Faculty faculty = {id, name, dept, subj, exp};
        int index = hashFunction(id);
        table[index].push_back(faculty);
        cout << "Faculty " << name << " inserted at index " << index << endl;
    }

    void searchFaculty(int id) {
        int index = hashFunction(id);
        cout << "Searching at index " << index << endl;
        
        bool found = false;
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->id == id) {
                cout << "Faculty Found:\n";
                cout << "ID: " << it->id << "\nName: " << it->name 
                     << "\nDepartment: " << it->department 
                     << "\nSubject: " << it->subject 
                     << "\nExperience: " << it->experience << " years" << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Faculty with ID " << id << " not found!" << endl;
        }
    }

    void deleteFaculty(int id) {
        int index = hashFunction(id);
        bool found = false;
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->id == id) {
                table[index].erase(it);
                cout << "Faculty with ID " << id << " deleted!" << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Faculty with ID " << id << " not found for deletion!" << endl;
        }
    }

    void displayTable() {
        cout << "\nHash Table Contents:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            if (table[i].empty()) {
                cout << "Empty";
            } else {
                for (auto faculty : table[i]) {
                    cout << "[" << faculty.id << ":" << faculty.name << "] ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    int choice, id, exp;
    string name, dept, subj;

    do {
        cout << "\nFaculty Database Menu\n";
        cout << "1. Insert Faculty\n";
        cout << "2. Search Faculty\n";
        cout << "3. Delete Faculty\n";
        cout << "4. Display Table\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Faculty ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Department: ";
                cin >> dept;
                cout << "Enter Subject: ";
                cin >> subj;
                cout << "Enter Experience: ";
                cin >> exp;
                ht.insertFaculty(id, name, dept, subj, exp);
                break;
            case 2:
                cout << "Enter Faculty ID to search: ";
                cin >> id;
                ht.searchFaculty(id);
                break;
            case 3:
                cout << "Enter Faculty ID to delete: ";
                cin >> id;
                ht.deleteFaculty(id);
                break;
            case 4:
                ht.displayTable();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 5);

    return 0;
}