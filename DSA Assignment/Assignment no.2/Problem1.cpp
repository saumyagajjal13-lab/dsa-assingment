#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    string roll_no;
    string year;
    string division;
};

int linearSearch(Student students[], int n, string targetName, string targetRoll) {
    for (int i = 0; i < n; i++) {
        if (students[i].year == "SY" && 
            students[i].name == targetName && 
            students[i].roll_no == targetRoll) {
            return i;
        }
    }
    return -1;
}

int main() {
    Student students[] = {
        {"ABC", "15", "SY", "A"},
        {"XYZ", "17", "SY", "B"},
        {"PQR", "12", "TY", "A"},
        {"LMN", "20", "SY", "C"},
        {"XYZ", "25", "TY", "B"}
    };
    
    int n = 5;
    string targetName = "XYZ";
    string targetRoll = "17";
    
    int result = linearSearch(students, n, targetName, targetRoll);
    
    if (result != -1) {
        cout << "Student found!\n";
        cout << "Name: " << students[result].name << endl;
        cout << "Roll No: " << students[result].roll_no << endl;
        cout << "Year: " << students[result].year << endl;
        cout << "Division: " << students[result].division << endl;
    } else {
        cout << "Student not found!\n";
    }
    
    return 0;
}