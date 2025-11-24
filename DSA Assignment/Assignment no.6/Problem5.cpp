#include <iostream>
#include <string>
using namespace std;

struct Call {
    string callerName;
    string phoneNumber;
    Call* next;
};

class CallCenter {
private:
    Call* front;
    Call* rear;

public:
    CallCenter() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueueCall(string name, string phone) {
        Call* newCall = new Call{name, phone, nullptr};
        
        if (isEmpty()) {
            front = rear = newCall;
        } else {
            rear->next = newCall;
            rear = newCall;
        }
        cout << "Call from " << name << " (" << phone << ") added to queue." << endl;
    }

    void dequeueCall() {
        if (isEmpty()) {
            cout << "No calls in queue. Waiting for calls..." << endl;
            return;
        }
        
        Call* temp = front;
        cout << "Agent assisting: " << temp->callerName << " (" << temp->phoneNumber << ")" << endl;
        
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "No calls waiting." << endl;
            return;
        }
        
        cout << "Calls in queue:" << endl;
        Call* current = front;
        int position = 1;
        
        while (current != nullptr) {
            cout << position << ". " << current->callerName << " (" << current->phoneNumber << ")" << endl;
            current = current->next;
            position++;
        }
    }

    void getNextCall() {
        if (isEmpty()) {
            cout << "No calls waiting." << endl;
        } else {
            cout << "Next call: " << front->callerName << " (" << front->phoneNumber << ")" << endl;
        }
    }
};

int main() {
    CallCenter center;
    int choice;
    string name, phone;

    do {
        cout << "\nCall Center System\n";
        cout << "1. Add Call\n";
        cout << "2. Assist Next Call\n";
        cout << "3. Display Queue\n";
        cout << "4. Show Next Call\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter caller name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phone;
                center.enqueueCall(name, phone);
                break;
            case 2:
                center.dequeueCall();
                break;
            case 3:
                center.displayQueue();
                break;
            case 4:
                center.getNextCall();
                break;
            case 5:
                cout << "System shutting down...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 5);

    return 0;
}