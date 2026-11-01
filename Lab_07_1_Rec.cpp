// Lab_07_1_Rec.cpp
// Варіант 29
// Лабораторна робота № 7.1
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Рекурсивний спосіб.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Рекурсивне формування елементів одного рядка
void CreateRow(int** q, const int rowNo, const int colCount, const int Low, const int High, int colNo) {
    q[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(q, rowNo, colCount, Low, High, colNo + 1);
}

// Рекурсивне формування всіх рядків матриці
void CreateRows(int** q, const int rowCount, const int colCount, const int Low, const int High, int rowNo) {
    CreateRow(q, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(q, rowCount, colCount, Low, High, rowNo + 1);
}

// Рекурсивне виведення елементів одного рядка
void PrintRow(int** q, const int rowNo, const int colCount, int colNo) {
    cout << setw(5) << q[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(q, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

// Рекурсивне виведення всіх рядків матриці
void PrintRows(int** q, const int rowCount, const int colCount, int rowNo) {
    PrintRow(q, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(q, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

// Рекурсивний обмін елементів двох рядків (допоміжна функція)
void ChangeRow(int** q, const int row1, const int row2, const int colCount, int colNo) {
    int tmp = q[row1][colNo];
    q[row1][colNo] = q[row2][colNo];
    q[row2][colNo] = tmp;
    if (colNo < colCount - 1)
        ChangeRow(q, row1, row2, colCount, colNo + 1);
}

// Внутрішній цикл рекурсивного сортування (прохід по сусідніх рядках)
void SortSort(int** q, const int rowCount, const int colCount, int i1) {
    if ((q[i1][0] < q[i1 + 1][0]) ||
        (q[i1][0] == q[i1 + 1][0] && q[i1][1] < q[i1 + 1][1]) ||
        (q[i1][0] == q[i1 + 1][0] && q[i1][1] == q[i1 + 1][1] && q[i1][3] > q[i1 + 1][3])) {
        ChangeRow(q, i1, i1 + 1, colCount, 0);
    }
    if (i1 < rowCount - 1)
        SortSort(q, rowCount, colCount, i1 + 1);
}

// Зовнішній цикл рекурсивного сортування
void SortRows(int** q, const int rowCount, const int colCount, int i0) {
    SortSort(q, rowCount - i0 - 1, colCount, 0);
    if (i0 < rowCount - 2)
        SortRows(q, rowCount, colCount, i0 + 1);
}

// Рекурсивна обробка елементів одного рядка (обчислення та обнулення)
void CalcRow(int** q, const int rowNo, const int colCount, int colNo, int& S, int& k) {
    if (q[rowNo][colNo] > 0 && !(rowNo % 2 == 0 && colNo % 2 == 0)) {
        S += q[rowNo][colNo];
        k++;
        q[rowNo][colNo] = 0;
    }
    if (colNo < colCount - 1)
        CalcRow(q, rowNo, colCount, colNo + 1, S, k);
}

// Рекурсивна обробка всіх рядків матриці
void CalcRows(int** q, const int rowCount, const int colCount, int rowNo, int& S, int& k) {
    CalcRow(q, rowNo, colCount, 0, S, k);
    if (rowNo < rowCount - 1)
        CalcRows(q, rowCount, colCount, rowNo + 1, S, k);
}

int main() {
    srand((unsigned)time(0));

    const int Low = -8;
    const int High = 42;
    const int rowCount = 8;
    const int colCount = 7;

    // Створення динамічної матриці
    int** q = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        q[i] = new int[colCount];

    // 1. Формування та виведення початкової матриці
    CreateRows(q, rowCount, colCount, Low, High, 0);
    cout << "Initial matrix:" << endl;
    PrintRows(q, rowCount, colCount, 0);

    // 2. Сортування та виведення
    SortRows(q, rowCount, colCount, 0);
    cout << "Sorted matrix:" << endl;
    PrintRows(q, rowCount, colCount, 0);

    // 3. Обчислення та модифікація (заміна 0)
    int S = 0;
    int k = 0;
    CalcRows(q, rowCount, colCount, 0, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix:" << endl;
    PrintRows(q, rowCount, colCount, 0);

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] q[i];
    delete[] q;

    return 0;
}