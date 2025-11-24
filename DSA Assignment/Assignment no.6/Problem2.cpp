#include <iostream>
using namespace std;

class PizzaParlour {
private:
    int* orders;
    int front, rear;
    int capacity;
    int currentSize;

public:
    PizzaParlour(int n) {
        capacity = n;
        orders = new int[capacity];
        front = rear = -1;
        currentSize = 0;
    }

    bool isFull() {
        return currentSize == capacity;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    void placeOrder(int orderId) {
        if (isFull()) {
            cout << "Cannot accept more orders! Maximum reached." << endl;
            return;
        }
        
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        
        orders[rear] = orderId;
        currentSize++;
        cout << "Order " << orderId << " placed successfully." << endl;
    }

    void serveOrder() {
        if (isEmpty()) {
            cout << "No orders to serve." << endl;
            return;
        }
        
        int servedOrder = orders[front];
        cout << "Serving order: " << servedOrder << endl;
        
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        currentSize--;
    }

    void displayOrders() {
        if (isEmpty()) {
            cout << "No pending orders." << endl;
            return;
        }
        
        cout << "Pending orders: ";
        int i = front;
        int count = 0;
        
        while (count < currentSize) {
            cout << orders[i] << " ";
            i = (i + 1) % capacity;
            count++;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter maximum orders: ";
    cin >> n;
    
    PizzaParlour parlour(n);
    int choice, orderId;
    orderId = 1;

    do {
        cout << "\nPizza Parlour System\n";
        cout << "1. Place Order\n";
        cout << "2. Serve Order\n";
        cout << "3. Display Orders\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                parlour.placeOrder(orderId++);
                break;
            case 2:
                parlour.serveOrder();
                break;
            case 3:
                parlour.displayOrders();
                break;
            case 4:
                cout << "Closing parlour...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 4);

    return 0;
}