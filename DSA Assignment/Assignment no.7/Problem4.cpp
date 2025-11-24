#include <iostream>
#include <stack>
#include <queue>
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

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        Node* newNode = createNode(value);
        
        if (root == nullptr) {
            root = newNode;
            return;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            } else {
                q.push(current->left);
            }
            
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            } else {
                q.push(current->right);
            }
        }
    }

    void nonRecursiveInorder() {
        cout << "Non-recursive Inorder: ";
        stack<Node*> s;
        Node* current = root;
        
        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            
            current = s.top();
            s.pop();
            cout << current->data << " ";
            
            current = current->right;
        }
        cout << endl;
    }

    void nonRecursivePreorder() {
        cout << "Non-recursive Preorder: ";
        if (root == nullptr) return;
        
        stack<Node*> s;
        s.push(root);
        
        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            cout << current->data << " ";
            
            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
        cout << endl;
    }

    int countLeafNodes() {
        if (root == nullptr) return 0;
        
        queue<Node*> q;
        q.push(root);
        int leafCount = 0;
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            if (current->left == nullptr && current->right == nullptr) {
                leafCount++;
            }
            
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        return leafCount;
    }

    void mirrorImage() {
        if (root == nullptr) return;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            Node* temp = current->left;
            current->left = current->right;
            current->right = temp;
            
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << "Mirror image created.\n";
    }
};

int main() {
    BinaryTree tree;
    int choice, value;

    do {
        cout << "\nBinary Tree Non-Recursive Operations\n";
        cout << "1. Insert\n";
        cout << "2. Non-recursive Inorder\n";
        cout << "3. Non-recursive Preorder\n";
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
                tree.nonRecursiveInorder();
                break;
            case 3:
                tree.nonRecursivePreorder();
                break;
            case 4:
                cout << "Number of leaf nodes: " << tree.countLeafNodes() << endl;
                break;
            case 5:
                tree.mirrorImage();
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