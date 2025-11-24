#include <iostream>
using namespace std;

struct Seat {
    int seatNumber;
    bool isBooked;
    Seat* next;
    Seat* prev;
};

class Multiplex {
private:
    Seat* rows[8];
    const int SEATS_PER_ROW = 8;

    // Create circular doubly linked list for a row
    Seat* createRow() {
        Seat* head = nullptr;
        Seat* tail = nullptr;

        for (int i = 1; i <= SEATS_PER_ROW; i++) {
            Seat* newSeat = new Seat{i, false, nullptr, nullptr};
            
            if (!head) {
                head = newSeat;
                head->next = head;
                head->prev = head;
                tail = head;
            } else {
                newSeat->prev = tail;
                newSeat->next = head;
                tail->next = newSeat;
                head->prev = newSeat;
                tail = newSeat;
            }
        }
        return head;
    }

public:
    Multiplex() {
        // Initialize all rows
        for (int i = 0; i < 8; i++) {
            rows[i] = createRow();
            
            // Randomly book some seats
            Seat* current = rows[i];
            for (int j = 0; j < SEATS_PER_ROW; j++) {
                if (rand() % 4 == 0) { // 25% chance of being booked
                    current->isBooked = true;
                }
                current = current->next;
            }
        }
    }

    // Display available seats
    void displayAvailableSeats() {
        cout << "\nAvailable Seats (O=Available, X=Booked):\n";
        for (int i = 0; i < 8; i++) {
            cout << "Row " << (i + 1) << ": ";
            Seat* current = rows[i];
            do {
                cout << (current->isBooked ? "X " : "O ");
                current = current->next;
            } while (current != rows[i]);
            cout << endl;
        }
    }

    // Book a seat
    void bookSeat(int row, int seat) {
        if (row < 1 || row > 8 || seat < 1 || seat > 8) {
            cout << "Invalid seat selection!\n";
            return;
        }

        Seat* current = rows[row - 1];
        do {
            if (current->seatNumber == seat) {
                if (current->isBooked) {
                    cout << "Seat already booked!\n";
                } else {
                    current->isBooked = true;
                    cout << "Seat booked successfully!\n";
                }
                return;
            }
            current = current->next;
        } while (current != rows[row - 1]);

        cout << "Seat not found!\n";
    }

    // Cancel booking
    void cancelBooking(int row, int seat) {
        if (row < 1 || row > 8 || seat < 1 || seat > 8) {
            cout << "Invalid seat selection!\n";
            return;
        }

        Seat* current = rows[row - 1];
        do {
            if (current->seatNumber == seat) {
                if (!current->isBooked) {
                    cout << "Seat is not booked!\n";
                } else {
                    current->isBooked = false;
                    cout << "Booking cancelled successfully!\n";
                }
                return;
            }
            current = current->next;
        } while (current != rows[row - 1]);

        cout << "Seat not found!\n";
    }
};

int main() {
    Multiplex galaxy;
    int choice, row, seat;

    do {
        cout << "\n=== Galaxy Multiplex ===\n";
        cout << "1. Display Available Seats\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                galaxy.displayAvailableSeats();
                break;
            case 2:
                cout << "Enter row (1-8): ";
                cin >> row;
                cout << "Enter seat (1-8): ";
                cin >> seat;
                galaxy.bookSeat(row, seat);
                break;
            case 3:
                cout << "Enter row (1-8): ";
                cin >> row;
                cout << "Enter seat (1-8): ";
                cin >> seat;
                galaxy.cancelBooking(row, seat);
                break;
            case 4:
                cout << "Thank you for using Galaxy Multiplex!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}