#include <iostream>
using namespace std;

class MultipleQueues {
private:
    int* arr;
    int front1, rear1;
    int front2, rear2;
    int size;

public:
    MultipleQueues(int n) {
        size = n;
        arr = new int[size];
        front1 = rear1 = -1;
        front2 = rear2 = -1;
    }

    bool isQueue1Empty() {
        return front1 == -1;
    }

    bool isQueue2Empty() {
        return front2 == -1;
    }

    bool isQueue1Full() {
        return (rear1 + 1) % (size/2) == front1;
    }

    bool isQueue2Full() {
        return (rear2 + 1) % (size/2) == front2;
    }

    void addToQueue1(int value) {
        if (isQueue1Full()) {
            cout << "Queue 1 is full!" << endl;
            return;
        }
        
        if (isQueue1Empty()) {
            front1 = rear1 = 0;
        } else {
            rear1 = (rear1 + 1) % (size/2);
        }
        arr[rear1] = value;
        cout << value << " added to Queue 1." << endl;
    }

    void addToQueue2(int value) {
        if (isQueue2Full()) {
            cout << "Queue 2 is full!" << endl;
            return;
        }
        
        if (isQueue2Empty()) {
            front2 = rear2 = size/2;
        } else {
            rear2 = (rear2 + 1) % (size/2) + size/2;
        }
        arr[rear2] = value;
        cout << value << " added to Queue 2." << endl;
    }

    void deleteFromQueue1() {
        if (isQueue1Empty()) {
            cout << "Queue 1 is empty!" << endl;
            return;
        }
        
        cout << arr[front1] << " deleted from Queue 1." << endl;
        
        if (front1 == rear1) {
            front1 = rear1 = -1;
        } else {
            front1 = (front1 + 1) % (size/2);
        }
    }

    void deleteFromQueue2() {
        if (isQueue2Empty()) {
            cout << "Queue 2 is empty!" << endl;
            return;
        }
        
        cout << arr[front2] << " deleted from Queue 2." << endl;
        
        if (front2 == rear2) {
            front2 = rear2 = -1;
        } else {
            front2 = (front2 + 1) % (size/2) + size/2;
        }
    }

    void displayQueue1() {
        if (isQueue1Empty()) {
            cout << "Queue 1 is empty." << endl;
            return;
        }
        
        cout << "Queue 1: ";
        int i = front1;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear1) break;
            i = (i + 1) % (size/2);
        }
        cout << endl;
    }

    void displayQueue2() {
        if (isQueue2Empty()) {
            cout << "Queue 2 is empty." << endl;
            return;
        }
        
        cout << "Queue 2: ";
        int i = front2;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear2) break;
            i = (i + 1) % (size/2) + size/2;
        }
        cout << endl;
    }
};

int main() {
    int size;
    cout << "Enter total array size: ";
    cin >> size;
    
    MultipleQueues mq(size);
    int choice, value, queueNum;

    do {
        cout << "\nMultiple Queues System\n";
        cout << "1. Add to Queue\n";
        cout << "2. Delete from Queue\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter queue number (1 or 2): ";
                cin >> queueNum;
                cout << "Enter value: ";
                cin >> value;
                if (queueNum == 1) mq.addToQueue1(value);
                else if (queueNum == 2) mq.addToQueue2(value);
                else cout << "Invalid queue number!\n";
                break;
            case 2:
                cout << "Enter queue number (1 or 2): ";
                cin >> queueNum;
                if (queueNum == 1) mq.deleteFromQueue1();
                else if (queueNum == 2) mq.deleteFromQueue2();
                else cout << "Invalid queue number!\n";
                break;
            case 3:
                cout << "Enter queue number (1 or 2): ";
                cin >> queueNum;
                if (queueNum == 1) mq.displayQueue1();
                else if (queueNum == 2) mq.displayQueue2();
                else cout << "Invalid queue number!\n";
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