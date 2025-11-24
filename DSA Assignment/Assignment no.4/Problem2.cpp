#include <iostream>
using namespace std;

class Polynomial {
private:
    struct Term {
        int coeff;
        int exp;
        Term* next;
        Term(int c, int e) : coeff(c), exp(e), next(nullptr) {}
    };
    
    Term* head;
    
public:
    Polynomial() : head(nullptr) {}
    
    void addTerm(int coeff, int exp) {
        if (coeff == 0) return;
        
        Term* newTerm = new Term(coeff, exp);
        
        if (!head || head->exp < exp) {
            newTerm->next = head;
            head = newTerm;
            return;
        }
        
        Term* temp = head;
        while (temp->next && temp->next->exp > exp) {
            temp = temp->next;
        }
        
        if (temp->exp == exp) {
            temp->coeff += coeff;
            if (temp->coeff == 0) {
                if (temp == head) {
                    head = head->next;
                    delete temp;
                }
            }
            delete newTerm;
        } else if (temp->next && temp->next->exp == exp) {
            temp->next->coeff += coeff;
            if (temp->next->coeff == 0) {
                Term* del = temp->next;
                temp->next = temp->next->next;
                delete del;
            }
            delete newTerm;
        } else {
            newTerm->next = temp->next;
            temp->next = newTerm;
        }
    }
    
    Polynomial* add(Polynomial& other) {
        Polynomial* result = new Polynomial();
        Term *t1 = head, *t2 = other.head;
        
        while (t1 && t2) {
            if (t1->exp == t2->exp) {
                int sumCoeff = t1->coeff + t2->coeff;
                if (sumCoeff != 0) {
                    result->addTerm(sumCoeff, t1->exp);
                }
                t1 = t1->next;
                t2 = t2->next;
            } else if (t1->exp > t2->exp) {
                result->addTerm(t1->coeff, t1->exp);
                t1 = t1->next;
            } else {
                result->addTerm(t2->coeff, t2->exp);
                t2 = t2->next;
            }
        }
        
        while (t1) {
            result->addTerm(t1->coeff, t1->exp);
            t1 = t1->next;
        }
        
        while (t2) {
            result->addTerm(t2->coeff, t2->exp);
            t2 = t2->next;
        }
        
        return result;
    }
    
    void display() {
        if (!head) {
            cout << "0" << endl;
            return;
        }
        
        Term* temp = head;
        bool first = true;
        
        while (temp) {
            if (!first) {
                if (temp->coeff > 0) cout << " + ";
                else cout << " ";
            }
            
            if (temp->coeff < 0 && !first) {
                cout << temp->coeff;
            } else if (temp->coeff < 0) {
                cout << temp->coeff;
            } else {
                cout << temp->coeff;
            }
            
            if (temp->exp > 0) {
                cout << "x";
                if (temp->exp > 1) cout << "^" << temp->exp;
            }
            
            temp = temp->next;
            first = false;
        }
        cout << endl;
    }
    
    void input() {
        int n;
        cout << "Enter number of terms: ";
        cin >> n;
        
        for (int i = 0; i < n; i++) {
            int coeff, exp;
            cout << "Enter coefficient and exponent for term " << i+1 << ": ";
            cin >> coeff >> exp;
            addTerm(coeff, exp);
        }
    }
    
    ~Polynomial() {
        while (head) {
            Term* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Polynomial p1, p2;
    
    cout << "=== Polynomial Addition using Singly Linked List ===" << endl;
    
    cout << "\nEnter first polynomial:" << endl;
    p1.input();
    
    cout << "\nEnter second polynomial:" << endl;
    p2.input();
    
    cout << "\nFirst Polynomial: ";
    p1.display();
    
    cout << "Second Polynomial: ";
    p2.display();
    
    Polynomial* result = p1.add(p2);
    
    cout << "\nResultant Polynomial (Sum): ";
    result->display();
    
    delete result;
    
    cout << "\n=== Testing with predefined polynomials ===" << endl;
    Polynomial p3, p4;
    
    p3.addTerm(5, 3);
    p3.addTerm(4, 2);
    p3.addTerm(2, 0);
    
    p4.addTerm(3, 3);
    p4.addTerm(-4, 2);
    p4.addTerm(1, 1);
    p4.addTerm(6, 0);
    
    cout << "\nPolynomial 1: ";
    p3.display();
    
    cout << "Polynomial 2: ";
    p4.display();
    
    Polynomial* result2 = p3.add(p4);
    
    cout << "Sum: ";
    result2->display();
    
    delete result2;
    
    return 0;
}