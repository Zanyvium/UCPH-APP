// CTRL + F2 when highlighting is REALLY COOL.
// CTRL + SHIFT + L is cooler
// SHIFT + ALT + I is also great
// SHIFT + ALT + A gives block commenting.
/* 
//-----Multi-cursor and selection-----//
Alt+Click Insert cursor
Ctrl+Alt+ ↑ / ↓ Insert cursor above / below
Ctrl+U Undo last cursor operation
Shift+Alt+I Insert cursor at end of each line selected
Ctrl+L Select current line
Ctrl+Shift+L Select all occurrences of current selection
Ctrl+F2 Select all occurrences of current word
Shift+Alt+→ Expand selection
Shift+Alt+← Shrink selection
Shift+Alt +
(drag mouse)
Column (box) selection
Ctrl+Shift+Alt
+ (arrow key)
Column (box) selection
Ctrl+Shift+Alt
+PgUp/PgDn
Column (box) selection page up/down 
*/
// "${workspaceFolder}/*.cpp" <- goes in tasks.json as one of the args//
/* Really cool code to declare and auto loop over arrays ->


const int i = 3, j = 3;
int matrix[i][j] = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
//pmatrix = AllocateMatrixMemory(i,j);
//pmatrix = &matrix;

for (auto &row : matrix)
{
    for (auto &column : row)
    {
        std::cout << column << " ";
    }
    std::cout << endl;
}

//for (auto &row : *pmatrix)
//{
//    for (auto &column : row)
//    {
//        std::cout << column << " ";
//    }
//    std::cout << endl;
//}

*/


#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <random>
//#include "2_6.h"
//#include "3_3.h"
//#include "5_3.h"
//#include "5_4.h"
#include "5_6.h"
//#include "5_9.h"
//#include "5_10.h"

/* void test2_6() {
    double initialGuess = 0.0, epsilon = 0.001;
    double ans = newton_Raphson(initialGuess, epsilon);
    printf("Newton-Raphson (%g, %g) = %g\n", initialGuess, epsilon, ans);
} */

// NOTE:
// Testing against correct formula e^-x does not yield equivalent results! (but close)

/* void test3_3() {
    implicit_Euler(100);
} */


/*void test5_3() {
    double a = 5.7;
    double b = 3.4;
    printf("a = %g, b = %g\n", a, b);
    swap_pointer(&a, &b);
    printf("a = %g, b = %g\n", a, b);
    swap_ref(a, b);
    printf("a = %g, b = %g\n", a, b);
}*/

// NOTE:
// Assignment hinted to divide sum by N-1, but N gives the correct result!
/*
void test5_4()
{
    double a[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    double std = calc_std(a, 10);
    printf("std [1 .. 10] = %g\n", std);
}
*/

// NOTE:
// res must be allocated before calling Multiply A B
//
// when Multiply V M, we provide V as first parameter, but should it not be M x V ?
// or should M x V and V x M give identical results?

void test5_6() {
    const int row_A = 2;
    const int col_A = 3;
    const int row_B = 3;
    const int col_B = 2;

    double** A = new double*[2]; A[0] = new double[2]; A[1] = new double[2];
    double** B = new double*[2]; B[0] = new double[2]; B[1] = new double[2];
    
    
    double** res = new double*[2]; res[0] = new double[2]; res[1] = new double[2];
    Multiply(res, A, B, 2, 2, 2, 2);
    printf("[%g %g]   [%g %g]   [%g %g]\n", A[0][0], A[0][1], B[0][0], B[0][1],
           res[0][0], res[0][1]);
    printf("[%g %g] x [%g %g] = [%g %g]\n", A[1][0], A[1][1], B[1][0], B[1][1],
           res[1][0], res[1][1]);
}

double* AllocateVectorMemory(int numRows) {
    double* vec;
    vec = new double[numRows];

    return vec;
}

void FreeVectorMemory(double* vector) {
    delete[] vector;
}

double** AllocateMatrixMemory(int numRows, int numCols) {
    double** matrix;
    matrix = new double*[numRows];
    for (int i=0; i<numRows; i++) {
        matrix[i] = new double[numCols];
    }
    return matrix;
}

void FreeMatrixMemory(int numRows, double** matrix) {
    for (int i=0; i<numRows; i++) {
        delete[] matrix[i];
    }
    delete matrix;
}

/*
double** AssignMatrixVals(double** matrix, int numRows, int numCols) {
    const int leng = numRows * numCols;
    double inp[leng];
    int k=0;
     for (int i = 0; i<numRows; i++) {
        for (int j = 0; j<numCols; j++) {
            inp[k] = A[i][j];
            k++;
        }   
    } 
     while(k<leng) {
        if (k+1 % numRows) {

        }
        k++;
    } 

}
*/


//void test5_10() {
//    int nrows = 3;
//    int ncols = nrows;
//    double** A = AllocateMatrixMemory(nrows, ncols);
//
//    /*
//    A[0][0] = 3; A[0][1] = -2; A[0][2] = 5; A[0][3] = 0;
//    A[1][0] = 4; A[1][1] = 5; A[1][2] = 8; A[1][3] = 1;
//    A[2][0] = 1; A[2][1] = 1; A[2][2] = 2; A[2][3] = 1;
//    A[3][0] = 2; A[3][1] = 7; A[3][2] = 6; A[3][3] = 5; 
//    */
//
//    A[0][0] = 1; A[0][1] = 1; A[0][2] = 1;
//    A[1][0] = 1; A[1][1] = 1; A[1][2] = 2;
//    A[2][0] = 0; A[2][1] = 5; A[2][2] = 1;
//
//    double* b = new double[ncols]; b[0] = 2; b[1] = 4; b[2] = 5;
//    double* u = new double[ncols];
//
//
//    solve3by3(A, b, u);
//    guassian_elimination(A, b, u, ncols);
//
//    FreeMatrixMemory(nrows, A);
//    FreeVectorMemory(b);
//    FreeVectorMemory(u);
//    //printf("u = [%g, %g, %g]\n", u[0], u[1], u[2]);
//}


int main() {
    //test2_6();
    //test3_3();
    //test5_3();
    //test5_4();
    //test5_6();
    //test5_10();

    const int i = 3, j = 3;
    double matrix[i][j] = {{1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0},
                        {7.0, 8.0, 9.0}};
    double** pmatrix;
    //pmatrix = AllocateMatrixMemory(i,j);
    double (*pmatrix)[i][j] = &matrix; //does the above line do anything when this line is like so?

for (auto &row : matrix)
{
    for (auto &column : row)
    {
        std::cout << column << " ";
    }
    std::cout << std::endl;
}
FreeMatrixMemory(i,pmatrix);

//for (auto &row : *pmatrix)
//{
//    for (auto &column : row)
//    {
//        std::cout << column << " ";
//    }
//    std::cout << endl;
//}


}
 
    

