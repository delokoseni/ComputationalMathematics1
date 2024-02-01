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
    for (i = 1; i < MatrixDimension; i++) {
        n = 0;
        while (Matrix[i][n] == 0) {
            n++;
        }
        for (j = i; j < MatrixDimension; j++)
        {
            buffer = Matrix[j][n];
            for (int k = 0; k < MatrixDimension + 1; k++)
            {
                Matrix[j][k] -= Matrix[i-1][k] * buffer / Matrix[i-1][i-1];
            }
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
        GetX(Matrix, X);
        for (i = 0; i < 4; i++) {
            cout << "X[" << i << "]: " << X[i] << endl;
        }
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
    int i, j;
    X[MatrixDimension - 1] = Matrix[MatrixDimension - 1][MatrixDimension] / Matrix[MatrixDimension - 1][MatrixDimension - 1];
    for (i = MatrixDimension - 2; i >= 0; i--)
    {
        float sum = 0;
        for (j = i + 1; j < MatrixDimension; j++)
        {
            sum += Matrix[i][j] * X[j];
        }
        X[i] = (Matrix[i][MatrixDimension] - sum) / Matrix[i][i];
    }
}