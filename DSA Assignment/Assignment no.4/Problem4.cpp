#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node *next, *prev;
        Node(int d) : data(d), next(nullptr), prev(nullptr) {}
    };
    
    Node *head, *tail;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
    void insertAtBeginning(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
            cout << "Inserted " << data << " as first node" << endl;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cout << "Inserted " << data << " at beginning" << endl;
        }
    }
    
    void insertAtEnd(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
            cout << "Inserted " << data << " as first node" << endl;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            cout << "Inserted " << data << " at end" << endl;
        }
    }
    
    void insertAtPosition(int data, int pos) {
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if (pos == 1) {
            insertAtBeginning(data);
            return;
        }
        
        Node* newNode = new Node(data);
        Node* temp = head;
        
        for (int i = 1; i < pos-1 && temp; i++) {
            temp = temp->next;
        }
        
        if (!temp) {
            cout << "Invalid position! Position exceeds list length." << endl;
            delete newNode;
            return;
        }
        
        if (!temp->next) {
            insertAtEnd(data);
            delete newNode;
            return;
        }
        
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        
        cout << "Inserted " << data << " at position " << pos << endl;
    }
    
    void insertAfterValue(int data, int value) {
        Node* temp = head;
        
        while (temp && temp->data != value) {
            temp = temp->next;
        }
        
        if (!temp) {
            cout << "Value " << value << " not found in list!" << endl;
            return;
        }
        
        Node* newNode = new Node(data);
        
        newNode->next = temp->next;
        newNode->prev = temp;
        
        if (temp->next) {
            temp->next->prev = newNode;
        } else {
            tail = newNode;
        }
        
        temp->next = newNode;
        cout << "Inserted " << data << " after value " << value << endl;
    }
    
    void insertBeforeValue(int data, int value) {
        Node* temp = head;
        
        while (temp && temp->data != value) {
            temp = temp->next;
        }
        
        if (!temp) {
            cout << "Value " << value << " not found in list!" << endl;
            return;
        }
        
        Node* newNode = new Node(data);
        
        newNode->next = temp;
        newNode->prev = temp->prev;
        
        if (temp->prev) {
            temp->prev->next = newNode;
        } else {
            head = newNode;
        }
        
        temp->prev = newNode;
        cout << "Inserted " << data << " before value " << value << endl;
    }
    
    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty! Cannot delete." << endl;
            return;
        }
        
        Node* temp = head;
        int deletedData = temp->data;
        
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        
        delete temp;
        cout << "Deleted " << deletedData << " from beginning" << endl;
    }
    
    void deleteFromEnd() {
        if (!head) {
            cout << "List is empty! Cannot delete." << endl;
            return;
        }
        
        Node* temp = tail;
        int deletedData = temp->data;
        
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        
        delete temp;
        cout << "Deleted " << deletedData << " from end" << endl;
    }
    
    void deleteFromPosition(int pos) {
        if (!head) {
            cout << "List is empty! Cannot delete." << endl;
            return;
        }
        
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if (pos == 1) {
            deleteFromBeginning();
            return;
        }
        
        Node* temp = head;
        for (int i = 1; i < pos && temp; i++) {
            temp = temp->next;
        }
        
        if (!temp) {
            cout << "Invalid position! Position exceeds list length." << endl;
            return;
        }
        
        int deletedData = temp->data;
        
        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;
        }
        
        delete temp;
        cout << "Deleted " << deletedData << " from position " << pos << endl;
    }
    
    void deleteByValue(int value) {
        if (!head) {
            cout << "List is empty! Cannot delete." << endl;
            return;
        }
        
        Node* temp = head;
        
        while (temp && temp->data != value) {
            temp = temp->next;
        }
        
        if (!temp) {
            cout << "Value " << value << " not found in list!" << endl;
            return;
        }
        
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }
        
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;
        }
        
        delete temp;
        cout << "Deleted value " << value << " from list" << endl;
    }
    
    void display() {
        if (!head) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* temp = head;
        cout << "List (Forward): ";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    void displayReverse() {
        if (!tail) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* temp = tail;
        cout << "List (Reverse): ";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
    
    int count() {
        int cnt = 0;
        Node* temp = head;
        while (temp) {
            cnt++;
            temp = temp->next;
        }
        return cnt;
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void displayMenu() {
    cout << "\n=== Doubly Linked List Operations ===" << endl;
    cout << "INSERT OPERATIONS:" << endl;
    cout << "1. Insert at Beginning" << endl;
    cout << "2. Insert at End" << endl;
    cout << "3. Insert at Position" << endl;
    cout << "4. Insert After Value" << endl;
    cout << "5. Insert Before Value" << endl;
    cout << "\nDELETE OPERATIONS:" << endl;
    cout << "6. Delete from Beginning" << endl;
    cout << "7. Delete from End" << endl;
    cout << "8. Delete from Position" << endl;
    cout << "9. Delete by Value" << endl;
    cout << "\nDISPLAY OPERATIONS:" << endl;
    cout << "10. Display Forward" << endl;
    cout << "11. Display Reverse" << endl;
    cout << "12. Count Nodes" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
    DoublyLinkedList dll;
    int choice, data, pos, value;
    
    cout << "=== Doubly Linked List - All Insert & Delete Operations ===" << endl;
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter data: ";
                cin >> data;
                dll.insertAtBeginning(data);
                break;
                
            case 2:
                cout << "Enter data: ";
                cin >> data;
                dll.insertAtEnd(data);
                break;
                
            case 3:
                cout << "Enter data: ";
                cin >> data;
                cout << "Enter position: ";
                cin >> pos;
                dll.insertAtPosition(data, pos);
                break;
                
            case 4:
                cout << "Enter data: ";
                cin >> data;
                cout << "Enter value after which to insert: ";
                cin >> value;
                dll.insertAfterValue(data, value);
                break;
                
            case 5:
                cout << "Enter data: ";
                cin >> data;
                cout << "Enter value before which to insert: ";
                cin >> value;
                dll.insertBeforeValue(data, value);
                break;
                
            case 6:
                dll.deleteFromBeginning();
                break;
                
            case 7:
                dll.deleteFromEnd();
                break;
                
            case 8:
                cout << "Enter position: ";
                cin >> pos;
                dll.deleteFromPosition(pos);
                break;
                
            case 9:
                cout << "Enter value to delete: ";
                cin >> value;
                dll.deleteByValue(value);
                break;
                
            case 10:
                dll.display();
                break;
                
            case 11:
                dll.displayReverse();
                break;
                
            case 12:
                cout << "Total nodes: " << dll.count() << endl;
                break;
                
            case 0:
                cout << "Exiting program..." << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
    
    return 0;
}