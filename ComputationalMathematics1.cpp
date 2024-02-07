#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>

//const int MatrixDimension = 4; //Размерность матрицы
int Sign = 1; //Знак для определителя

bool MatrixInput(double **Matrix, int N, int M, std::string FileName); //Ввод матрицы
void MatrixOutput(double** Matrix, int N, int M, std::ostream& Stream); //Вывод матрицы
void GetX(double** Matrix, int N, int M, double *X); //Найти столбец свободных членов
void GaussMethodWithChoice(double** Matrix, int N, int M); //Метод Гаусса с выбором
void GetResidualVector(double** Matrix, int N, int M, double *X, double *r); //Получить вектор невязки
void RowRearrangement(double** Matrix, int N, int M, int FirstRow, int SecondRow); //Перестановка строк
double GetDetermTriangMatrix(double** Matrix, int N, int M); //Получить определитель треугольной матрицы

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string FileName = "A1.txt", FileForNM = "NM.txt";
    int i, j, n, m, k = 0;
    ifstream InputFileNM(FileForNM);
    if (InputFileNM.is_open())
    {
        InputFileNM >> n; //Количество строк в матрице
        InputFileNM >> m; //Количество столбцов в матрице
        InputFileNM.close();
    }
    else
        cout << "Ошибка! Не удалось открыть файл для чтения N и M." << endl;
    double **Matrix; //Первоначальная матрица
    Matrix = new double* [n];
    for (i = 0; i < n; i++)
        *(Matrix + i) = new double[m+1];
    double *X; //Вектор Х
    X = new double [n];
    double *r; //Вектор невязки
    r = new double[n];
    double **InverseMatrix; //Обратная матрица
    InverseMatrix = new double* [n];
    for (i = 0; i < n; i++)
        *(InverseMatrix + i) = new double[m + 1];
    ofstream OutputFile("output.txt");
    if (!MatrixInput(Matrix, n, m, FileName)) //Ввод, вычисление и вывод матриц треугольных матриц
    {
        OutputFile << endl << "Матрица: " << endl;
        MatrixOutput(Matrix, n, m, OutputFile);
        GaussMethodWithChoice(Matrix, n, m);
        OutputFile << endl << "Треугольная матрица: " << endl;
        MatrixOutput(Matrix, n, m, OutputFile);
        OutputFile << endl << "Определитель матрицы: ";
        OutputFile << GetDetermTriangMatrix(Matrix, n, m) << endl;
        if (GetDetermTriangMatrix(Matrix, n, m) == 0)
        {
            OutputFile << endl << "Матрица вырождена." << endl;
        }
        else
        {
            OutputFile << endl << "Матрица не вырождена." << endl;
            GetX(Matrix, n, m, X);
            for (i = 0; i < n; i++)
            {
                OutputFile << "X[" << i << "]: " << X[i] << endl;
            }
            GetResidualVector(Matrix, n, m, X, r);
            OutputFile << endl << "Вектор невязки: " << endl;
            for (i = 0; i < n; i++) {
                OutputFile << "r[" << i << "]: " << r[i] << endl;
            }
        }
    }
    else
    {
        cout << endl << "Ошибка! Не удалось открыть файл!" << endl;
    }
    if (!MatrixInput(Matrix, n, m, FileName)) { //Вычисление обратной матрицы
        if (GetDetermTriangMatrix(Matrix, n, m) != 0)
        {
            for (i = 0; i < n; i++) {
                MatrixInput(Matrix, n, m, FileName);
                for (j = 0; j < m; j++)
                    Matrix[j][m] = 0;
                Matrix[i][m] = 1;
                GaussMethodWithChoice(Matrix, n, m);
                GetX(Matrix, n, m, X);
                for (j = 0; j < m; j++) {
                    InverseMatrix[i][j] = X[j];
                }
            }
        }
        OutputFile << endl << "Обратная матрица: " << endl;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                OutputFile << InverseMatrix[i][j] << "\t\t";
            }
            OutputFile << endl;
        }
    }
    return 0;
}
//Вывод матрицы
void MatrixOutput(double** Matrix, int N, int M, std::ostream& Stream)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M + 1; j++)
            Stream << Matrix[i][j] << "\t\t";
        Stream << endl;
    }
}
//Вычисление определителя треугольной матрицы
double GetDetermTriangMatrix(double** Matrix, int N, int M)
{
    double determinant = 1;
    for (int i = 0; i < N; i++)
        determinant *= Matrix[i][i];
    determinant *= Sign;
    Sign = 1;
    return determinant;
}
//Вычисление столбца свободных членов
void GetX(double** Matrix, int N, int M, double* X)
{
    X[N - 1] = Matrix[N - 1][M] / Matrix[N - 1][M - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < M; j++)
        {
            sum += Matrix[i][j] * X[j];
        }
        X[i] = (Matrix[i][M] - sum) / Matrix[i][i];
    }
}
//Метод Гаусса с выбором
void GaussMethodWithChoice(double** Matrix, int N, int M)
{
    for (int i = 0; i < N; i++) {
        for (int j = i; j < M; j++) 
        {
            if (fabs(Matrix[i][i]) < fabs(Matrix[j][i])) {
                RowRearrangement(Matrix, N, M, i, j);
                Sign *= -1;
            }
        }
        int n = 0;
        while (Matrix[i][n] == 0) {
            n++;
        }
        if (i > 0) {
            for (int j = i; j < N; j++)
            {
                double buffer = Matrix[j][n];
                for (int k = 0; k < M + 1; k++)
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
void GetResidualVector(double** Matrix, int N, int M, double* X, double* r)
{
    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        for (int j = 0; j < M; j++)
        {
            sum += Matrix[i][j] * X[j];
        }
        r[i] = Matrix[i][M] - sum;
    }
}
//Ввод матрицы
bool MatrixInput(double** Matrix, int N, int M, std::string FileName)
{
    ifstream InputFileA(FileName);
    if (InputFileA.is_open())
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M + 1; j++)
                InputFileA >> Matrix[i][j];
        InputFileA.close();
        return 0;
    }
    else
        return 1;
}
//Перестановка строк матрицы
void RowRearrangement(double** Matrix, int N, int M, int FirstRow, int SecondRow) {
    double buffer;
    for (int i = 0; i < M+1; i++) {
        buffer = Matrix[FirstRow][i];
        Matrix[FirstRow][i] = Matrix[SecondRow][i];
        Matrix[SecondRow][i] = buffer;
    }
}