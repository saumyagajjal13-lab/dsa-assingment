#include <iostream>
using namespace std;

class MultipleStacks {
private:
    int* arr;
    int* top;
    int* next;
    int n, k;
    int freeSpot;

public:
    MultipleStacks(int k, int n) : k(k), n(n) {
        arr = new int[n];
        top = new int[k];
        next = new int[n];
        freeSpot = 0;

        // Initialize all tops as -1
        for (int i = 0; i < k; i++) {
            top[i] = -1;
        }

        // Initialize next array
        for (int i = 0; i < n; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1;
    }

    // Push element to specific stack
    bool push(int x, int sn) {
        if (sn < 0 || sn >= k) {
            cout << "Invalid stack number!\n";
            return false;
        }

        // Check for overflow
        if (freeSpot == -1) {
            cout << "Stack Overflow!\n";
            return false;
        }

        int index = freeSpot;
        freeSpot = next[index];
        next[index] = top[sn];
        top[sn] = index;
        arr[index] = x;

        cout << "Pushed " << x << " to stack " << sn << endl;
        return true;
    }

    // Pop element from specific stack
    int pop(int sn) {
        if (sn < 0 || sn >= k) {
            cout << "Invalid stack number!\n";
            return -1;
        }

        // Check for underflow
        if (top[sn] == -1) {
            cout << "Stack " << sn << " Underflow!\n";
            return -1;
        }

        int index = top[sn];
        top[sn] = next[index];
        next[index] = freeSpot;
        freeSpot = index;

        cout << "Popped " << arr[index] << " from stack " << sn << endl;
        return arr[index];
    }

    // Display specific stack
    void display(int sn) {
        if (sn < 0 || sn >= k) {
            cout << "Invalid stack number!\n";
            return;
        }

        if (top[sn] == -1) {
            cout << "Stack " << sn << " is empty\n";
            return;
        }

        cout << "Stack " << sn << ": ";
        int index = top[sn];
        while (index != -1) {
            cout << arr[index] << " ";
            index = next[index];
        }
        cout << endl;
    }

    // Display all stacks
    void displayAll() {
        for (int i = 0; i < k; i++) {
            display(i);
        }
    }

    // Check if specific stack is empty
    bool isEmpty(int sn) {
        return top[sn] == -1;
    }
};

int main() {
    int k = 3; // Number of stacks
    int n = 10; // Total size

    MultipleStacks ms(k, n);
    int choice, value, stackNum;

    do {
        cout << "\n=== Multiple Stacks Operations ===\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Display Stack\n";
        cout << "4. Display All Stacks\n";
        cout << "5. Check Stack Empty\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter stack number (0 to " << k-1 << "): ";
                cin >> stackNum;
                cout << "Enter value to push: ";
                cin >> value;
                ms.push(value, stackNum);
                break;
            case 2:
                cout << "Enter stack number (0 to " << k-1 << "): ";
                cin >> stackNum;
                ms.pop(stackNum);
                break;
            case 3:
                cout << "Enter stack number (0 to " << k-1 << "): ";
                cin >> stackNum;
                ms.display(stackNum);
                break;
            case 4:
                ms.displayAll();
                break;
            case 5:
                cout << "Enter stack number (0 to " << k-1 << "): ";
                cin >> stackNum;
                cout << "Stack " << stackNum << " is " 
                     << (ms.isEmpty(stackNum) ? "empty" : "not empty") << endl;
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