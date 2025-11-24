#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    string name;
    int id;
};

class Clinic {
private:
    queue<Patient> patientQueue;
    int patientCount;

public:
    Clinic() : patientCount(0) {}

    void addPatient(string name) {
        Patient newPatient;
        newPatient.name = name;
        newPatient.id = ++patientCount;
        patientQueue.push(newPatient);
        cout << "Patient " << name << " added. ID: " << patientCount << endl;
    }

    void assignToDoctor() {
        if (patientQueue.empty()) {
            cout << "No patients waiting." << endl;
            return;
        }
        Patient nextPatient = patientQueue.front();
        patientQueue.pop();
        cout << "Assigned to doctor: " << nextPatient.name << " (ID: " << nextPatient.id << ")" << endl;
    }

    void displayWaiting() {
        if (patientQueue.empty()) {
            cout << "No patients waiting." << endl;
            return;
        }
        cout << "Patients waiting: " << patientQueue.size() << endl;
    }
};

int main() {
    Clinic clinic;
    int choice;
    string name;

    do {
        cout << "\nMedical Clinic System\n";
        cout << "1. Add Patient\n";
        cout << "2. Assign to Doctor\n";
        cout << "3. Display Waiting\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter patient name: ";
                cin >> name;
                clinic.addPatient(name);
                break;
            case 2:
                clinic.assignToDoctor();
                break;
            case 3:
                clinic.displayWaiting();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 4);

    return 0;
}