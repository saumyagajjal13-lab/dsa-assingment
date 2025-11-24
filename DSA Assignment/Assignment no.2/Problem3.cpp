#include <iostream>
using namespace std;

void quickSort(int marks[], int low, int high, int pass = 0) {
    if (low < high) {
        int pivot = marks[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (marks[j] <= pivot) {
                i++;
                swap(marks[i], marks[j]);
            }
        }
        swap(marks[i+1], marks[high]);
        
        // Display pass
        cout << "Pass " << pass + 1 << ": ";
        for (int k = low; k <= high; k++) {
            cout << marks[k] << " ";
        }
        cout << endl;
        
        int pi = i + 1;
        quickSort(marks, low, pi-1, pass+1);
        quickSort(marks, pi+1, high, pass+1);
    }
}

int findMin(int marks[], int low, int high) {
    if (low == high) return marks[low];
    
    int mid = (low + high) / 2;
    int leftMin = findMin(marks, low, mid);
    int rightMin = findMin(marks, mid+1, high);
    
    return (leftMin < rightMin) ? leftMin : rightMin;
}

int findMax(int marks[], int low, int high) {
    if (low == high) return marks[low];
    
    int mid = (low + high) / 2;
    int leftMax = findMax(marks, low, mid);
    int rightMax = findMax(marks, mid+1, high);
    
    return (leftMax > rightMax) ? leftMax : rightMax;
}

int main() {
    int marks[] = {85, 92, 78, 65, 95, 88, 72};
    int n = 7;
    
    cout << "Original marks: ";
    for (int i = 0; i < n; i++) {
        cout << marks[i] << " ";
    }
    cout << endl << endl;
    
    quickSort(marks, 0, n-1);
    
    cout << "\nSorted marks: ";
    for (int i = 0; i < n; i++) {
        cout << marks[i] << " ";
    }
    cout << endl;
    
    cout << "Minimum marks: " << findMin(marks, 0, n-1) << endl;
    cout << "Maximum marks: " << findMax(marks, 0, n-1) << endl;
    
    return 0;
}