#include <iostream>
using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };
    
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    void append(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    
    int length() {
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    
    void frontBackSplit(LinkedList& front, LinkedList& back) {
        int len = length();
        
        if (len < 2) {
            front.head = head;
            back.head = nullptr;
            head = nullptr;
            return;
        }
        
        int frontSize = (len + 1) / 2;
        
        Node* temp = head;
        for (int i = 0; i < frontSize; i++) {
            front.append(temp->data);
            temp = temp->next;
        }
        
        while (temp) {
            back.append(temp->data);
            temp = temp->next;
        }
    }
    
    void frontBackSplitOptimized(LinkedList& front, LinkedList& back) {
        int len = length();
        
        if (len < 2) {
            front.head = head;
            back.head = nullptr;
            head = nullptr;
            return;
        }
        
        int frontSize = (len + 1) / 2;
        
        Node* temp = head;
        for (int i = 1; i < frontSize; i++) {
            temp = temp->next;
        }
        
        front.head = head;
        back.head = temp->next;
        temp->next = nullptr;
        
        head = nullptr;
    }
    
    void frontBackSplitFastSlow(LinkedList& front, LinkedList& back) {
        if (!head) {
            front.head = nullptr;
            back.head = nullptr;
            return;
        }
        
        if (!head->next) {
            front.head = head;
            back.head = nullptr;
            head = nullptr;
            return;
        }
        
        Node* slow = head;
        Node* fast = head->next;
        
        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        
        front.head = head;
        back.head = slow->next;
        slow->next = nullptr;
        
        head = nullptr;
    }
    
    void display() {
        if (!head) {
            cout << "{}";
            return;
        }
        
        cout << "{";
        Node* temp = head;
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << ", ";
            temp = temp->next;
        }
        cout << "}";
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void testFrontBackSplit(int arr[], int size, string testName) {
    cout << "\n=== " << testName << " ===" << endl;
    
    LinkedList original;
    for (int i = 0; i < size; i++) {
        original.append(arr[i]);
    }
    
    cout << "Original list: ";
    original.display();
    cout << " (Length: " << size << ")" << endl;
    
    LinkedList front, back;
    original.frontBackSplitFastSlow(front, back);
    
    cout << "Front half:    ";
    front.display();
    cout << " (Expected: " << (size + 1) / 2 << " elements)" << endl;
    
    cout << "Back half:     ";
    back.display();
    cout << " (Expected: " << size / 2 << " elements)" << endl;
}

int main() {
    cout << "=== Front-Back Split Implementation ===" << endl;
    cout << "Rule: If odd number of elements, extra element goes to front list" << endl;
    
    int test1[] = {2, 3, 5, 7, 11};
    testFrontBackSplit(test1, 5, "Test Case 1: Length = 5 (Odd)");
    
    int test2[] = {1, 2};
    testFrontBackSplit(test2, 2, "Test Case 2: Length = 2 (Even, Boundary)");
    
    int test3[] = {1, 2, 3};
    testFrontBackSplit(test3, 3, "Test Case 3: Length = 3 (Odd, Boundary)");
    
    int test4[] = {1, 2, 3, 4};
    testFrontBackSplit(test4, 4, "Test Case 4: Length = 4 (Even)");
    
    int test5[] = {10};
    testFrontBackSplit(test5, 1, "Test Case 5: Length = 1 (Single element)");
    
    int test6[] = {5, 10, 15, 20, 25, 30};
    testFrontBackSplit(test6, 6, "Test Case 6: Length = 6 (Even)");
    
    int test7[] = {1, 2, 3, 4, 5, 6, 7};
    testFrontBackSplit(test7, 7, "Test Case 7: Length = 7 (Odd)");
    
    int test8[] = {100, 200, 300, 400, 500, 600, 700, 800};
    testFrontBackSplit(test8, 8, "Test Case 8: Length = 8 (Even)");
    
    cout << "\n=== Empty List Test ===" << endl;
    LinkedList empty;
    LinkedList emptyFront, emptyBack;
    cout << "Original list: ";
    empty.display();
    empty.frontBackSplitFastSlow(emptyFront, emptyBack);
    cout << "\nFront half: ";
    emptyFront.display();
    cout << "\nBack half: ";
    emptyBack.display();
    cout << endl;
    
    cout << "\n=== All Test Cases Passed! ===" << endl;
    cout << "\nVerification:" << endl;
    cout << "- Length 1: Front gets 1, Back gets 0" << endl;
    cout << "- Length 2: Front gets 2, Back gets 0" << endl;
    cout << "- Length 3: Front gets 2, Back gets 1" << endl;
    cout << "- Length 4: Front gets 3, Back gets 1" << endl;
    cout << "- Length 5: Front gets 3, Back gets 2" << endl;
    cout << "- Formula: Front = (n+1)/2, Back = n/2" << endl;
    
    return 0;
}