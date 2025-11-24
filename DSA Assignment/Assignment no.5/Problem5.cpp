#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

class PostfixEvaluator {
private:
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    int performOperation(char op, int a, int b) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) {
                    cout << "ERROR: Division by zero!\n";
                    return 0;
                }
                return a / b;
            default: return 0;
        }
    }

public:
    int evaluate(string postfix) {
        stack<int> st;
        int step = 1;

        cout << "Evaluating: " << postfix << endl;
        cout << "Step-by-step evaluation:\n";

        for (int i = 0; i < postfix.length(); i++) {
            char c = postfix[i];
            cout << "Step " << step++ << ": Current token = '" << c << "'\n";

            // If operand, push to stack
            if (isdigit(c)) {
                st.push(c - '0'); // Convert char to int
                cout << "Pushed " << (c - '0') << " to stack\n";
            }
            // If operator, pop two operands and perform operation
            else if (isOperator(c)) {
                if (st.size() < 2) {
                    cout << "ERROR: Insufficient operands for operator '" << c << "'\n";
                    return 0;
                }

                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                int result = performOperation(c, a, b);

                cout << "Popped " << b << " and " << a << endl;
                cout << "Operation: " << a << " " << c << " " << b << " = " << result << endl;
                
                st.push(result);
                cout << "Pushed result " << result << " to stack\n";
            }
            else {
                cout << "Invalid character '" << c << "' - ignored\n";
            }

            // Display current stack
            cout << "Current stack: ";
            displayStack(st);
            cout << "------------------------\n";
        }

        if (st.size() != 1) {
            cout << "ERROR: Invalid expression!\n";
            return 0;
        }

        int finalResult = st.top();
        cout << "Final result: " << finalResult << endl;
        return finalResult;
    }

    void displayStack(stack<int> st) {
        if (st.empty()) {
            cout << "empty";
        } else {
            stack<int> temp;
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
    PostfixEvaluator evaluator;
    string postfix;

    cout << "Enter postfix expression: ";
    cin >> postfix;

    int result = evaluator.evaluate(postfix);
    cout << "\nExpression Result: " << result << endl;

    // Example expressions to try:
    // "23*54*+9-"  -> (2*3)+(5*4)-9 = 6+20-9 = 17
    // "34+2*7/"    -> (3+4)*2/7 = 14/7 = 2

    return 0;
}