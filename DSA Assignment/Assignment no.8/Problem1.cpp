#include <iostream>
#include <string>
using namespace std;

class BST {
private:
    struct Node {
        string name;
        int rank;
        Node* left;
        Node* right;
        Node(string n, int r) : name(n), rank(r), left(NULL), right(NULL) {}
    };

    Node* root;
    int roll_no;

    Node* insert(Node* root, string name, int rank) {
        if (root == NULL) return new Node(name, rank);
        if (rank < root->rank)
            root->left = insert(root->left, name, rank);
        else
            root->right = insert(root->right, name, rank);
        return root;
    }

    void assignRollNumber(Node* root) {
        if (root == NULL) return;
        assignRollNumber(root->left);
        cout << "Roll No: " << roll_no++ << " | Name: " << root->name << " | Rank: " << root->rank << endl;
        assignRollNumber(root->right);
    }

public:
    BST() { root = NULL; }

    void addStudent(string name, int rank) {
        root = insert(root, name, rank);
    }

    void displayRollList() {
        roll_no = 1;
        cout << "\n--- ROLL NUMBERS ALLOTMENT LIST ---\n";
        assignRollNumber(root);
    }
};

int main() {
    BST obj;
    int n, rank;
    string name;

    cout << "Enter total number of students: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Name: ";
        cin >> name;
        cout << "Enter Previous Year Rank: ";
        cin >> rank;
        obj.addStudent(name, rank);
    }

    obj.displayRollList();
    return 0;
}
