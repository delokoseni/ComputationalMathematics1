#include <iostream>
#include <fstream>
#include <Windows.h>

const int MatrixDimension = 4; //Размерность матрицы

bool MatrixInput(float Matrix[MatrixDimension][MatrixDimension + 1], std::string FileName);
void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension + 1], std::ostream& Stream);
void GetX(float Matrix[MatrixDimension][MatrixDimension + 1], float X[MatrixDimension]);
void GaussMethod(float Matrix[MatrixDimension][MatrixDimension + 1]);
void GetResidualVector(float Matrix[MatrixDimension][MatrixDimension + 1], float X[MatrixDimension], float r[MatrixDimension]);
float GetDetermTriangMatrix(float Matrix[MatrixDimension][MatrixDimension + 1]);

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int i, j, n = 0;
    float Matrix[MatrixDimension][MatrixDimension + 1]; //Первоначальная матрица
    float X[MatrixDimension]; //Вектор Х
    float r[MatrixDimension]; //Вектор невязки
    float InverseMatrix[MatrixDimension][MatrixDimension]; //Обратная матрица
    string FileName[3] = { "A0.txt", "A1.txt", "A2.txt" };
    ofstream OutputFile("output.txt");
    while (n < 3) {
        if (!MatrixInput(Matrix, FileName[n]))
        {
            cout << endl << "Матрица: " << endl;
            OutputFile << endl << "Матрица: " << endl;
            MatrixOutput(Matrix, OutputFile);
            MatrixOutput(Matrix, std::cout);
            GaussMethod(Matrix);
            cout << endl << "Треугольная матрица: " << endl;
            OutputFile << endl << "Треугольная матрица: " << endl;
            MatrixOutput(Matrix, OutputFile);
            MatrixOutput(Matrix, std::cout);
            cout << endl << "Определитель матрицы: ";
            OutputFile << endl << "Определитель матрицы: ";
            cout << GetDetermTriangMatrix(Matrix) << endl;
            OutputFile << GetDetermTriangMatrix(Matrix) << endl;
            if (GetDetermTriangMatrix(Matrix) == 0) 
            {
                cout << endl << "Матрица вырождена." << endl;
                OutputFile << endl << "Матрица вырождена." << endl;
            }
            else
            {
                cout << endl << "Матрица не вырождена." << endl;
                OutputFile << endl << "Матрица не вырождена." << endl;
                GetX(Matrix, X);
                for (i = 0; i < MatrixDimension; i++)
                {
                    cout << "X[" << i << "]: " << X[i] << endl;
                    OutputFile << "X[" << i << "]: " << X[i] << endl;
                }
                GetResidualVector(Matrix, X, r);
                cout << endl << "Вектор невязки: " << endl;
                OutputFile << endl << "Вектор невязки: " << endl;
                for (i = 0; i < MatrixDimension; i++) {
                    cout << "r[" << i << "]: " << r[i] << endl;
                    OutputFile << "r[" << i << "]: " << r[i] << endl;
                }
            }
        }
        else
        {
            cout << endl << "Ошибка! Не удалось открыть файл!" << endl;
            OutputFile << endl << "Ошибка! Не удалось открыть файл!" << endl;
        }
        n++;
    }
    if (!MatrixInput(Matrix, FileName[0])) {
        if (GetDetermTriangMatrix(Matrix) != 0)
        {
            for (i = 0; i < MatrixDimension; i++) {
                MatrixInput(Matrix, FileName[0]);
                for (j = 0; j < MatrixDimension; j++)
                    Matrix[j][MatrixDimension] = 0;
                Matrix[i][MatrixDimension] = 1;
                GaussMethod(Matrix);
                GetX(Matrix, X);
                for (j = 0; j < MatrixDimension; j++) {
                    InverseMatrix[i][j] = X[j];
                }
            }
        }
        cout << endl << "Обратная матрица: " << endl;
        OutputFile << endl << "Обратная матрица: " << endl;
        for (i = 0; i < MatrixDimension; i++) {
            for (j = 0; j < MatrixDimension; j++) {
                cout << InverseMatrix[i][j] << "\t\t";
                OutputFile << InverseMatrix[i][j] << "\t\t";
            }
            cout << endl;
            OutputFile << endl;
        }
    }
    return 0;
}

void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension + 1], std::ostream& Stream)
{
    for (int i = 0; i < MatrixDimension; i++) {
        for (int j = 0; j < MatrixDimension + 1; j++)
            Stream << Matrix[i][j] << "\t\t";
        Stream << endl;
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

bool MatrixInput(float Matrix[MatrixDimension][MatrixDimension + 1], string FileName)
{
    ifstream InputFileA(FileName);
    if (InputFileA.is_open())
    {
        for (int i = 0; i < MatrixDimension; i++)
            for (int j = 0; j < MatrixDimension + 1; j++)
                InputFileA >> Matrix[i][j];
        InputFileA.close();
        return 0;
    }
    else
        return 1;
}