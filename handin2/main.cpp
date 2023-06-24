#include "ComplexNumber.hpp"
#include "CalculateExponential.hpp" //Even though CalculateExponential has its own #include "ComplexNumber.hpp"
                                      // this doesn't include the functionality as implemented in ComplexNumber.cpp
                                      // when only imported here as #include "CalculateExponential.hpp"
#include "Matrix2x2.hpp"
#include "Student.hpp"
#include "GraduateStudent.hpp"
#include "PhdStudent.hpp"
#include "Exception.hpp"
#include "FileNotOpenException.hpp"
#include "OutOfRangeException.hpp"
#include "Exercise82.hpp"

#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>
#include <random>

void PrintComplexMatrix(ComplexNumber** pmatrix, int numRows, int numCols) {
    //Print pmatrix
    std::cout << "" << std::endl;
    for (int i = 0; i<numRows; i++) {
        for (int j = 0; j<numCols; j++) {
            std::cout << pmatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

ComplexNumber** AllocateComplexMatrixMemory(int numRows, int numCols) {
    ComplexNumber** matrix;
    matrix = new ComplexNumber*[numRows];
    for (int i=0; i<numRows; i++) {
        matrix[i] = new ComplexNumber[numCols];
    }
    return matrix;
}

void FreeComplexMatrixMemory(ComplexNumber** matrix, int numRows) {
    for (int i=0; i<numRows; i++) {
        delete[] matrix[i];
    }
    delete matrix;
}


/* 
ComplexNumber** AllocateNCopyMatrix(int numRows, int numCols, ComplexNumber[numRows][numCols]) {

} */
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

    /* //Print A
    std::cout << "A:" << std::endl;
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    } */

    //Allocate pA dynamically
    ComplexNumber** pA = AllocateComplexMatrixMemory(numRowsA, numColsA);
    ComplexNumber** pA2 = AllocateComplexMatrixMemory(numRowsA, numColsA);
    ComplexNumber** pA3 = AllocateComplexMatrixMemory(numRowsA, numColsA);
    //ComplexNumber** pA4 = AllocateComplexMatrixMemory(numRowsA, numColsA);



    /* ComplexNumber** pA = new ComplexNumber*[numRowsA];
    for (int i = 0; i < numRowsA; i++) {
        pA[i] = new ComplexNumber[numColsA];
    } */

    //Allocate values of pA with double for loop
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            pA[i][j] = A[i][j];
        }
    }

/*  //Allocate pA2
    ComplexNumber** pA2 = new ComplexNumber*[numRowsA];
    for (int i = 0; i < numRowsA; i++) {
        pA2[i] = new ComplexNumber[numColsA];
    }
     //Allocate values of pA2 with reference 
    //pA2 = &A; // <- doesn't work!!!!!!!!!

    //deallocate pA2
    for(int i = 0; i<numRowsA; i++) {
        delete[] pA2[i];
    }
    delete[] pA2; */

    /* //Redo copy, by copying the copy
    ComplexNumber** pA2 = new ComplexNumber*[numRowsA];
    ComplexNumber** pA3 = new ComplexNumber*[numRowsA];

    for (int i = 0; i < numRowsA; i++) {
        pA2[i] = new ComplexNumber[numColsA];
        pA3[i] = new ComplexNumber[numColsA];

    } */

    //direct assignment. Results in shallow copy
    pA2 = pA;

    //for-loop assignment for pA3. Results in deep-copy.
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            pA3[i][j] = pA[i][j];
        }
    }

    //pA4 = **pA; <- deep copying this way doesn't work.

/*     //Print pA
    std::cout << "pA:" << std::endl;
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            std::cout << pA[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //Print pA2
    std::cout << "pA2:" << std::endl;
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            std::cout << pA2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //Print pA3
    std::cout << "pA3:" << std::endl;
    for (int i = 0; i<numRowsA; i++) {
        for (int j = 0; j<numColsA; j++) {
            std::cout << pA3[i][j] << " ";
        }
        std::cout << std::endl;
    } */
    std::cout << "First round:" << std::endl;
    std::cout << "A:";
    for (auto &row : A) {
        for (auto &column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "pA:";
    PrintComplexMatrix(pA, numRowsA, numColsA);
    std::cout << "pA2:";
    PrintComplexMatrix(pA2, numRowsA, numColsA);
    std::cout << "pA3:";
    PrintComplexMatrix(pA3, numRowsA, numColsA);


    //Change pA3 and print 
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsA; j++) {
            pA3[i][j] = ComplexNumber(3.0,3.0);
        }
    }

    std::cout << "Second round:" << std::endl;
    std::cout << "A:";
    for (auto &row : A) {
        for (auto &column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "pA:";
    PrintComplexMatrix(pA, numRowsA, numColsA);
    std::cout << "pA2:";
    PrintComplexMatrix(pA2, numRowsA, numColsA);
    std::cout << "pA3:";
    PrintComplexMatrix(pA3, numRowsA, numColsA);
    


    //Change pA2 and print
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsA; j++) {
            pA2[i][j] = ComplexNumber(2.0,2.0);
        }
    }

    std::cout << "Third round:" << std::endl;
    std::cout << "A:";
    for (auto &row : A) {
        for (auto &column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "pA:";
    PrintComplexMatrix(pA, numRowsA, numColsA);
    std::cout << "pA2:";
    PrintComplexMatrix(pA2, numRowsA, numColsA);
    std::cout << "pA3:";
    PrintComplexMatrix(pA3, numRowsA, numColsA);

    //Change pA and print version 1
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsA; j++) {
            pA[i][j] = ComplexNumber(1.0,1.0);
        }
    }

    std::cout << "Fourth round:" << std::endl;
    std::cout << "A:";
    for (auto &row : A) {
        for (auto &column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "pA:";
    PrintComplexMatrix(pA, numRowsA, numColsA);
    std::cout << "pA2:";
    PrintComplexMatrix(pA2, numRowsA, numColsA);
    std::cout << "pA3:";
    PrintComplexMatrix(pA3, numRowsA, numColsA);

    //Change pA and print version 2:
    //This one only changes the [0][0] location, as this is where the pointer to the pointer array is stored.
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsA; j++) {
            **pA = ComplexNumber(1.5,1.5);
        }
    }

    std::cout << "Fifth round:" << std::endl;
    std::cout << "A:";
    for (auto &row : A) {
        for (auto &column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "pA:";
    PrintComplexMatrix(pA, numRowsA, numColsA);
    std::cout << "pA2:";
    PrintComplexMatrix(pA2, numRowsA, numColsA);
    std::cout << "pA3:";
    PrintComplexMatrix(pA3, numRowsA, numColsA);

    //Free Memory
    FreeComplexMatrixMemory(pA, numRowsA);
    FreeComplexMatrixMemory(pA3, numRowsA);
    //FreeComplexMatrixMemory(pA2, numRowsA); // <- As demonstrated, pA2 is a shallow copy of pA, thus is already deleted
    

    /* //deallocate pA
    for(int i = 0; i<numRowsA; i++) {
        delete[] pA[i];
    }
    delete[] pA;

    //deallocate pA2
    for(int i = 0; i<numRowsA; i++) {
        delete[] pA2[i];
    }
    delete[] pA2;

    //deallocate pA3
    for(int i = 0; i<numRowsA; i++) {
        delete[] pA3[i];
    }
    delete[] pA3; */



    // Start:
    const int numRowsB = 3;
    const int numColsB = 3;

    ComplexNumber B[numRowsB][numColsB];
    ComplexNumber** pB = AllocateComplexMatrixMemory(numRowsB, numColsB);
    ComplexNumber** res = AllocateComplexMatrixMemory(numRowsB, numColsB);
    
    //populate B with something
    for (int i = 0; i<numRowsB; i++) {
        for (int j = 0; j<numColsB; j++) {
            B[i][j] = ComplexNumber((2*i+2)*(i == j), (2*i+3)*(i == j));
        }
    }

    //Copy content of B onto pB
    for (int i = 0; i<numRowsB; i++) {
        for (int j = 0; j<numColsB; j++) {
            pB[i][j] = B[i][j];
        }
    }
    std::cout << std::endl;
    const int N = 50;
    std::cout << "pB";
    PrintComplexMatrix(pB,numRowsB, numColsB);
    CalculateExponential(pB, N, res);
    std::cout << "pB^N";
    PrintComplexMatrix(res, numRowsB, numColsB);

    FreeComplexMatrixMemory(pB, numRowsB);
    FreeComplexMatrixMemory(res, numRowsB);

    return 0;
}






