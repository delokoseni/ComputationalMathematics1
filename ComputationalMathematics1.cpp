#include <iostream>
#include <fstream>
#include <Windows.h>

const int MatrixDimension = 4;
void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension]);

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int i, j;
    float MatrixA[MatrixDimension][MatrixDimension], MatrixB[MatrixDimension];
    string FileName;
    /*cout << "Input name of file for matrix A: ";
    cin >> FileName;
    ifstream InputFileA(FileName);*/
    ifstream InputFileA("A.txt");
    if (InputFileA.is_open())
    {
        for (i = 0; i < MatrixDimension; i++)
            for (j = 0; j < MatrixDimension; j++)
                InputFileA >> MatrixA[i][j];
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
        buffer = MatrixA[j][n];
        for (int k = 0; k < MatrixDimension; k++)
        {
            Matrix[j][k] -= Matrix[0][k] * buffer / Matrix[0][0];
        }
    }
    cout << endl << "Матрица: " << endl;
    MatrixOutput(Matrix);


    for (j = 2; j < MatrixDimension; j++)
    {
        buffer = MatrixA[j][1];
        //cout << endl << "buffer[" << j << "][" << n << "]: " << buffer << endl;
        for (int k = 0; k < MatrixDimension; k++)
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
        buffer = MatrixA[j][n];
        cout << endl << "buffer: " << buffer << endl;
        for (int k = 0; k < MatrixDimension; k++)
        {
            MatrixA[j][k] -= MatrixA[2][k] * buffer / MatrixA[2][2];
        }
    }
    return 0;
}

void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension]) 
{
    for (int i = 0; i < MatrixDimension; i++) {
        for (int j = 0; j < MatrixDimension; j++)
            cout << Matrix[i][j] << "\t";
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