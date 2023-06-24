#include "5_6.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>

//void Multiply(double ** res, double **A, double **B, int ARows, int ACols, int BRows, int BCols);
//void Multiply(double* res, double* A, double** B, int ACols, int BRows, int BCols);
//void Multiply(double* res, double** A, double* B, int ARows, int ACols, int BRows);
//void Multiply(double** res, double scalar, double** B, int BRows, int BCols);
//void Multiply(double** res, double** B, double scalar, int BRows, int BCols);
//
//
//int main {
//    int n = 2;
//    int m = 3;
//    int p = 5;
//    double* u = new double[n];
//    double* v = new double[n];
//    double** A = new double*[n];
//    double** B = new double*[m];
//
//    for (int i = 0; i<n; i++) { // A will be a n x m matrix
//        A[i] = new double [m];
//    }
//
//    for (int i = 0; i<m; i++) { // B will be a m x p matrix
//        B[i] = new double [p];
//    }
//    //***************************
//    //*******Do Something********
//
//
//
//
//
//    //***************************
//    delete[] u;
//    delete[] v;
//
//    for (int i = 0; i<n; i++) {
//        delete[] A[i];
//    }
//    delete[] A;
//
//    for (int i = 0; i<m; i++) {
//        delete[] B[i];
//    }
//    delete[] B;
//
//
//    return 0;
//}


void Multiply(double** res, double** A, double** B, int ARows, int ACols, int BRows, int BCols) {
    //Matrix A, Matrix B multiplication
    assert(ACols == BRows);
    // For each of the ARows x BCols positions of res, we need to do a vector, vector multiplication.
    for (int i = 0; i<ARows; i++) {
        for (int j = 0; j<BCols; j++) {
            res[i][j] = 0.0;
            for (int k = 0; k<ACols; k++) { //res[i][j] = vectorvectorprod(A[i][], B[][j])
                res[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}


void Multiply(double* res, double* A, double** B, int ACols, int BRows, int BCols) {
    //rowvector A, Matrix B multiplication
    assert(ACols == BRows);
    // Take the matrix, matrix multiplication above and simply substitute i = 1 (rows).
    // Stare at this for a while, and realise that it summerises to the following.
    for (int j = 0; j<ACols; j++) {
        res[j] = 0.0;
        for (int k = 0; k<BRows; k++) { //res[1][j] = vectorvectorprod(A[1][], B[][j])
            res[j] += A[k]*B[k][j];
        }
    }
}


void Multiply(double* res, double** A, double* B, int ARows, int ACols, int BRows) {
    //Matrix A, Column vector B multiplication
    assert(ACols == BRows);
    // Take the matrix, matrix multiplication above and simply substitute j = 1 (column).
    // Stare at this for a while, and realise that it summerises to the following.
    for (int i = 0; i<ARows; i++) {
        res[i] = 0.0;
        for (int k = 0; k<BRows; k++) { //res[i][1] = vectorvectorprod(A[i][], B[][1])
            res[i] += A[i][k]*B[k];
        }
    }
}

void Multiply(double** res, double scalar, double** B, int BRows, int BCols) {
    // scalar, Matrix B multiplication <- (res = scalar*B)
    // Note that the code to do this is included in the book on page 88
    // and simply needs a rewrite to account for non-square matrices,
    // and different nomenclature.

    for (int i = 0; i<BRows; i++) {
        for (int j = 0; j<BCols; j++) {
            res[i][j] = scalar*B[i][j];
        }
    }
}
void Multiply(double** res, double** B, double scalar, int BRows, int BCols) {
    // Matrix B, scalar multiplication
    // By definition of scalar, matrix multiplication, this operation is commutative.
    // Thus we may simply do a function call to the above Multiply function, or,
    // alternatively, simply copy the code. Here we will however opt for using
    // the code from above with the ordering of the multiplication of scalar and B
    // interchanged (does no difference)
    for (int i = 0; i<BRows; i++) {
        for (int j = 0; j<BCols; j++) {
            res[i][j] = B[i][j] * scalar;
        }
    }
}




