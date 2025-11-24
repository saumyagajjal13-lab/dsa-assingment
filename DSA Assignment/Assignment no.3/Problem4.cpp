#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    string PRN;
    bool likesCricket;
    bool likesFootball;
    Student* next;
};

class SportsGroups {
private:
    Student* head;
    int totalStudents;

public:
    SportsGroups() : head(nullptr), totalStudents(0) {}

    void addStudent(string name, string PRN, bool cricket, bool football) {
        Student* newStudent = new Student{name, PRN, cricket, football, nullptr};
        
        if (!head) {
            head = newStudent;
        } else {
            Student* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newStudent;
        }
        totalStudents++;
    }

    // Students who like both cricket and football
    void displayBothSports() {
        cout << "\nStudents who like both Cricket and Football:\n";
        Student* current = head;
        bool found = false;
        
        while (current) {
            if (current->likesCricket && current->likesFootball) {
                cout << current->name << " (PRN: " << current->PRN << ")\n";
                found = true;
            }
            current = current->next;
        }
        
        if (!found) {
            cout << "No students like both sports.\n";
        }
    }

    // Students who like either but not both
    void displayEitherButNotBoth() {
        cout << "\nStudents who like either Cricket or Football but not both:\n";
        Student* current = head;
        bool found = false;
        
        while (current) {
            if ((current->likesCricket && !current->likesFootball) || 
                (!current->likesCricket && current->likesFootball)) {
                cout << current->name << " (PRN: " << current->PRN << ")\n";
                found = true;
            }
            current = current->next;
        }
        
        if (!found) {
            cout << "No students found in this category.\n";
        }
    }

    // Students who like neither sport
    void displayNeitherSport() {
        cout << "\nStudents who like neither Cricket nor Football:\n";
        Student* current = head;
        int count = 0;
        
        while (current) {
            if (!current->likesCricket && !current->likesFootball) {
                cout << current->name << " (PRN: " << current->PRN << ")\n";
                count++;
            }
            current = current->next;
        }
        
        cout << "Total students who like neither: " << count << endl;
    }

    void displayAllStudents() {
        cout << "\nAll Students:\n";
        Student* current = head;
        while (current) {
            cout << current->name << " (PRN: " << current->PRN << ") - ";
            cout << "Cricket: " << (current->likesCricket ? "Yes" : "No") << ", ";
            cout << "Football: " << (current->likesFootball ? "Yes" : "No") << endl;
            current = current->next;
        }
    }
};

int main() {
    SportsGroups groups;
    int choice;
    string name, PRN;
    char cricket, football;

    // Add some sample data
    groups.addStudent("Alice", "PRN001", true, false);
    groups.addStudent("Bob", "PRN002", false, true);
    groups.addStudent("Carol", "PRN003", true, true);
    groups.addStudent("David", "PRN004", false, false);
    groups.addStudent("Eve", "PRN005", true, false);

    do {
        cout << "\n=== Sports Preference System ===\n";
        cout << "1. Display All Students\n";
        cout << "2. Students who like both sports\n";
        cout << "3. Students who like either but not both\n";
        cout << "4. Students who like neither sport\n";
        cout << "5. Add New Student\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                groups.displayAllStudents();
                break;
            case 2:
                groups.displayBothSports();
                break;
            case 3:
                groups.displayEitherButNotBoth();
                break;
            case 4:
                groups.displayNeitherSport();
                break;
            case 5:
                cout << "Enter student name: ";
                cin >> name;
                cout << "Enter PRN: ";
                cin >> PRN;
                cout << "Likes Cricket? (y/n): ";
                cin >> cricket;
                cout << "Likes Football? (y/n): ";
                cin >> football;
                groups.addStudent(name, PRN, cricket == 'y', football == 'y');
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}