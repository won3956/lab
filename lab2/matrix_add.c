#include <iostream>
using namespace std;

int** allocateMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            cout << "행렬의 " << i + 1 << "행 " << j + 1 << "열 원소 입력: ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}
int** addMatrices(int** matrix1, int** matrix2, int rows, int cols) {
    int** result = new int*[rows];
    for (int i = 0; i < rows; i++) {
        result[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];  // 오타 수정: result[i][j]) -> result[i][j]
        }
    }
    return result;
}
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
int main() {
    int rows, cols;
    cout << "행렬의 행 수를 입력하세요: ";
    cin >> rows;
    cout << "행렬의 열 수를 입력하세요: ";
    cin >> cols;

    int** matrix1 = allocateMatrix(rows, cols);

    int** matrix2 = allocateMatrix(rows, cols);

    int** resultMatrix = addMatrices(matrix1, matrix2, rows, cols);

    cout << "덧셈 결과:" << endl;
    printMatrix(resultMatrix, rows, cols);

    freeMatrix(matrix1, rows);
    freeMatrix(matrix2, rows);
    freeMatrix(resultMatrix, rows);

    return 0;
}
