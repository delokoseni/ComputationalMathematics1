#include <iostream>
#include <fstream>
#include <Windows.h>

const int MatrixDimension = 4; //Размерность матрицы

void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension + 1]);
void GetX(float Matrix[MatrixDimension][MatrixDimension + 1], float X[MatrixDimension]);
void GaussMethod(float Matrix[MatrixDimension][MatrixDimension + 1]);
void GetResidualVector(float Matrix[MatrixDimension][MatrixDimension + 1], float X[MatrixDimension], float r[MatrixDimension]);
float GetDetermTriangMatrix(float Matrix[MatrixDimension][MatrixDimension + 1]);

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int i, j;
    float Matrix[MatrixDimension][MatrixDimension + 1], X[MatrixDimension], r[MatrixDimension];
    string FileName;
    /*cout << "Введите имя файла: ";
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
    GaussMethod(Matrix);
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
        for (i = 0; i < MatrixDimension; i++) {
            cout << "X[" << i << "]: " << X[i] << endl;
        }
        GetResidualVector(Matrix, X, r);
        cout << "Вектор невязки: " << endl;
        for (i = 0; i < MatrixDimension; i++) {
            cout << "r[" << i << "]: " << r[i] << endl;
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
    X[MatrixDimension - 1] = Matrix[MatrixDimension - 1][MatrixDimension] / Matrix[MatrixDimension - 1][MatrixDimension - 1];
    for (int i = MatrixDimension - 2; i >= 0; i--)
    {
        float sum = 0;
        for (int j = i + 1; j < MatrixDimension; j++)
        {
            sum += Matrix[i][j] * X[j];
        }
        X[i] = (Matrix[i][MatrixDimension] - sum) / Matrix[i][i];
    }
}

void GaussMethod(float Matrix[MatrixDimension][MatrixDimension + 1])
{
    for (int i = 1; i < MatrixDimension; i++) {
        int n = 0;
        while (Matrix[i][n] == 0) {
            n++;
        }
        for (int j = i; j < MatrixDimension; j++)
        {
            float buffer = Matrix[j][n];
            for (int k = 0; k < MatrixDimension + 1; k++)
            {
                Matrix[j][k] -= Matrix[i - 1][k] * buffer / Matrix[i - 1][i - 1];
            }
        }
    }
}

void GetResidualVector(float Matrix[MatrixDimension][MatrixDimension + 1], float X[MatrixDimension], float r[MatrixDimension])
{
    for (int i = 0; i < MatrixDimension; i++)
    {
        float sum = 0;
        for (int j = 0; j < MatrixDimension; j++)
        {
            sum += Matrix[i][j] * X[j];
        }
        r[i] = Matrix[i][MatrixDimension] - sum;
    }
}