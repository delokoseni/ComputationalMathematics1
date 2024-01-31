#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    double MatrixA[4][4], MatrixB[4];
    string FileName;
    cout << "Input name of file for matrix A: ";
    cin >> FileName;
    ifstream InputFileA(FileName);
    if (InputFileA.is_open())
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                InputFileA >> MatrixA[i][j];
        InputFileA.close();
    }
    else
        cout << "Error! File for matrix A isn`t open!";
    cout << "Input name of file for matrix B: ";
    cin >> FileName;
    ifstream InputFileB(FileName);
    if (InputFileB.is_open())
    {
        for (int i = 0; i < 4; i++)
            InputFileB >> MatrixB[i];
        InputFileB.close();
    }
    else
        cout << "Error! File for matrix B isn`t open!";
    cout << endl << "Matrix A: " << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            cout << MatrixA[i][j] << "\t";
        cout << endl;
    }
    cout << endl << "Matrix B: " << endl;
    for (int i = 0; i < 4; i++)
            cout << MatrixB[i] << endl;
    return 0;
}

