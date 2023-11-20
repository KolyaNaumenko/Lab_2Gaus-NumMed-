// Lab_2Gaus.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void printMatrix(vector<vector<double>>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<double>> generateHilbertMatrix(int n) {
    vector<vector<double>> A(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = 1.0 / (i + j + 1);
        }
    }
    return A;
}

// Function to generate a random matrix with integer values
void generateRandomMatrix(vector<vector<double>>& A, int n, int minValue, int maxValue) {
    A = vector<vector<double>>(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = static_cast<double>(rand() % (maxValue - minValue + 1) + minValue);
        }
    }
}


void computeVectorB(const vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();
    b = vector<double>(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i] += A[i][j];
        }
    }
}


// Function to perform forward substitution for solving Ly = b
void forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b, vector<double>& y) {
    int n = L.size();
    y = vector<double>(n, 0.0);

    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }
}

// Function to perform backward substitution for solving Ux = y
void backwardSubstitution(const vector<vector<double>>& U, const vector<double>& y, vector<double>& x) {
    int n = U.size();
    x = vector<double>(n, 0.0);

    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = n - 1; j > i; j--) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

void luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U) {
    int n = A.size();
    L = vector<vector<double>>(n, vector<double>(n, 0.0));
    U = vector<vector<double>>(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;

        for (int j = i; j < n; j++) {
            U[i][j] = A[i][j];
            for (int k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }

        for (int j = i + 1; j < n; j++) {
            L[j][i] = A[j][i];
            for (int k = 0; k < i; k++) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            L[j][i] /= U[i][i];
        }
    }
}

int main() {
    int n;
    cout << "Enter the matrix 322 dimension: ";
    cin >> n;

    vector<vector<double>> A, L, U;
    vector<double> b;

    cout << "Choose the type of matrix: 1 - Random, 2 - Hilbert: ";
    int choice;
    cin >> choice;

    srand(time(0));

    if (choice == 1) {
        int minValue, maxValue;
        cout << "Enter the minimum and maximum values for random matrix elements: ";
        cin >> minValue >> maxValue;
        generateRandomMatrix(A, n, minValue, maxValue);
    }
    else if (choice == 2) {
        A = generateHilbertMatrix(n);
    }
    else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    computeVectorB(A, b);

    luDecomposition(A, L, U);




    cout << "Vector b:" << endl;
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;

    // Perform forward substitution to solve Ly = b
    vector<double> y;
    forwardSubstitution(L, b, y);

    // Perform backward substitution to solve Ux = y
    vector<double> x;
    backwardSubstitution(U, y, x);

    cout << "Solution x:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
