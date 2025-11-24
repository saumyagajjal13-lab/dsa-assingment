#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinaryTree {
private:
    Node* root;

    Node* createNode(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    void recursiveInorder(Node* root) {
        if (root == nullptr) return;
        recursiveInorder(root->left);
        cout << root->data << " ";
        recursiveInorder(root->right);
    }

    void recursivePreorder(Node* root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        recursivePreorder(root->left);
        recursivePreorder(root->right);
    }

    int countLeafNodes(Node* root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 1;
        return countLeafNodes(root->left) + countLeafNodes(root->right);
    }

    Node* mirrorImage(Node* root) {
        if (root == nullptr) return nullptr;
        
        Node* temp = root->left;
        root->left = mirrorImage(root->right);
        root->right = mirrorImage(temp);
        
        return root;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        Node* newNode = createNode(value);
        
        if (root == nullptr) {
            root = newNode;
            return;
        }
        
        if (value % 2 == 0) {
            Node* current = root;
            while (current->left != nullptr) {
                current = current->left;
            }
            current->left = newNode;
        } else {
            Node* current = root;
            while (current->right != nullptr) {
                current = current->right;
            }
            current->right = newNode;
        }
    }

    void displayRecursiveInorder() {
        cout << "Recursive Inorder: ";
        recursiveInorder(root);
        cout << endl;
    }

    void displayRecursivePreorder() {
        cout << "Recursive Preorder: ";
        recursivePreorder(root);
        cout << endl;
    }

    void displayLeafCount() {
        cout << "Number of leaf nodes: " << countLeafNodes(root) << endl;
    }

    void createMirror() {
        root = mirrorImage(root);
        cout << "Mirror image created.\n";
    }
};

int main() {
    BinaryTree tree;
    int choice, value;

    do {
        cout << "\nBinary Tree Recursive Operations\n";
        cout << "1. Insert\n";
        cout << "2. Recursive Inorder\n";
        cout << "3. Recursive Preorder\n";
        cout << "4. Count Leaf Nodes\n";
        cout << "5. Create Mirror Image\n";
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
                tree.displayRecursiveInorder();
                break;
            case 3:
                tree.displayRecursivePreorder();
                break;
            case 4:
                tree.displayLeafCount();
                break;
            case 5:
                tree.createMirror();
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