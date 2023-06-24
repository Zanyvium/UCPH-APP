#include "CalculateExponential.hpp"
#include "ComplexNumber.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>
#include <random>

ComplexNumber ComplexNumber::operator*(const ComplexNumber& z) const  {
    ComplexNumber w;
    w.mRealPart = mRealPart * z.mRealPart - mImaginaryPart * z.mImaginaryPart;
    w.mImaginaryPart = mRealPart * z.mImaginaryPart + mImaginaryPart * z.mRealPart;
    return w;
}

void Multiply(ComplexNumber** res, ComplexNumber** A, ComplexNumber** B, int ARows, int ACols, int BRows, int BCols) {
    //Matrix A, Matrix B multiplication
    assert(ACols == BRows);
    // For each of the ARows x BCols positions of res, we need to do a vector, vector multiplication.
    for (int i = 0; i<ARows; i++) {
        for (int j = 0; j<BCols; j++) {
            res[i][j] = 0.0;
            for (int k = 0; k<ACols; k++) { //res[i][j] = vectorvectorprod(A[i][], B[][j])
                res[i][j] = res[i][j] + A[i][k]*B[k][j];
            }
        }
    }
}

void Add(ComplexNumber** res, ComplexNumber** A, ComplexNumber** B, int ARows, int ACols, int BRows, int BCols) {
    //Matrix A, Matrix B addition
    assert(ARows == BRows);
    assert(ACols == BCols);
    //simple addition of the elements
    for (int i = 0; i<ARows; i++) {
        for (int j = 0; j<BCols; j++) {
            res[i][j] = A[i][j] + B[i][j];
        }
    }
}

double factorial(double n) {
    if (n == 0.0 || n == 1.0) {
        return 1.0;
    } else {
        return n*factorial(n-1);
    }
}

ComplexNumber complexRealDivide(ComplexNumber z, double a) {
    assert(a != 0.0);
    return(ComplexNumber(z.GetRealPart()/a, z.GetImaginaryPart()/a));
}

void CalculateExponential(ComplexNumber **A, int nMax, ComplexNumber **res) {
    const int nCol = 3;
    const int nRow = 3;
    assert(nMax>=0);

    ComplexNumber** partialRes;
    ComplexNumber** partialRes2;
    partialRes = new ComplexNumber*[nRow];
    partialRes2 = new ComplexNumber*[nRow];
    for (int i=0; i<nRow; i++) {
        partialRes[i] = new ComplexNumber[nCol];
        partialRes2[i] = new ComplexNumber[nCol];
    }
    
    //Initialise the value of the result matrix to be the (complex type) identity
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            //Fancy c++ if-else statement for assigning 1 or zero based on condition.
            res[i][j] = (i == j) ? ComplexNumber(1.0,0.0) : ComplexNumber(0.0,0.0);
            partialRes2[i][j] = (i == j) ? ComplexNumber(1.0,0.0) : ComplexNumber(0.0,0.0);
            
            //res[i][j] = (i == j) ? 1 : 0;
        }
    }
    for (int n = 1; n < nMax+1; n++) {
        Multiply(partialRes, A, partialRes2, nRow, nCol, nRow, nCol); //after this, partialRes = A^n, partialRes2 = A^(n-1)
        
        //Deepcopy result of partialRes2 into partialRes each iteration
        for (int i = 0; i < nRow; i++) {
            for (int j = 0; j < nCol; j++) {
                partialRes2[i][j] = partialRes[i][j];
                res[i][j] = res[i][j] + complexRealDivide(partialRes[i][j],factorial(n));
            }
        }
    }
    for (int i=0; i<nRow; i++) {
        delete[] partialRes[i];
        delete[] partialRes2[i];
        
    }
    delete partialRes;
    delete partialRes2;
}


/*
int main() {
    const int numRowsA = 3;
    const int numColsA = 4;

    ComplexNumber A[numRowsA][numColsA];

    //populate A with something
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            A[i][j] = ComplexNumber(i*numColsA + j + 1, i*numColsA + j - 1);
        }
    }

    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
*/
/*
int main() {
    const int numRowsA = 3;
    const int numColsA = 4;

    ComplexNumber A[numRowsA][numColsA];

    //populate A with something
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            A[i][j] = ComplexNumber(i*numColsA + j + 1, i*numColsA + j - 1);
        }
    }
    std::cout << "A:";
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}*/