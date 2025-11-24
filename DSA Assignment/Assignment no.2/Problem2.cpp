#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int roll_no;
    float total_marks;
};

int bubbleSortSwaps = 0;
int quickSortSwaps = 0;

void bubbleSort(Student arr[], int n) {
    bubbleSortSwaps = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].roll_no > arr[j+1].roll_no) {
                swap(arr[j], arr[j+1]);
                bubbleSortSwaps++;
            }
        }
    }
}

int partition(Student arr[], int low, int high) {
    int pivot = arr[high].roll_no;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].roll_no <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            quickSortSwaps++;
        }
    }
    swap(arr[i+1], arr[high]);
    quickSortSwaps++;
    return i+1;
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void displayStudents(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i].roll_no << " " << arr[i].name << " " << arr[i].total_marks << endl;
    }
}

int main() {
    Student students[] = {
        {"John", 25, 85.5},
        {"Alice", 12, 92.0},
        {"Bob", 8, 78.5},
        {"Emma", 30, 88.0},
        {"Mike", 5, 76.5}
    };
    int n = 5;
    
    // Bubble Sort
    Student bubbleStudents[5];
    copy(students, students+n, bubbleStudents);
    bubbleSort(bubbleStudents, n);
    cout << "After Bubble Sort:\n";
    displayStudents(bubbleStudents, n);
    cout << "Bubble Sort Swaps: " << bubbleSortSwaps << endl << endl;
    
    // Quick Sort
    Student quickStudents[5];
    copy(students, students+n, quickStudents);
    quickSort(quickStudents, 0, n-1);
    cout << "After Quick Sort:\n";
    displayStudents(quickStudents, n);
    cout << "Quick Sort Swaps: " << quickSortSwaps << endl;
    
    return 0;
}