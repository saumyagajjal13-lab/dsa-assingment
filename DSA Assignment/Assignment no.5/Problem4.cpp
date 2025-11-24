#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BalancedParentheses {
private:
    bool isOpening(char c) {
        return (c == '(' || c == '{' || c == '[');
    }

    bool isClosing(char c) {
        return (c == ')' || c == '}' || c == ']');
    }

    bool isMatching(char open, char close) {
        return (open == '(' && close == ')') ||
               (open == '{' && close == '}') ||
               (open == '[' && close == ']');
    }

public:
    bool check(string s) {
        stack<char> st;
        
        cout << "Checking: " << s << endl;
        cout << "Step-by-step analysis:\n";

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            cout << "Character '" << c << "': ";

            if (isOpening(c)) {
                st.push(c);
                cout << "Opening bracket - pushed to stack\n";
            }
            else if (isClosing(c)) {
                if (st.empty()) {
                    cout << "ERROR: Closing bracket without matching opening bracket!\n";
                    return false;
                }
                
                char top = st.top();
                if (isMatching(top, c)) {
                    st.pop();
                    cout << "Closing bracket matches '" << top << "' - popped from stack\n";
                } else {
                    cout << "ERROR: Mismatch! '" << top << "' doesn't match '" << c << "'\n";
                    return false;
                }
            }
            else {
                cout << "Not a bracket - ignored\n";
            }

            // Display current stack
            cout << "Current stack: ";
            displayStack(st);
            cout << "------------------------\n";
        }

        bool result = st.empty();
        if (result) {
            cout << "SUCCESS: All brackets are balanced!\n";
        } else {
            cout << "ERROR: Unclosed brackets remaining!\n";
        }
        
        return result;
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
    BalancedParentheses checker;
    string input;

    cout << "Enter string with parentheses: ";
    cin >> input;

    bool isBalanced = checker.check(input);
    cout << "\nFinal Result: " << (isBalanced ? "BALANCED" : "NOT BALANCED") << endl;

    return 0;
}