#include <iostream>
#include <stack>
#include <string>
using namespace std;

class InfixToPostfix {
private:
    // Check if character is operator
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    // Get precedence of operator
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

public:
    string convert(string infix) {
        stack<char> st;
        string postfix = "";
        int step = 1;

        cout << "Step-by-step conversion:\n";
        cout << "Infix: " << infix << endl << endl;

        for (int i = 0; i < infix.length(); i++) {
            char c = infix[i];
            
            cout << "Step " << step++ << ": Current char = '" << c << "'\n";
            cout << "Stack: ";
            displayStack(st);
            cout << "Postfix: " << postfix << endl;

            // If operand, add to output
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
                postfix += c;
                cout << "Action: Added '" << c << "' to postfix\n";
            }
            // If '(', push to stack
            else if (c == '(') {
                st.push(c);
                cout << "Action: Pushed '(' to stack\n";
            }
            // If ')', pop until '('
            else if (c == ')') {
                cout << "Action: Popping until '(' found\n";
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    cout << "Popped '" << st.top() << "' from stack to postfix\n";
                    st.pop();
                }
                st.pop(); // Remove '('
            }
            // If operator
            else if (isOperator(c)) {
                cout << "Action: Processing operator '" << c << "'\n";
                while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                    postfix += st.top();
                    cout << "Popped '" << st.top() << "' from stack to postfix\n";
                    st.pop();
                }
                st.push(c);
                cout << "Pushed '" << c << "' to stack\n";
            }
            cout << "------------------------\n";
        }

        // Pop all remaining operators
        cout << "Final step: Popping remaining operators from stack\n";
        while (!st.empty()) {
            postfix += st.top();
            cout << "Popped '" << st.top() << "' from stack to postfix\n";
            st.pop();
        }

        return postfix;
    }

    void displayStack(stack<char> st) {
        if (st.empty()) {
            cout << "empty";
        } else {
            stack<char> temp;
            while (!st.empty()) {
                temp.push(st.top());
                st.pop();
            }
            while (!temp.empty()) {
                cout << temp.top() << " ";
                temp.pop();
            }
        }
        cout << endl;
    }
};

int main() {
    InfixToPostfix converter;
    string infix;

    cout << "Enter infix expression: ";
    cin >> infix;

    string postfix = converter.convert(infix);
    cout << "\nFinal Postfix Expression: " << postfix << endl;

    return 0;
}