#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BST {
private:
    Node* root;

    Node* createNode(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    Node* insertNode(Node* root, int value) {
        if (root == nullptr) {
            return createNode(value);
        }
        if (value < root->data) {
            root->left = insertNode(root->left, value);
        } else if (value > root->data) {
            root->right = insertNode(root->right, value);
        }
        return root;
    }

    int findMinimum(Node* root) {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return -1;
        }
        while (root->left != nullptr) {
            root = root->left;
        }
        return root->data;
    }

    int findMaximum(Node* root) {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return -1;
        }
        while (root->right != nullptr) {
            root = root->right;
        }
        return root->data;
    }

    bool searchNode(Node* root, int value) {
        if (root == nullptr) return false;
        if (root->data == value) return true;
        if (value < root->data) return searchNode(root->left, value);
        return searchNode(root->right, value);
    }

    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(int value) {
        root = insertNode(root, value);
    }

    void findMin() {
        int minVal = findMinimum(root);
        if (minVal != -1) {
            cout << "Minimum value: " << minVal << endl;
        }
    }

    void findMax() {
        int maxVal = findMaximum(root);
        if (maxVal != -1) {
            cout << "Maximum value: " << maxVal << endl;
        }
    }

    void search(int value) {
        if (searchNode(root, value)) {
            cout << value << " found in BST.\n";
        } else {
            cout << value << " not found in BST.\n";
        }
    }

    void displayInorder() {
        cout << "Inorder traversal: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int choice, value;

    do {
        cout << "\nBST Min/Max Search\n";
        cout << "1. Insert\n";
        cout << "2. Find Minimum\n";
        cout << "3. Find Maximum\n";
        cout << "4. Search Value\n";
        cout << "5. Display Inorder\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                tree.findMin();
                break;
            case 3:
                tree.findMax();
                break;
            case 4:
                cout << "Enter value to search: ";
                cin >> value;
                tree.search(value);
                break;
            case 5:
                tree.displayInorder();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 6);

    return 0;
}