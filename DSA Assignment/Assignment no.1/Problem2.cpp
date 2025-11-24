#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class MagicSquare {
private:
    vector<vector<int>> square;
    int n;

public:
    MagicSquare(int size) : n(size) {
        square.resize(n, vector<int>(n, 0));
    }

    // Generate magic square for odd order
    void generateOddMagicSquare() {
        int i = n / 2;
        int j = n - 1;
        
        for (int num = 1; num <= n * n;) {
            if (i == -1 && j == n) {
                j = n - 2;
                i = 0;
            } else {
                if (j == n) j = 0;
                if (i < 0) i = n - 1;
            }
            
            if (square[i][j] != 0) {
                j -= 2;
                i++;
                continue;
            } else {
                square[i][j] = num++;
            }
            
            j++;
            i--;
        }
    }

    // Generate magic square for even order (single even)
    void generateSingleEvenMagicSquare() {
        // Initialize with numbers 1 to n²
        int num = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                square[i][j] = num++;
            }
        }
        
        // Swap elements to create magic square
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n / 2; j++) {
                if (i != n / 4) {
                    swap(square[i][j], square[n - 1 - i][n - 1 - j]);
                }
            }
        }
        
        for (int i = 0; i < n / 2; i++) {
            for (int j = n / 2; j < n - 1; j++) {
                swap(square[i][j], square[n - 1 - i][n - 1 - j]);
            }
        }
    }

    // Verify if it's a magic square
    bool verifyMagicSquare() {
        int magicSum = n * (n * n + 1) / 2;
        
        // Check rows and columns
        for (int i = 0; i < n; i++) {
            int rowSum = 0, colSum = 0;
            for (int j = 0; j < n; j++) {
                rowSum += square[i][j];
                colSum += square[j][i];
            }
            if (rowSum != magicSum || colSum != magicSum) {
                return false;
            }
        }
        
        // Check diagonals
        int diag1 = 0, diag2 = 0;
        for (int i = 0; i < n; i++) {
            diag1 += square[i][i];
            diag2 += square[i][n - 1 - i];
        }
        
        return (diag1 == magicSum && diag2 == magicSum);
    }

    void display() {
        cout << "Magic Square of order " << n << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(4) << square[i][j] << " ";
            }
            cout << endl;
        }
    }

    void demo() {
        if (n % 2 == 1) {
            generateOddMagicSquare();
        } else {
            generateSingleEvenMagicSquare();
        }
        
        display();
        
        if (verifyMagicSquare()) {
            cout << "✓ Verified: This is a valid magic square!\n";
        } else {
            cout << "✗ Not a valid magic square!\n";
        }
    }
};

int main() {
    int order;
    cout << "Enter the order of magic square: ";
    cin >> order;
    
    if (order < 3) {
        cout << "Order must be at least 3!\n";
        return 1;
    }
    
    MagicSquare ms(order);
    ms.demo();
    return 0;
}