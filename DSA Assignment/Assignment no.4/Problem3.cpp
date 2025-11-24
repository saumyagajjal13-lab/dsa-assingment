#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int d) : data(d), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void bubbleSort() {
        if (!head) return;
        bool swapped;
        Node* ptr;
        Node* end = nullptr;
        do {
            swapped = false;
            ptr = head;
            while (ptr->next != end) {
                if (ptr->data > ptr->next->data) {
                    int temp = ptr->data;
                    ptr->data = ptr->next->data;
                    ptr->next->data = temp;
                    swapped = true;
                }
                ptr = ptr->next;
            }
            end = ptr;
        } while (swapped);
    }

    ~DoublyLinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList dll;
    int n, x;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter " << n << " numbers:\n";
    for (int i = 0; i < n; i++) {
        cin >> x;
        dll.insert(x);
    }

    cout << "Original List: ";
    dll.display();

    dll.bubbleSort();

    cout << "Sorted List: ";
    dll.display();
    
    return 0;
}
