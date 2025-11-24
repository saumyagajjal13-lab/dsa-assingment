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

    Product(string c, string n, float p, int q, string rcv, string exp) {
        code = c;
        name = n;
        price = p;
        qty = q;
        received = rcv;
        expiry = exp;
        left = right = nullptr;
    }
};

class Tree {
public:
    Product *root;
    Tree() { root = nullptr; }

    Product* insert(Product *r, Product *p) {
        if (!r) return p;
        if (p->name < r->name) r->left = insert(r->left, p);
        else r->right = insert(r->right, p);
        return r;
    }

    void inorder(Product *r) {
        if (!r) return;
        inorder(r->left);
        cout << r->code << "  " << r->name << "  " << r->price << "  " << r->qty 
             << "  " << r->received << "  " << r->expiry << endl;
        inorder(r->right);
    }

    void listExpired(Product *r, string today) {
        if (!r) return;
        cout << "[" << r->name << " | Exp: " << r->expiry << "]\n";
        if (r->expiry < today) 
            cout << "→ EXPIRED PRODUCT\n";
        listExpired(r->left, today);
        listExpired(r->right, today);
    }
};

int main() {
    Tree t;
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

    cout << "\nInventory (Inorder — Sorted by Product Name):\n";
    t.inorder(t.root);

    string date;
    cout << "\nEnter today's date (YYYY-MM-DD) to show expired: ";
    cin >> date;
    cout << "\nExpired Products (Preorder Listing):\n";
    t.listExpired(t.root, date);
}
