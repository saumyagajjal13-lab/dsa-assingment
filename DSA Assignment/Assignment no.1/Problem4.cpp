#include <iostream>
#include <vector>
using namespace std;

struct Element {
    int row, col, value;
};

class SparseMatrix {
private:
    vector<Element> compactForm;
    int rows, cols, nonZeroCount;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), nonZeroCount(0) {}

    // Convert from 2D array to compact form
    void from2DArray(int** matrix) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] != 0) {
                    Element elem;
                    elem.row = i;
                    elem.col = j;
                    elem.value = matrix[i][j];
                    compactForm.push_back(elem);
                    nonZeroCount++;
                }
            }
        }
    }

    // Display compact representation
    void displayCompact() {
        cout << "Compact Representation (Row, Column, Value):\n";
        cout << "Rows: " << rows << ", Columns: " << cols << ", Non-zero: " << nonZeroCount << endl;
        
        for (const auto& elem : compactForm) {
            cout << "(" << elem.row << ", " << elem.col << ", " << elem.value << ")\n";
        }
    }

    // Display in matrix form
    void displayMatrix() {
        cout << "Sparse Matrix (" << rows << "x" << cols << "):\n";
        
        // Create a 2D array filled with zeros
        int** matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols]();
        }
        
        // Fill with non-zero values
        for (const auto& elem : compactForm) {
            matrix[elem.row][elem.col] = elem.value;
        }
        
        // Display
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
        
        // Cleanup
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Simple transpose
    SparseMatrix simpleTranspose() {
        SparseMatrix transposed(cols, rows);
        transposed.nonZeroCount = nonZeroCount;
        
        for (int j = 0; j < cols; j++) {
            for (const auto& elem : compactForm) {
                if (elem.col == j) {
                    Element transElem;
                    transElem.row = elem.col;
                    transElem.col = elem.row;
                    transElem.value = elem.value;
                    transposed.compactForm.push_back(transElem);
                }
            }
        }
        
        return transposed;
    }

    void demo() {
        // Create a sample sparse matrix
        int** sampleMatrix = new int*[4];
        for (int i = 0; i < 4; i++) {
            sampleMatrix[i] = new int[5]();
        }
        
        // Set some non-zero values
        sampleMatrix[0][1] = 5;
        sampleMatrix[1][0] = 8;
        sampleMatrix[1][3] = 3;
        sampleMatrix[2][2] = 7;
        sampleMatrix[3][1] = 9;
        sampleMatrix[3][4] = 2;
        
        from2DArray(sampleMatrix);
        
        cout << "Original Sparse Matrix:\n";
        displayMatrix();
        cout << "\n";
        displayCompact();
        
        cout << "\nTransposed Matrix:\n";
        SparseMatrix transposed = simpleTranspose();
        transposed.displayMatrix();
        cout << "\n";
        transposed.displayCompact();
        
        // Cleanup
        for (int i = 0; i < 4; i++) {
            delete[] sampleMatrix[i];
        }
        delete[] sampleMatrix;
    }
};

int main() {
    SparseMatrix sm(4, 5);
    sm.demo();
    return 0;
}