#include <iostream>
using namespace std;

struct StockNode {
    int price;
    StockNode* next;
};

class StockTracker {
private:
    StockNode* top;

public:
    StockTracker() : top(nullptr) {}

    // Add new stock price
    void record(int price) {
        StockNode* newNode = new StockNode{price, nullptr};
        newNode->next = top;
        top = newNode;
        cout << "Recorded price: $" << price << endl;
    }

    // Remove and return most recent price
    int remove() {
        if (isEmpty()) {
            cout << "No prices to remove!\n";
            return -1;
        }
        
        StockNode* temp = top;
        int removedPrice = top->price;
        top = top->next;
        delete temp;
        
        cout << "Removed price: $" << removedPrice << endl;
        return removedPrice;
    }

    // Return most recent price without removing
    int latest() {
        if (isEmpty()) {
            cout << "No prices recorded!\n";
            return -1;
        }
        return top->price;
    }

    // Check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Display all prices
    void display() {
        if (isEmpty()) {
            cout << "No stock prices recorded.\n";
            return;
        }

        cout << "Stock Price History (most recent first):\n";
        StockNode* current = top;
        int position = 1;
        
        while (current) {
            cout << position << ". $" << current->price << endl;
            current = current->next;
            position++;
        }
    }
};

int main() {
    StockTracker tracker;
    int choice, price;

    do {
        cout << "\n=== Stock Price Tracker ===\n";
        cout << "1. Record Price\n";
        cout << "2. Remove Latest Price\n";
        cout << "3. View Latest Price\n";
        cout << "4. Check if Empty\n";
        cout << "5. Display All Prices\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter stock price: $";
                cin >> price;
                tracker.record(price);
                break;
            case 2:
                tracker.remove();
                break;
            case 3:
                price = tracker.latest();
                if (price != -1) {
                    cout << "Latest price: $" << price << endl;
                }
                break;
            case 4:
                cout << (tracker.isEmpty() ? "No prices recorded" : "Prices available") << endl;
                break;
            case 5:
                tracker.display();
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