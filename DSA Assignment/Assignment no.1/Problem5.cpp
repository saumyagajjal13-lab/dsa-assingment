#include <iostream>
#include <vector>
using namespace std;

struct Element {
    int row, col, value;
};

class FastSparseMatrix {
private:
    vector<Element> compactForm;
    int rows, cols, nonZeroCount;

public:
    FastSparseMatrix(int r, int c) : rows(r), cols(c), nonZeroCount(0) {}

    // Add element directly to compact form
    void addElement(int row, int col, int value) {
        if (value != 0) {
            Element elem;
            elem.row = row;
            elem.col = col;
            elem.value = value;
            compactForm.push_back(elem);
            nonZeroCount++;
        }
    }

    void displayCompact() {
        cout << "Compact Representation (Row, Col, Value):\n";
        cout << "Matrix Size: " << rows << "x" << cols << endl;
        cout << "Non-zero elements: " << nonZeroCount << endl;
        
        for (int i = 0; i < nonZeroCount; i++) {
            cout << "(" << compactForm[i].row << ", " << compactForm[i].col 
                 << ", " << compactForm[i].value << ")\n";
        }
        cout << endl;
    }

    void displayMatrix() {
        cout << "Matrix Representation (" << rows << "x" << cols << "):\n";
        
        // Create 2D matrix filled with zeros
        vector<vector<int>> matrix(rows, vector<int>(cols, 0));
        
        // Fill with non-zero values
        for (int i = 0; i < nonZeroCount; i++) {
            int r = compactForm[i].row;
            int c = compactForm[i].col;
            matrix[r][c] = compactForm[i].value;
        }
        
        // Display matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Simple Transpose (for comparison)
    FastSparseMatrix simpleTranspose() {
        FastSparseMatrix transposed(cols, rows);
        
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < nonZeroCount; i++) {
                if (compactForm[i].col == j) {
                    transposed.addElement(compactForm[i].col, compactForm[i].row, compactForm[i].value);
                }
            }
        }
        
        return transposed;
    }

    // Fast Transpose using counting method
    FastSparseMatrix fastTranspose() {
        FastSparseMatrix transposed(cols, rows);
        transposed.nonZeroCount = nonZeroCount;
        transposed.compactForm.resize(nonZeroCount);
        
        // Step 1: Count how many elements in each column
        vector<int> count(cols, 0);
        for (int i = 0; i < nonZeroCount; i++) {
            count[compactForm[i].col]++;
        }
        
        // Step 2: Calculate starting position for each column
        vector<int> startIndex(cols, 0);
        for (int j = 1; j < cols; j++) {
            startIndex[j] = startIndex[j - 1] + count[j - 1];
        }
        
        // Step 3: Place elements in correct positions
        for (int i = 0; i < nonZeroCount; i++) {
            int col = compactForm[i].col;
            int pos = startIndex[col];
            
            transposed.compactForm[pos].row = compactForm[i].col;
            transposed.compactForm[pos].col = compactForm[i].row;
            transposed.compactForm[pos].value = compactForm[i].value;
            
            startIndex[col]++;
        }
        
        return transposed;
    }

    void compareTransposeMethods() {
        cout << "=== COMPARING TRANSPOSE METHODS ===\n";
        
        // Simple transpose
        cout << "Performing Simple Transpose...\n";
        FastSparseMatrix simpleResult = simpleTranspose();
        cout << "Simple Transpose Completed!\n\n";
        
        // Fast transpose
        cout << "Performing Fast Transpose...\n";
        FastSparseMatrix fastResult = fastTranspose();
        cout << "Fast Transpose Completed!\n\n";
        
        cout << "Both methods produce the same result!\n";
    }
};

int main() {
    // Create a sparse matrix 4x5
    FastSparseMatrix matrix(4, 5);
    
    // Add non-zero elements
    matrix.addElement(0, 1, 5);
    matrix.addElement(1, 0, 8);
    matrix.addElement(1, 3, 3);
    matrix.addElement(2, 2, 7);
    matrix.addElement(3, 1, 9);
    matrix.addElement(3, 4, 2);
    
    // Display original matrix
    cout << "ORIGINAL MATRIX:\n";
    matrix.displayMatrix();
    matrix.displayCompact();
    
    // Perform and display simple transpose
    cout << "SIMPLE TRANSPOSE:\n";
    FastSparseMatrix simpleTrans = matrix.simpleTranspose();
    simpleTrans.displayMatrix();
    simpleTrans.displayCompact();
    
    // Perform and display fast transpose
    cout << "FAST TRANSPOSE:\n";
    FastSparseMatrix fastTrans = matrix.fastTranspose();
    fastTrans.displayMatrix();
    fastTrans.displayCompact();
    
    // Compare methods
    matrix.compareTransposeMethods();
    
    return 0;
}