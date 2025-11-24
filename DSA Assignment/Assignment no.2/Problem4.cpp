#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    float marks;
    int roll_no;
};

void bubbleSortWithAnalysis(Student arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        cout << "Pass " << i+1 << ":\n";
        bool swapped = false;
        
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].marks < arr[j+1].marks) { // Descending order for topper first
                swap(arr[j], arr[j+1]);
                swapped = true;
                cout << "  Swapped: " << arr[j+1].name << " (" << arr[j+1].marks 
                     << ") <-> " << arr[j].name << " (" << arr[j].marks << ")\n";
            }
        }
        
        // Display current state after pass
        cout << "  Current order: ";
        for (int k = 0; k < n; k++) {
            cout << arr[k].name << "(" << arr[k].marks << ") ";
        }
        cout << endl << endl;
        
        if (!swapped) break;
    }
}

int main() {
    Student students[] = {
        {"Alice", 92.5, 0},
        {"Bob", 78.0, 0},
        {"Carol", 85.5, 0},
        {"David", 95.0, 0},
        {"Eve", 88.5, 0}
    };
    int n = 5;
    
    cout << "Original order: ";
    for (int i = 0; i < n; i++) {
        cout << students[i].name << "(" << students[i].marks << ") ";
    }
    cout << endl << endl;
    
    bubbleSortWithAnalysis(students, n);
    
    // Assign roll numbers
    for (int i = 0; i < n; i++) {
        students[i].roll_no = i + 1;
    }
    
    cout << "Final Result:\n";
    cout << "Roll No\tName\tMarks\n";
    for (int i = 0; i < n; i++) {
        cout << students[i].roll_no << "\t" << students[i].name 
             << "\t" << students[i].marks << endl;
    }
    
    return 0;
}
