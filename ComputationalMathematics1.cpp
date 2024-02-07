#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>

const int MatrixDimension = 4; //Размерность матрицы
int Sign = 1; //Знак для определителя

bool MatrixInput(double Matrix[MatrixDimension][MatrixDimension + 1], std::string FileName); //Ввод матрицы
void MatrixOutput(double Matrix[MatrixDimension][MatrixDimension + 1], std::ostream& Stream); //Вывод матрицы
void GetX(double Matrix[MatrixDimension][MatrixDimension + 1], double X[MatrixDimension]); //Найти столбец свободных членов
void GaussMethod(double Matrix[MatrixDimension][MatrixDimension + 1]); //Метод Гаусса без выбора
void GaussMethodWithChoice(double Matrix[MatrixDimension][MatrixDimension + 1]); //Метод Гаусса с выбором
//Получить вектор невязки
void GetResidualVector(double Matrix[MatrixDimension][MatrixDimension + 1], double X[MatrixDimension], double r[MatrixDimension]);
void RowRearrangement(double Matrix[MatrixDimension][MatrixDimension + 1], int FirstRow, int SecondRow); //Перестановка строк
double GetDetermTriangMatrix(double Matrix[MatrixDimension][MatrixDimension + 1]); //Получить определитель треугольной матрицы

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int i, j, n = 0;
    double Matrix[MatrixDimension][MatrixDimension + 1]; //Первоначальная матрица
    double X[MatrixDimension]; //Вектор Х
    double r[MatrixDimension]; //Вектор невязки
    double InverseMatrix[MatrixDimension][MatrixDimension]; //Обратная матрица
    string FileName[3] = { "A0.txt", "A1.txt", "A2.txt" };
    ofstream OutputFile("output.txt");
    while (n < 3) {
        if (!MatrixInput(Matrix, FileName[n])) //Ввод, вычисление и вывод матриц треугольных матриц
        {
            OutputFile << endl << "Матрица: " << endl;
            MatrixOutput(Matrix, OutputFile);
            GaussMethodWithChoice(Matrix);
            OutputFile << endl << "Треугольная матрица: " << endl;
            MatrixOutput(Matrix, OutputFile);
            OutputFile << endl << "Определитель матрицы: ";
            OutputFile << GetDetermTriangMatrix(Matrix) << endl;
            if (GetDetermTriangMatrix(Matrix) == 0) 
            {
                OutputFile << endl << "Матрица вырождена." << endl;
            }
            else
            {
                OutputFile << endl << "Матрица не вырождена." << endl;
                GetX(Matrix, X);
                for (i = 0; i < MatrixDimension; i++)
                {
                    OutputFile << "X[" << i << "]: " << X[i] << endl;
                }
                GetResidualVector(Matrix, X, r);
                OutputFile << endl << "Вектор невязки: " << endl;
                for (i = 0; i < MatrixDimension; i++) {
                    OutputFile << "r[" << i << "]: " << r[i] << endl;
                }
            }
        }
        else
        {
            cout << endl << "Ошибка! Не удалось открыть файл!" << endl;
        }
        n++;
    }
    if (!MatrixInput(Matrix, FileName[0])) { //Вычисление обратной матрицы
        if (GetDetermTriangMatrix(Matrix) != 0)
        {
            for (i = 0; i < MatrixDimension; i++) {
                MatrixInput(Matrix, FileName[0]);
                for (j = 0; j < MatrixDimension; j++)
                    Matrix[j][MatrixDimension] = 0;
                Matrix[i][MatrixDimension] = 1;
                GaussMethodWithChoice(Matrix);
                GetX(Matrix, X);
                for (j = 0; j < MatrixDimension; j++) {
                    InverseMatrix[i][j] = X[j];
                }
            }
        }
        OutputFile << endl << "Обратная матрица: " << endl;
        for (i = 0; i < MatrixDimension; i++) {
            for (j = 0; j < MatrixDimension; j++) {
                OutputFile << InverseMatrix[i][j] << "\t\t";
            }
            OutputFile << endl;
        }
    }
    return 0;
}
//Вывод матрицы
void MatrixOutput(double Matrix[MatrixDimension][MatrixDimension + 1], std::ostream& Stream)
{
    for (int i = 0; i < MatrixDimension; i++) {
        for (int j = 0; j < MatrixDimension + 1; j++)
            Stream << Matrix[i][j] << "\t\t";
        Stream << endl;
    }
}
//Вычисление определителя треугольной матрицы
double GetDetermTriangMatrix(double Matrix[MatrixDimension][MatrixDimension + 1])
{
    double determinant = 1;
    for (int i = 0; i < MatrixDimension; i++)
        determinant *= Matrix[i][i];
    determinant *= Sign;
    Sign = 1;
    return determinant;
}
//Вычисление столбца свободных членов
void GetX(double Matrix[MatrixDimension][MatrixDimension + 1], double X[MatrixDimension])
{
    X[MatrixDimension - 1] = Matrix[MatrixDimension - 1][MatrixDimension] / Matrix[MatrixDimension - 1][MatrixDimension - 1];
    for (int i = MatrixDimension - 2; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < MatrixDimension; j++)
        {
            sum += Matrix[i][j] * X[j];
        }
        X[i] = (Matrix[i][MatrixDimension] - sum) / Matrix[i][i];
    }
}
//Метод Гаусса без выбора
void GaussMethod(double Matrix[MatrixDimension][MatrixDimension + 1])
{
    for (int i = 1; i < MatrixDimension; i++) {
        int n = 0;
        while (Matrix[i][n] == 0) {
            n++;
        }
        for (int j = i; j < MatrixDimension; j++)
        {
            double buffer = Matrix[j][n];
            for (int k = 0; k < MatrixDimension + 1; k++)
            {
                if (Matrix[i - 1][i - 1] != 0)
                    Matrix[j][k] -= Matrix[i - 1][k] * buffer / Matrix[i - 1][i - 1];
                else
                    Matrix[j][k] = 0;
            }
        }
    }
}
//Метод Гаусса с выбором
void GaussMethodWithChoice(double Matrix[MatrixDimension][MatrixDimension + 1])
{
    for (int i = 0; i < MatrixDimension; i++) {
        for (int j = i; j < MatrixDimension; j++) 
        {
            if (fabs(Matrix[i][i]) < fabs(Matrix[j][i])) {
                RowRearrangement(Matrix, i, j);
                Sign *= -1;
            }
        }
        int n = 0;
        while (Matrix[i][n] == 0) {
            n++;
        }
        if (i > 0) {
            for (int j = i; j < MatrixDimension; j++)
            {
                double buffer = Matrix[j][n];
                for (int k = 0; k < MatrixDimension + 1; k++)
                {
                    if (Matrix[i - 1][i - 1] != 0)
                        Matrix[j][k] -= Matrix[i - 1][k] * buffer / Matrix[i - 1][i - 1];
                    else
                        Matrix[j][k] = 0;
                }
            }
        }
    }
}
//Вычисление вектора невязки
void GetResidualVector(double Matrix[MatrixDimension][MatrixDimension + 1], double X[MatrixDimension], double r[MatrixDimension])
{
    for (int i = 0; i < MatrixDimension; i++)
    {
        double sum = 0;
        for (int j = 0; j < MatrixDimension; j++)
        {
            sum += Matrix[i][j] * X[j];
        }
        r[i] = Matrix[i][MatrixDimension] - sum;
    }
}
//Ввод матрицы
bool MatrixInput(double Matrix[MatrixDimension][MatrixDimension + 1], string FileName)
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
//Перестановка строк матрицы
void RowRearrangement(double Matrix[MatrixDimension][MatrixDimension + 1], int FirstRow, int SecondRow) {
    double buffer;
    for (int i = 0; i < MatrixDimension+1; i++) {
        buffer = Matrix[FirstRow][i];
        Matrix[FirstRow][i] = Matrix[SecondRow][i];
        Matrix[SecondRow][i] = buffer;
    }
}