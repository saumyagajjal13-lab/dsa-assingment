#include <iostream>
using namespace std;

struct BinaryNode {
    int bit;
    BinaryNode* next;
    BinaryNode* prev;
};

class BinaryNumber {
private:
    BinaryNode* head;
    BinaryNode* tail;

public:
    BinaryNumber() : head(nullptr), tail(nullptr) {}

    // Add bit at the end (MSB first)
    void addBit(int bit) {
        if (bit != 0 && bit != 1) {
            cout << "Invalid bit! Must be 0 or 1.\n";
            return;
        }

        BinaryNode* newNode = new BinaryNode{bit, nullptr, nullptr};
        
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Display binary number
    void display() {
        BinaryNode* current = head;
        while (current) {
            cout << current->bit;
            current = current->next;
        }
        cout << endl;
    }

    // 1's complement
    BinaryNumber onesComplement() {
        BinaryNumber result;
        BinaryNode* current = head;
        
        while (current) {
            result.addBit(current->bit == 0 ? 1 : 0);
            current = current->next;
        }
        
        return result;
    }

    // 2's complement
    BinaryNumber twosComplement() {
        BinaryNumber onesComp = onesComplement();
        
        // Add 1 to ones complement
        BinaryNumber result;
        BinaryNode* current = onesComp.tail;
        int carry = 1;
        
        while (current) {
            int sum = current->bit + carry;
            result.addBitAtFront(sum % 2);
            carry = sum / 2;
            current = current->prev;
        }
        
        if (carry) {
            result.addBitAtFront(carry);
        }
        
        return result;
    }

    // Helper function to add bit at front
    void addBitAtFront(int bit) {
        BinaryNode* newNode = new BinaryNode{bit, nullptr, nullptr};
        
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Add two binary numbers
    static BinaryNumber add(BinaryNumber& num1, BinaryNumber& num2) {
        BinaryNumber result;
        BinaryNode* curr1 = num1.tail;
        BinaryNode* curr2 = num2.tail;
        int carry = 0;
        
        while (curr1 || curr2 || carry) {
            int bit1 = curr1 ? curr1->bit : 0;
            int bit2 = curr2 ? curr2->bit : 0;
            
            int sum = bit1 + bit2 + carry;
            result.addBitAtFront(sum % 2);
            carry = sum / 2;
            
            if (curr1) curr1 = curr1->prev;
            if (curr2) curr2 = curr2->prev;
        }
        
        return result;
    }
};

int main() {
    BinaryNumber num1, num2;
    int choice, bit;
    
    // Initialize with sample binary numbers: 1010 (10) and 1101 (13)
    cout << "Initializing with sample numbers:\n";
    cout << "Number 1: 1010 (10 in decimal)\n";
    cout << "Number 2: 1101 (13 in decimal)\n\n";
    
    num1.addBit(1); num1.addBit(0); num1.addBit(1); num1.addBit(0);
    num2.addBit(1); num2.addBit(1); num2.addBit(0); num2.addBit(1);

    do {
        cout << "\n=== Binary Number Operations ===\n";
        cout << "1. Display Numbers\n";
        cout << "2. 1's Complement\n";
        cout << "3. 2's Complement\n";
        cout << "4. Add Numbers\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Number 1: ";
                num1.display();
                cout << "Number 2: ";
                num2.display();
                break;
            case 2:
                cout << "1's Complement of Number 1: ";
                num1.onesComplement().display();
                cout << "1's Complement of Number 2: ";
                num2.onesComplement().display();
                break;
            case 3:
                cout << "2's Complement of Number 1: ";
                num1.twosComplement().display();
                cout << "2's Complement of Number 2: ";
                num2.twosComplement().display();
                break;
            case 4:
                cout << "Addition Result: ";
                BinaryNumber::add(num1, num2).display();
                cout << "Expected: 1010 + 1101 = 10111 (23 in decimal)\n";
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