#include <iostream>
#include <fstream>

const int MatrixDimension = 4;
void MatrixOutput(double Matrix[MatrixDimension][MatrixDimension]);

using namespace std;

int main()
{
    int i, j;
    double MatrixA[MatrixDimension][MatrixDimension], MatrixB[MatrixDimension];
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
        cout << "Error! File for matrix A isn`t open!";
    /*cout << "Input name of file for matrix B: ";
    cin >> FileName;
    ifstream InputFileB(FileName);*/
    ifstream InputFileB("B.txt");
    if (InputFileB.is_open())
    {
        for (i = 0; i < MatrixDimension; i++)
            InputFileB >> MatrixB[i];
        InputFileB.close();
    }
    else
        cout << "Error! File for matrix B isn`t open!";
    cout << endl << "Matrix A: " << endl;
    MatrixOutput(MatrixA);
    cout << endl << "Matrix B: " << endl;
    for (i = 0; i < MatrixDimension; i++)
            cout << MatrixB[i] << endl;
    int buffer;
    for (i = 0; i < 1; i++) {
        for (j = 1; j < MatrixDimension; j++)
        {
            buffer = MatrixA[j][0];
            for (int k = 0; k < MatrixDimension; k++)
            {
                MatrixA[j][k] -= MatrixA[i][k] * buffer / MatrixA[i][i];
            }
        }
    }
    cout << endl << "Matrix A: " << endl;
    MatrixOutput(MatrixA);
    return 0;
}

void MatrixOutput(double Matrix[MatrixDimension][MatrixDimension]) 
{
    for (int i = 0; i < MatrixDimension; i++) {
        for (int j = 0; j < MatrixDimension; j++)
            cout << Matrix[i][j] << "\t";
        cout << endl;
    }
}