#include <iostream>
#include <string>
using namespace std;

class GeneralizedLinkedList {
public:
    struct Node {
        bool isAtom;
        char data;
        Node* down;
        Node* next;

        Node(char d) : isAtom(true), data(d), down(nullptr), next(nullptr) {}
        Node(Node* sublist) : isAtom(false), data('\0'), down(sublist), next(nullptr) {}
    };

private:
    Node* head;

    Node* createAtom(char ch) {
        return new Node(ch);
    }

    Node* createSublist(Node* sublist) {
        return new Node(sublist);
    }

    void displayList(Node* node) {
        if (!node) {
            cout << "{}";
            return;
        }

        cout << "{";
        Node* temp = node;
        bool first = true;

        while (temp) {
            if (!first) cout << ", ";

            if (temp->isAtom) cout << temp->data;
            else displayList(temp->down);

            temp = temp->next;
            first = false;
        }
        cout << "}";
    }

    void destroyList(Node* node) {
        while (node) {
            if (!node->isAtom) destroyList(node->down);
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }

public:
    GeneralizedLinkedList() : head(nullptr) {}

    void buildExampleSet() {
        head = createAtom('p');
        head->next = createAtom('q');

        Node* sublist = createAtom('r');
        sublist->next = createAtom('s');
        sublist->next->next = createAtom('t');

        sublist->next->next->next = createSublist(nullptr);

        Node* uvList = createAtom('u');
        uvList->next = createAtom('v');
        sublist->next->next->next->next = createSublist(uvList);

        sublist->next->next->next->next->next = createAtom('w');
        sublist->next->next->next->next->next->next = createAtom('x');

        Node* yzList = createAtom('y');
        yzList->next = createAtom('z');
        sublist->next->next->next->next->next->next->next = createSublist(yzList);

        sublist->next->next->next->next->next->next->next->next = createAtom('a');
        sublist->next->next->next->next->next->next->next->next->next = createAtom('b');

        head->next->next = createSublist(sublist);
    }

    void display() {
        cout << "S = ";
        displayList(head);
        cout << endl;
    }

    void addAtom(char ch) {
        Node* newNode = createAtom(ch);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void addSublist(Node* sublist) {
        Node* newNode = createSublist(sublist);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    ~GeneralizedLinkedList() {
        destroyList(head);
    }
};

int main() {
    GeneralizedLinkedList gll;

    cout << "Building default set..." << endl;
    gll.buildExampleSet();
    gll.display();

    cout << "\nAnother Example" << endl;
    GeneralizedLinkedList gll2;
    gll2.addAtom('a');
    gll2.addAtom('b');

    GeneralizedLinkedList::Node* innerList = new GeneralizedLinkedList::Node('x');
    innerList->next = new GeneralizedLinkedList::Node('y');
    innerList->next->next = new GeneralizedLinkedList::Node('z');

    gll2.addSublist(innerList);
    gll2.addAtom('c');

    gll2.display();
    return 0;
}
