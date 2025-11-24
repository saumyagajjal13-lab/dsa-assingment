#include <iostream>
using namespace std;

class StringOperations {
private:
    static const int MAX_SIZE = 100;
    char str[MAX_SIZE];

public:
    // Function to calculate string length
    int stringLength(const char s[]) {
        int len = 0;
        while (s[len] != '\0') {
            len++;
        }
        return len;
    }

    // Function to copy string
    void stringCopy(char dest[], const char src[]) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    // Function to reverse string
    void stringReverse(char s[]) {
        int len = stringLength(s);
        int start = 0, end = len - 1;
        
        while (start < end) {
            // Swap characters
            char temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++;
            end--;
        }
    }

    // Function to concatenate strings
    void stringConcat(char dest[], const char src[]) {
        int destLen = stringLength(dest);
        int i = 0;
        
        while (src[i] != '\0') {
            dest[destLen + i] = src[i];
            i++;
        }
        dest[destLen + i] = '\0';
    }

    // Function to display string
    void displayString(const char s[]) {
        int i = 0;
        while (s[i] != '\0') {
            cout << s[i];
            i++;
        }
        cout << endl;
    }

    void demo() {
        char str1[MAX_SIZE] = "Hello";
        char str2[MAX_SIZE] = "World";
        char result[MAX_SIZE];
        
        cout << "String Operations Demo:\n";
        cout << "String 1: "; displayString(str1);
        cout << "String 2: "; displayString(str2);
        
        cout << "Length of String 1: " << stringLength(str1) << endl;
        
        stringCopy(result, str1);
        cout << "Copied string: "; displayString(result);
        
        stringReverse(result);
        cout << "Reversed string: "; displayString(result);
        
        stringConcat(str1, str2);
        cout << "Concatenated string: "; displayString(str1);
    }
};

int main() {
    StringOperations ops;
    ops.demo();
    return 0;
}