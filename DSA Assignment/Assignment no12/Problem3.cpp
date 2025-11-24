#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct Employee {
    int id;
    string name;
    string position;
    double salary;
    bool isEmpty;
};

class HashTable {
private:
    static const int TABLE_SIZE = 100;
    vector<Employee> table;

    int midSquareHash(int id) {
        long long square = (long long)id * id;
        string squareStr = to_string(square);
        int mid = squareStr.length() / 2;
        int digits = 2;
        
        string hashStr = squareStr.substr(mid - 1, digits);
        if (hashStr.length() < digits) {
            hashStr = string(digits - hashStr.length(), '0') + hashStr;
        }
        
        return stoi(hashStr) % TABLE_SIZE;
    }

    int linearProbe(int index) {
        int original = index;
        while (!table[index].isEmpty) {
            index = (index + 1) % TABLE_SIZE;
            if (index == original) return -1;
        }
        return index;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].isEmpty = true;
        }
    }

    void insertEmployee(int id, string name, string pos, double salary) {
        int index = midSquareHash(id);
        index = linearProbe(index);
        
        if (index == -1) {
            cout << "Hash table is full!" << endl;
            return;
        }
        
        table[index] = {id, name, pos, salary, false};
        cout << "Employee " << name << " inserted at index " << index << endl;
    }

    void searchEmployee(int id) {
        int index = midSquareHash(id);
        int original = index;
        
        while (true) {
            if (!table[index].isEmpty && table[index].id == id) {
                cout << "Employee Found at index " << index << ":\n";
                cout << "ID: " << table[index].id << "\nName: " << table[index].name 
                     << "\nPosition: " << table[index].position 
                     << "\nSalary: $" << table[index].salary << endl;
                return;
            }
            if (table[index].isEmpty) break;
            
            index = (index + 1) % TABLE_SIZE;
            if (index == original) break;
        }
        cout << "Employee with ID " << id << " not found!" << endl;
    }

    void deleteEmployee(int id) {
        int index = midSquareHash(id);
        int original = index;
        
        while (true) {
            if (!table[index].isEmpty && table[index].id == id) {
                table[index].isEmpty = true;
                cout << "Employee with ID " << id << " deleted from index " << index << endl;
                return;
            }
            if (table[index].isEmpty) break;
            
            index = (index + 1) % TABLE_SIZE;
            if (index == original) break;
        }
        cout << "Employee with ID " << id << " not found for deletion!" << endl;
    }

    void displayTable() {
        cout << "\nHash Table Contents (First 20 entries):\n";
        for (int i = 0; i < 20 && i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            if (table[i].isEmpty) {
                cout << "Empty";
            } else {
                cout << "[" << table[i].id << ":" << table[i].name << "]";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    int choice, id;
    string name, position;
    double salary;

    do {
        cout << "\nEmployee Database Menu\n";
        cout << "1. Insert Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Display Table\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Position: ";
                cin >> position;
                cout << "Enter Salary: ";
                cin >> salary;
                ht.insertEmployee(id, name, position, salary);
                break;
            case 2:
                cout << "Enter Employee ID to search: ";
                cin >> id;
                ht.searchEmployee(id);
                break;
            case 3:
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                ht.deleteEmployee(id);
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