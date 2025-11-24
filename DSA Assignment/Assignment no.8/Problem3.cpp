#include <iostream>
using namespace std;

class Node {
public:
    int empid;
    string name;
    Node *left, *right;
    Node(int id, string n) {
        empid = id;
        name = n;
        left = right = right = nullptr;
    }
};

class BST {
public:
    Node *root;
    BST() { root = nullptr; }

    Node* insert(Node *r, int id, string name) {
        if (!r) return new Node(id, name);
        if (id < r->empid) r->left = insert(r->left, id, name);
        else r->right = insert(r->right, id, name);
        return r;
    }

    Node* search(Node *r, int id) {
        if (!r || r->empid == id) return r;
        if (id < r->empid) return search(r->left, id);
        return search(r->right, id);
    }

    void inorder(Node *r) {
        if (!r) return;
        inorder(r->left);
        cout << r->empid << "  " << r->name << endl;
        inorder(r->right);
    }
};

int main() {
    BST t;
    int n;
    cout << "Enter number of employees: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int id;
        string name;
        cout << "Enter Emp ID and Name: ";
        cin >> id >> name;
        t.root = t.insert(t.root, id, name);
    }

    cout << "\nEmployees sorted by Emp-ID:\n";
    t.inorder(t.root);

    int x;
    cout << "\nEnter Emp-ID to search: ";
    cin >> x;

    Node *res = t.search(t.root, x);
    if (res) cout << "Record Found — ID: " << res->empid << "  Name: " << res->name << endl;
    else cout << "Employee Not Found\n";
}
