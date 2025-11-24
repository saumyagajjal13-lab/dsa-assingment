#include <iostream>
#include <string>
using namespace std;

struct Employee {
    string name;
    float height; // in cm
    float weight; // in kg
    float avg;    // average of height and weight
};

int mergeSortComparisons = 0;
int selectionSortComparisons = 0;

void selectionSort(Employee arr[], int n) {
    selectionSortComparisons = 0;
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            selectionSortComparisons++;
            if (arr[j].avg < arr[minIndex].avg) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void merge(Employee arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Employee L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        mergeSortComparisons++;
        if (L[i].avg <= R[j].avg) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Employee arr[], int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void displayEmployees(Employee arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i].name << "\t" << arr[i].height << "cm\t" 
             << arr[i].weight << "kg\t" << arr[i].avg << endl;
    }
}

int main() {
    Employee employees[] = {
        {"John", 175, 70, 0},
        {"Alice", 160, 55, 0},
        {"Bob", 180, 80, 0},
        {"Emma", 165, 60, 0},
        {"Mike", 170, 75, 0}
    };
    int n = 5;
    
    // Calculate averages
    for (int i = 0; i < n; i++) {
        employees[i].avg = (employees[i].height + employees[i].weight) / 2;
    }
    
    cout << "Original list:\n";
    displayEmployees(employees, n);
    cout << endl;
    
    // Merge Sort
    Employee mergeEmployees[5];
    copy(employees, employees+n, mergeEmployees);
    mergeSortComparisons = 0;
    mergeSort(mergeEmployees, 0, n-1);
    cout << "After Merge Sort:\n";
    displayEmployees(mergeEmployees, n);
    cout << "Merge Sort Comparisons: " << mergeSortComparisons << endl << endl;
    
    // Selection Sort
    Employee selectionEmployees[5];
    copy(employees, employees+n, selectionEmployees);
    selectionSort(selectionEmployees, n);
    cout << "After Selection Sort:\n";
    displayEmployees(selectionEmployees, n);
    cout << "Selection Sort Comparisons: " << selectionSortComparisons << endl << endl;
    
    // Conclusion
    cout << "CONCLUSION:\n";
    cout << "Merge Sort is more efficient with " << mergeSortComparisons 
         << " comparisons vs " << selectionSortComparisons 
         << " comparisons in Selection Sort.\n";
    cout << "Time Complexity: Merge Sort O(n log n), Selection Sort O(n²)\n";
    
    return 0;
}