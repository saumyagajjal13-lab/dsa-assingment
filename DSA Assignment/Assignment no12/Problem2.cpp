#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Faculty {
    int id;
    string name;
    string department;
    string subject;
    int experience;
    bool isDeleted;
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<Faculty> table;

    int hashFunction(int id) {
        return id % TABLE_SIZE;
    }

    int linearProbe(int index, int id) {
        int original = index;
        while (table[index].id != -1 && table[index].id != id && !table[index].isDeleted) {
            index = (index + 1) % TABLE_SIZE;
            if (index == original) return -1;
        }
        return index;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].id = -1;
            table[i].isDeleted = false;
        }
    }

    void insertFaculty(int id, string name, string dept, string subj, int exp) {
        int index = hashFunction(id);
        index = linearProbe(index, id);
        
        if (index == -1) {
            cout << "Hash table is full!" << endl;
            return;
        }
        
        table[index] = {id, name, dept, subj, exp, false};
        cout << "Faculty " << name << " inserted at index " << index << endl;
    }

    void searchFaculty(int id) {
        int index = hashFunction(id);
        int original = index;
        
        while (true) {
            if (table[index].id == id && !table[index].isDeleted) {
                cout << "Faculty Found at index " << index << ":\n";
                cout << "ID: " << table[index].id << "\nName: " << table[index].name 
                     << "\nDepartment: " << table[index].department 
                     << "\nSubject: " << table[index].subject 
                     << "\nExperience: " << table[index].experience << " years" << endl;
                return;
            }
            if (table[index].id == -1 && !table[index].isDeleted) break;
            
            index = (index + 1) % TABLE_SIZE;
            if (index == original) break;
        }
        cout << "Faculty with ID " << id << " not found!" << endl;
    }

    void deleteFaculty(int id) {
        int index = hashFunction(id);
        int original = index;
        
        while (true) {
            if (table[index].id == id && !table[index].isDeleted) {
                table[index].isDeleted = true;
                cout << "Faculty with ID " << id << " deleted from index " << index << endl;
                return;
            }
            if (table[index].id == -1 && !table[index].isDeleted) break;
            
            index = (index + 1) % TABLE_SIZE;
            if (index == original) break;
        }
        cout << "Faculty with ID " << id << " not found for deletion!" << endl;
    }

    void displayTable() {
        cout << "\nHash Table Contents:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            if (table[i].id == -1 && !table[i].isDeleted) {
                cout << "Empty";
            } else if (table[i].isDeleted) {
                cout << "Deleted";
            } else {
                cout << "[" << table[i].id << ":" << table[i].name << "]";
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