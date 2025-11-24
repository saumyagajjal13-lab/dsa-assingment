#include <iostream>
#include <string>
using namespace std;

struct Member {
    string name;
    string PRN;
    Member* next;
};

class VertexClub {
private:
    Member* head;
    Member* tail;

public:
    VertexClub() : head(nullptr), tail(nullptr) {}

    // Add member at end
    void addMember(string name, string PRN) {
        Member* newMember = new Member{name, PRN, nullptr};
        
        if (!head) {
            head = tail = newMember;
            cout << "Added as President and Secretary\n";
        } else {
            tail->next = newMember;
            tail = newMember;
            cout << "Added as new Secretary\n";
        }
    }

    // Delete member by PRN
    void deleteMember(string PRN) {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }

        // If president is being deleted
        if (head->PRN == PRN) {
            Member* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            cout << "President deleted. New president: " << (head ? head->name : "None") << endl;
            return;
        }

        Member* current = head;
        while (current->next && current->next->PRN != PRN) {
            current = current->next;
        }

        if (!current->next) {
            cout << "Member not found!\n";
            return;
        }

        Member* temp = current->next;
        current->next = temp->next;
        
        if (temp == tail) {
            tail = current;
            cout << "Secretary deleted. New secretary: " << tail->name << endl;
        } else {
            cout << "Member deleted successfully\n";
        }
        delete temp;
    }

    // Count members
    int countMembers() {
        int count = 0;
        Member* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Display all members
    void displayMembers() {
        if (!head) {
            cout << "No members in club!\n";
            return;
        }

        Member* current = head;
        int position = 1;
        while (current) {
            cout << position << ". " << current->name << " (PRN: " << current->PRN << ")";
            if (current == head) cout << " - President";
            if (current == tail) cout << " - Secretary";
            cout << endl;
            current = current->next;
            position++;
        }
    }

    // Search by PRN
    void searchByPRN(string PRN) {
        Member* current = head;
        int position = 1;
        while (current) {
            if (current->PRN == PRN) {
                cout << "Member found at position " << position << ": " 
                     << current->name << " (PRN: " << current->PRN << ")\n";
                return;
            }
            current = current->next;
            position++;
        }
        cout << "Member not found!\n";
    }

    // Sort by PRN (Bubble Sort)
    void sortByPRN() {
        if (!head || !head->next) return;

        bool swapped;
        do {
            swapped = false;
            Member* current = head;
            Member* prev = nullptr;

            while (current->next) {
                if (current->PRN > current->next->PRN) {
                    // Swap nodes
                    Member* temp = current->next;
                    current->next = temp->next;
                    temp->next = current;

                    if (prev) {
                        prev->next = temp;
                    } else {
                        head = temp;
                    }

                    if (current == tail) {
                        tail = temp;
                    }

                    prev = temp;
                    swapped = true;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        } while (swapped);
    }

    // Reverse the list
    void reverseList() {
        if (!head || !head->next) return;

        Member* prev = nullptr;
        Member* current = head;
        Member* next = nullptr;
        tail = head;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    // Concatenate two lists
    void concatenate(VertexClub& other) {
        if (!other.head) return;

        if (!head) {
            head = other.head;
            tail = other.tail;
        } else {
            tail->next = other.head;
            tail = other.tail;
        }

        other.head = other.tail = nullptr;
    }
};

int main() {
    VertexClub club;
    int choice;
    string name, PRN;

    do {
        cout << "\n=== Vertex Club Management ===\n";
        cout << "1. Add Member\n";
        cout << "2. Delete Member\n";
        cout << "3. Count Members\n";
        cout << "4. Display Members\n";
        cout << "5. Search by PRN\n";
        cout << "6. Sort by PRN\n";
        cout << "7. Reverse List\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter PRN: ";
                cin >> PRN;
                club.addMember(name, PRN);
                break;
            case 2:
                cout << "Enter PRN to delete: ";
                cin >> PRN;
                club.deleteMember(PRN);
                break;
            case 3:
                cout << "Total members: " << club.countMembers() << endl;
                break;
            case 4:
                club.displayMembers();
                break;
            case 5:
                cout << "Enter PRN to search: ";
                cin >> PRN;
                club.searchByPRN(PRN);
                break;
            case 6:
                club.sortByPRN();
                cout << "List sorted by PRN\n";
                break;
            case 7:
                club.reverseList();
                cout << "List reversed\n";
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}