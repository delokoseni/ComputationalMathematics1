#include <iostream>
#include <fstream>

const int MatrixDimension = 4;
void MatrixOutput(float Matrix[MatrixDimension][MatrixDimension]);

using namespace std;

int main()
{
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
    float buffer;

    int n = 0;

    for (j = 1; j < MatrixDimension; j++)
    {
        n = 0;
        while (MatrixA[j][n] == 0) {
            n++;
        }
        buffer = MatrixA[j][n];
        for (int k = 0; k < MatrixDimension; k++)
        {
            MatrixA[j][k] -= MatrixA[0][k] * buffer / MatrixA[0][0];
        }
    }
    cout << endl << "Matrix A: " << endl;
    MatrixOutput(MatrixA);


    for (j = 2; j < MatrixDimension; j++)
    {
        buffer = MatrixA[j][1];
        //cout << endl << "buffer[" << j << "][" << n << "]: " << buffer << endl;
        for (int k = 0; k < MatrixDimension; k++)
        {
            cout << MatrixA[j][k] << " - " << MatrixA[1][k] << " * " << buffer << " / " << MatrixA[1][1] << " = " << " ";
            MatrixA[j][k] -= MatrixA[1][k] * buffer / MatrixA[1][1];
            cout << MatrixA[j][k] << endl;
        }
    }
    cout << endl << "Matrix A: " << endl;
    MatrixOutput(MatrixA);



    for (j = 3; j < 4; j++)
    {
        n = 0;
        while (MatrixA[j][n] == 0) {
            n++;
        }
        buffer = MatrixA[j][n];
        cout << endl << "buffer: " << buffer << endl;
        for (int k = 0; k < MatrixDimension; k++)
        {
            MatrixA[j][k] -= MatrixA[2][k] * buffer / MatrixA[2][2];
        }
    }
    cout << endl << "Matrix A: " << endl;
    MatrixOutput(MatrixA);
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