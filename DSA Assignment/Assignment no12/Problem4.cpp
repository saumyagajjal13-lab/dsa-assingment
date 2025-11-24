#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string branch;
    float cgpa;
    string phone;
};

class StudentDB {
private:
    static const int TABLE_SIZE = 20;
    vector<list<Student>> table;

    int hashFunction(int rollNo) {
        return rollNo % TABLE_SIZE;
    }

public:
    StudentDB() {
        table.resize(TABLE_SIZE);
    }

    void insertStudent(int rollNo, string name, string branch, float cgpa, string phone) {
        Student student = {rollNo, name, branch, cgpa, phone};
        int index = hashFunction(rollNo);
        table[index].push_back(student);
        cout << "Student " << name << " inserted at index " << index << endl;
    }

    void searchStudent(int rollNo) {
        int index = hashFunction(rollNo);
        cout << "Searching at index " << index << endl;
        
        bool found = false;
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->rollNo == rollNo) {
                cout << "Student Found:\n";
                cout << "Roll No: " << it->rollNo << "\nName: " << it->name 
                     << "\nBranch: " << it->branch 
                     << "\nCGPA: " << it->cgpa 
                     << "\nPhone: " << it->phone << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Student with Roll No " << rollNo << " not found!" << endl;
        }
    }

    void deleteStudent(int rollNo) {
        int index = hashFunction(rollNo);
        bool found = false;
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->rollNo == rollNo) {
                table[index].erase(it);
                cout << "Student with Roll No " << rollNo << " deleted!" << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Student with Roll No " << rollNo << " not found for deletion!" << endl;
        }
    }

    void updateStudent(int rollNo, float newCGPA, string newPhone) {
        int index = hashFunction(rollNo);
        bool found = false;
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->rollNo == rollNo) {
                it->cgpa = newCGPA;
                it->phone = newPhone;
                cout << "Student record updated successfully!" << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Student with Roll No " << rollNo << " not found for update!" << endl;
        }
    }

    void displayAllStudents() {
        cout << "\nAll Student Records:\n";
        bool hasStudents = false;
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i].empty()) {
                for (auto student : table[i]) {
                    cout << "Index " << i << ": Roll No: " << student.rollNo 
                         << ", Name: " << student.name 
                         << ", Branch: " << student.branch 
                         << ", CGPA: " << student.cgpa << endl;
                    hasStudents = true;
                }
            }
        }
        
        if (!hasStudents) {
            cout << "No student records found!" << endl;
        }
    }

    void displayTableStructure() {
        cout << "\nHash Table Structure:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            if (table[i].empty()) {
                cout << "Empty";
            } else {
                cout << table[i].size() << " student(s) - ";
                for (auto student : table[i]) {
                    cout << "[" << student.rollNo << ":" << student.name << "] ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    StudentDB db;
    int choice, rollNo;
    string name, branch, phone;
    float cgpa;

    do {
        cout << "\nStudent Database Management System\n";
        cout << "1. Insert Student\n";
        cout << "2. Search Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Update Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Display Table Structure\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Roll No: ";
                cin >> rollNo;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Branch: ";
                cin >> branch;
                cout << "Enter CGPA: ";
                cin >> cgpa;
                cout << "Enter Phone: ";
                cin >> phone;
                db.insertStudent(rollNo, name, branch, cgpa, phone);
                break;
            case 2:
                cout << "Enter Roll No to search: ";
                cin >> rollNo;
                db.searchStudent(rollNo);
                break;
            case 3:
                cout << "Enter Roll No to delete: ";
                cin >> rollNo;
                db.deleteStudent(rollNo);
                break;
            case 4:
                cout << "Enter Roll No to update: ";
                cin >> rollNo;
                cout << "Enter new CGPA: ";
                cin >> cgpa;
                cout << "Enter new Phone: ";
                cin >> phone;
                db.updateStudent(rollNo, cgpa, phone);
                break;
            case 5:
                db.displayAllStudents();
                break;
            case 6:
                db.displayTableStructure();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 7);

    return 0;
}