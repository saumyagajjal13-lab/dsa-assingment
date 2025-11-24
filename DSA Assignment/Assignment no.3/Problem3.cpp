#include <iostream>
#include <string>
using namespace std;

struct Appointment {
    string startTime;
    string endTime;
    int duration;
    bool isBooked;
    string customerName;
    Appointment* next;
};

class AppointmentSystem {
private:
    Appointment* head;
    const int MIN_DURATION = 30; // minutes
    const int MAX_DURATION = 120; // minutes

public:
    AppointmentSystem() : head(nullptr) {
        // Create some random time slots
        initializeSlots();
    }

    void initializeSlots() {
        string times[] = {"09:00", "10:00", "11:00", "12:00", "14:00", "15:00", "16:00", "17:00"};
        
        for (int i = 0; i < 8; i++) {
            addSlot(times[i], rand() % (MAX_DURATION - MIN_DURATION + 1) + MIN_DURATION);
        }
    }

    void addSlot(string startTime, int duration) {
        Appointment* newSlot = new Appointment{startTime, "", duration, false, "", nullptr};
        
        // Calculate end time
        int hours = stoi(startTime.substr(0, 2));
        int minutes = stoi(startTime.substr(3, 2));
        
        minutes += duration;
        hours += minutes / 60;
        minutes = minutes % 60;
        
        newSlot->endTime = (hours < 10 ? "0" : "") + to_string(hours) + ":" + 
                          (minutes < 10 ? "0" : "") + to_string(minutes);

        if (!head) {
            head = newSlot;
        } else {
            Appointment* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newSlot;
        }
    }

    void displayAvailableSlots() {
        cout << "\nAvailable Appointment Slots:\n";
        Appointment* current = head;
        int slotNum = 1;
        
        while (current) {
            cout << slotNum << ". " << current->startTime << " - " << current->endTime 
                 << " (" << current->duration << " mins) - " 
                 << (current->isBooked ? "BOOKED by " + current->customerName : "AVAILABLE") << endl;
            current = current->next;
            slotNum++;
        }
    }

    void bookAppointment(int slotNum, string customerName) {
        Appointment* current = head;
        int currentNum = 1;
        
        while (current && currentNum < slotNum) {
            current = current->next;
            currentNum++;
        }
        
        if (!current || currentNum != slotNum) {
            cout << "Invalid slot number!\n";
            return;
        }
        
        if (current->isBooked) {
            cout << "Slot already booked!\n";
        } else {
            current->isBooked = true;
            current->customerName = customerName;
            cout << "Appointment booked successfully!\n";
        }
    }

    void cancelAppointment(string customerName) {
        Appointment* current = head;
        bool found = false;
        
        while (current) {
            if (current->isBooked && current->customerName == customerName) {
                current->isBooked = false;
                current->customerName = "";
                cout << "Appointment cancelled successfully!\n";
                found = true;
                break;
            }
            current = current->next;
        }
        
        if (!found) {
            cout << "No appointment found for " << customerName << "!\n";
        }
    }

    // Sort by time using pointer manipulation
    void sortByTime() {
        if (!head || !head->next) return;
        
        bool swapped;
        do {
            swapped = false;
            Appointment* current = head;
            Appointment* prev = nullptr;
            
            while (current->next) {
                if (current->startTime > current->next->startTime) {
                    // Swap nodes by adjusting pointers
                    Appointment* temp = current->next;
                    current->next = temp->next;
                    temp->next = current;
                    
                    if (prev) {
                        prev->next = temp;
                    } else {
                        head = temp;
                    }
                    
                    prev = temp;
                    swapped = true;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        } while (swapped);
        
        cout << "Appointments sorted by time!\n";
    }
};

int main() {
    AppointmentSystem system;
    int choice, slotNum;
    string name;

    do {
        cout << "\n=== Appointment Scheduling System ===\n";
        cout << "1. Display Available Slots\n";
        cout << "2. Book Appointment\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. Sort by Time\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayAvailableSlots();
                break;
            case 2:
                cout << "Enter slot number: ";
                cin >> slotNum;
                cout << "Enter customer name: ";
                cin >> name;
                system.bookAppointment(slotNum, name);
                break;
            case 3:
                cout << "Enter customer name to cancel: ";
                cin >> name;
                system.cancelAppointment(name);
                break;
            case 4:
                system.sortByTime();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}