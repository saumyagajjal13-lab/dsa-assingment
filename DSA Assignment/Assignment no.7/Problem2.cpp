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

    int countNodes(Node* root) {
        if (root == nullptr) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    int computeHeight(Node* root) {
        if (root == nullptr) return 0;
        int leftHeight = computeHeight(root->left);
        int rightHeight = computeHeight(root->right);
        return 1 + max(leftHeight, rightHeight);
    }

    Node* mirrorImage(Node* root) {
        if (root == nullptr) return nullptr;
        
        Node* temp = root->left;
        root->left = mirrorImage(root->right);
        root->right = mirrorImage(temp);
        
        return root;
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

    void displayCount() {
        cout << "Total nodes: " << countNodes(root) << endl;
    }

    void displayHeight() {
        cout << "Height of BST: " << computeHeight(root) << endl;
    }

    void createMirror() {
        root = mirrorImage(root);
        cout << "Mirror image created. Inorder traversal: ";
        inorder(root);
        cout << endl;
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
        cout << "\nBST Operations\n";
        cout << "1. Insert\n";
        cout << "2. Count Nodes\n";
        cout << "3. Compute Height\n";
        cout << "4. Create Mirror Image\n";
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
                tree.displayCount();
                break;
            case 3:
                tree.displayHeight();
                break;
            case 4:
                tree.createMirror();
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