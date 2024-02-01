#include <iostream>
#include <fstream>
#include <Windows.h>

const int MatrixDimension = 4;
void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension + 1]);
float GetDetermTriangMatrix(float Matrix[MatrixDimension][MatrixDimension + 1]);
void GetX(float Matrix[MatrixDimension][MatrixDimension + 1], float X[MatrixDimension]);

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int i, j;
    float Matrix[MatrixDimension][MatrixDimension + 1], X[MatrixDimension];
    string FileName;
    /*cout << "Input name of file for matrix A: ";
    cin >> FileName;
    ifstream InputFileA(FileName);*/
    ifstream InputFileA("A.txt");
    if (InputFileA.is_open())
    {
        for (i = 0; i < MatrixDimension; i++)
            for (j = 0; j < MatrixDimension + 1; j++)
                InputFileA >> Matrix[i][j];
        InputFileA.close();
    }
    else
        cout << "Ошибка! Не удалось открыть файл!";

    cout << endl << "Матрица: " << endl;
    MatrixOutput(Matrix);

    float buffer;

    int n = 0;

    for (j = 1; j < MatrixDimension; j++)
    {
        n = 0;
        while (Matrix[j][n] == 0) {
            n++;
        }
        buffer = Matrix[j][n];
        for (int k = 0; k < MatrixDimension + 1; k++)
        {
            Matrix[j][k] -= Matrix[0][k] * buffer / Matrix[0][0];
        }
    }
    cout << endl << "Матрица: " << endl;
    MatrixOutput(Matrix);


    for (j = 2; j < MatrixDimension; j++)
    {
        buffer = Matrix[j][1];
        for (int k = 0; k < MatrixDimension + 1; k++)
        {
            Matrix[j][k] -= Matrix[1][k] * buffer / Matrix[1][1];
        }
    }
    cout << endl << "Матрица: " << endl;
    MatrixOutput(Matrix);



    for (j = 3; j < 4; j++)
    {
        n = 0;
        while (Matrix[j][n] == 0) {
            n++;
        }
        buffer = Matrix[j][n];
        for (int k = 0; k < MatrixDimension + 1; k++)
        {
            Matrix[j][k] -= Matrix[2][k] * buffer / Matrix[2][2];
        }
    }
    cout << endl << "Матрица: " << endl;
    MatrixOutput(Matrix);
    cout << "Определитель матрицы: ";
    cout << GetDetermTriangMatrix(Matrix) << endl;
    if (GetDetermTriangMatrix(Matrix) == 0)
        cout << "Матрица вырождена." << endl;
    else
    {
        cout << "Матрица не вырождена." << endl;
        float x1, x2, x3, x4;
        x4 = Matrix[MatrixDimension - 1][MatrixDimension] / Matrix[MatrixDimension - 1][MatrixDimension - 1];
        x3 = (Matrix[MatrixDimension - 2][MatrixDimension] - Matrix[MatrixDimension - 2][MatrixDimension - 1] * x4) /
            Matrix[MatrixDimension - 2][MatrixDimension - 2];
        x2 = (Matrix[MatrixDimension - 3][MatrixDimension] - Matrix[MatrixDimension - 3][MatrixDimension - 2] * x3
            - Matrix[MatrixDimension - 3][MatrixDimension - 1] * x4) / Matrix[MatrixDimension - 3][MatrixDimension - 3];
        x1 = (Matrix[MatrixDimension - 4][MatrixDimension] - Matrix[MatrixDimension - 4][MatrixDimension - 3] * x2
            - Matrix[MatrixDimension - 4][MatrixDimension - 2] * x3 - Matrix[MatrixDimension - 4][MatrixDimension - 1] * x4) /
            Matrix[MatrixDimension - 4][MatrixDimension - 4];
        cout << "X1 = " << x1 << endl;
        cout << "X2 = " << x2 << endl;
        cout << "X3 = " << x3 << endl;
        cout << "X4 = " << x4 << endl;
    }
    GetX(Matrix, X);
    for (i = 0; i < 4; i++) {
        cout << X[i] << endl;
    }
    return 0;
}

void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension + 1])
{
    for (int i = 0; i < MatrixDimension; i++) {
        for (int j = 0; j < MatrixDimension + 1; j++)
            cout << Matrix[i][j] << "\t\t";
        cout << endl;
    }
}

float GetDetermTriangMatrix(float Matrix[MatrixDimension][MatrixDimension + 1])
{
    float determinant = 1;
    for (int i = 0; i < MatrixDimension; i++)
        determinant *= Matrix[i][i];
    return determinant;
}

void GetX(float Matrix[MatrixDimension][MatrixDimension + 1], float X[MatrixDimension])
{
    int m, i;
    X[MatrixDimension - 1] = Matrix[MatrixDimension - 1][MatrixDimension] / Matrix[MatrixDimension - 1][MatrixDimension - 1];
    for (m = MatrixDimension - 2; m >= 0; m--)
    {
        float sum = 0;
        for (i = m + 1; i < MatrixDimension; i++)
        {
            sum += Matrix[m][i] * X[i];
        }
        X[m] = (Matrix[m][MatrixDimension] - sum) / Matrix[m][m];
    }
}