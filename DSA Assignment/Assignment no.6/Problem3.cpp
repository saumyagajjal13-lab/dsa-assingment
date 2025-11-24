#include <iostream>
#include <queue>
#include <string>
using namespace std;

class TicketQueue {
private:
    queue<string> passengers;

public:
    void insertPassenger(string name) {
        passengers.push(name);
        cout << "Passenger " << name << " added to queue." << endl;
    }

    void displayFront() {
        if (passengers.empty()) {
            cout << "No passengers in queue." << endl;
            return;
        }
        cout << "Next passenger: " << passengers.front() << endl;
    }

    void removeFront() {
        if (passengers.empty()) {
            cout << "No passengers to remove." << endl;
            return;
        }
        string removed = passengers.front();
        passengers.pop();
        cout << "Passenger " << removed << " served and removed." << endl;
    }

    int getQueueSize() {
        return passengers.size();
    }
};

int main() {
    TicketQueue tq;
    int choice;
    string name;

    do {
        cout << "\nTicket Agent System\n";
        cout << "1. Add Passenger\n";
        cout << "2. Display Next Passenger\n";
        cout << "3. Serve Passenger\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter passenger name: ";
                cin >> name;
                tq.insertPassenger(name);
                break;
            case 2:
                tq.displayFront();
                break;
            case 3:
                tq.removeFront();
                break;
            case 4:
                cout << "Passengers remaining: " << tq.getQueueSize() << endl;
                cout << "System shutting down...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 4);

    return 0;
}