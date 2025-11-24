#include <iostream>
using namespace std;

class Product {
public:
    string code, name;
    float price;
    int qty;
    string received;
    string expiry;
    Product *left, *right;

    Product(string c, string n, float p, int q, string r, string e) {
        code = c;
        name = n;
        price = p;
        qty = q;
        received = r;
        expiry = e;
        left = right = nullptr;
    }
};

class Inventory {
public:
    Product *root;
    Inventory() { root = nullptr; }

    Product* insert(Product *r, Product *p) {
        if (!r) return p;
        if (p->name < r->name) r->left = insert(r->left, p);
        else r->right = insert(r->right, p);
        return r;
    }

    Product* findMin(Product *r) {
        while (r->left) r = r->left;
        return r;
    }

    Product* deleteByCode(Product *r, string code) {
        if (!r) return r;
        if (code < r->code) r->left = deleteByCode(r->left, code);
        else if (code > r->code) r->right = deleteByCode(r->right, code);
        else {
            if (!r->left) return r->right;
            if (!r->right) return r->left;
            Product *temp = findMin(r->right);
            r->name = temp->name;
            r->code = temp->code;
            r->price = temp->price;
            r->qty = temp->qty;
            r->received = temp->received;
            r->expiry = temp->expiry;
            r->right = deleteByCode(r->right, temp->code);
        }
        return r;
    }

    Product* deleteExpired(Product *r, string today) {
        if (!r) return r;
        r->left = deleteExpired(r->left, today);
        r->right = deleteExpired(r->right, today);
        if (r->expiry < today) return deleteByCode(r, r->code);
        return r;
    }

    void inorder(Product *r) {
        if (!r) return;
        inorder(r->left);
        cout << r->code << "  " << r->name << "  " << r->price << "  " << r->qty
             << "  " << r->received << "  " << r->expiry << endl;
        inorder(r->right);
    }
};

int main() {
    Inventory t;
    int n;
    cout << "Enter number of products: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string c, name, rec, exp;
        float price;
        int qty;
        cout << "Enter Code, Name, Price, Qty, Received-Date, Expiry-Date: ";
        cin >> c >> name >> price >> qty >> rec >> exp;
        Product *p = new Product(c, name, price, qty, rec, exp);
        t.root = t.insert(t.root, p);
    }

    cout << "\nInventory before deletion:\n";
    t.inorder(t.root);

    int option;
    cout << "\n1.Delete by Code\n2.Delete All Expired\nEnter: ";
    cin >> option;

    if (option == 1) {
        string code;
        cout << "Enter Code: ";
        cin >> code;
        t.root = t.deleteByCode(t.root, code);
    } else {
        string today;
        cout << "Enter today's date (YYYY-MM-DD): ";
        cin >> today;
        t.root = t.deleteExpired(t.root, today);
    }

    cout << "\nInventory after deletion:\n";
    t.inorder(t.root);
}
