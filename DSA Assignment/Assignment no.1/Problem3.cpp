#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

class MatrixMultiplier {
private:
    vector<vector<int>> matrixA, matrixB, result;
    int size;

public:
    MatrixMultiplier(int n) : size(n) {
        matrixA.resize(n, vector<int>(n));
        matrixB.resize(n, vector<int>(n));
        result.resize(n, vector<int>(n, 0));
        initializeMatrices();
    }

    void initializeMatrices() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 10);
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrixA[i][j] = dis(gen);
                matrixB[i][j] = dis(gen);
            }
        }
    }

    // Row-major order (cache-friendly)
    long long multiplyRowMajor() {
        auto start = high_resolution_clock::now();
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count();
    }

    // Column-major order (cache-unfriendly)
    long long multiplyColumnMajor() {
        auto start = high_resolution_clock::now();
        
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                result[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count();
    }

    void displayMatrix(const vector<vector<int>>& mat, const string& name) {
        if (size > 6) {
            cout << name << " (showing 6x6 portion):\n";
            int displaySize = min(6, size);
            for (int i = 0; i < displaySize; i++) {
                for (int j = 0; j < displaySize; j++) {
                    cout << mat[i][j] << "\t";
                }
                cout << endl;
            }
        } else {
            cout << name << ":\n";
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    cout << mat[i][j] << "\t";
                }
                cout << endl;
            }
        }
        cout << endl;
    }

    void performanceAnalysis() {
        cout << "Matrix Multiplication Performance Analysis\n";
        cout << "Matrix Size: " << size << "x" << size << "\n\n";
        
        // Row-major multiplication
        long long timeRowMajor = multiplyRowMajor();
        cout << "Row-major order time: " << timeRowMajor << " microseconds\n";
        
        // Column-major multiplication
        long long timeColumnMajor = multiplyColumnMajor();
        cout << "Column-major order time: " << timeColumnMajor << " microseconds\n";
        
        cout << "\nPerformance Ratio (Column/Row): " 
             << static_cast<double>(timeColumnMajor) / timeRowMajor << endl;
        
        if (size <= 6) {
            displayMatrix(matrixA, "Matrix A");
            displayMatrix(matrixB, "Matrix B");
            displayMatrix(result, "Result Matrix");
        }
    }
};

int main() {
    int size;
    cout << "Enter matrix size: ";
    cin >> size;
    
    MatrixMultiplier mm(size);
    mm.performanceAnalysis();
    return 0;
}