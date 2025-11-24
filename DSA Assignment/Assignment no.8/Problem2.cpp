// bst_menu.cpp
#include <iostream>
#include <limits>
using namespace std;

class BST {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertRec(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insertRec(node->left, key);
        else if (key > node->key) node->right = insertRec(node->right, key);
        // if equal, do nothing (no duplicates). You may change policy if duplicates required.
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* removeRec(Node* node, int key, bool &removed) {
        if (!node) return nullptr;
        if (key < node->key) node->left = removeRec(node->left, key, removed);
        else if (key > node->key) node->right = removeRec(node->right, key, removed);
        else {
            removed = true;
            // Node with only one child or no child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Node with two children: get inorder successor (smallest in right subtree)
            Node* succ = findMin(node->right);
            node->key = succ->key;
            node->right = removeRec(node->right, succ->key, removed); 
            // Note: 'removed' already true; removing successor won't set it false
        }
        return node;
    }

    bool findRec(Node* node, int key) {
        if (!node) return false;
        if (node->key == key) return true;
        if (key < node->key) return findRec(node->left, key);
        return findRec(node->right, key);
    }

    void inorderRec(Node* node) {
        if (!node) return;
        inorderRec(node->left);
        cout << node->key << " ";
        inorderRec(node->right);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int key) {
        if (findRec(root, key)) {
            cout << "Key " << key << " already exists. Duplicates not allowed.\n";
            return;
        }
        root = insertRec(root, key);
        cout << "Inserted " << key << ".\n";
    }

    void removeKey(int key) {
        bool removed = false;
        root = removeRec(root, key, removed);
        if (removed) cout << "Deleted key " << key << ".\n";
        else cout << "Key " << key << " not found.\n";
    }

    void findKey(int key) {
        bool found = findRec(root, key);
        if (found) cout << "Key " << key << " found in the tree.\n";
        else cout << "Key " << key << " NOT found.\n";
    }

    void showInorder() {
        if (!root) {
            cout << "<empty tree>\n";
            return;
        }
        cout << "Inorder (sorted): ";
        inorderRec(root);
        cout << "\n";
    }
};

int readInt(const string &prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cout << "Invalid input. Please enter an integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    BST tree;
    int choice;
    cout << "=== Binary Search Tree (numeric keys) ===\n";
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Find\n";
        cout << "4. Show (Inorder)\n";
        cout << "5. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: {
                int k = readInt("Enter key to insert: ");
                tree.insert(k);
                break;
            }
            case 2: {
                int k = readInt("Enter key to delete: ");
                tree.removeKey(k);
                break;
            }
            case 3: {
                int k = readInt("Enter key to find: ");
                tree.findKey(k);
                break;
            }
            case 4:
                tree.showInorder();
                break;
            case 5:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
