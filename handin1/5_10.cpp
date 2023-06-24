#include "5_10.h"
#include "5_3.h"
#include <iostream>
#include <cmath>
/* 
void swap_refn(double& a, double& b) {
    a = a + b;
    b = a - b;
    a = a - b;
}
 */
void guassian_elimination(double **A, double *b, double *u, int n) {
    double eps = 0.001;
    int maxabsrow;

    //Elimination step
    double quo;
    for (int k = 0; k<=n-2; k++) {
        if (fabs(A[k][k])<eps) {

            //Finding the row with the pivot point of the greatest magnitude
            maxabsrow = k;
            for (int i = k+1; i<=n-1; i++) {
                if (fabs(A[i][k])>fabs(A[maxabsrow][k])) {
                    maxabsrow = i;
                }
            }
            //using swap_ref to swap the values of b, as well as the appropriate rows of A
            swap_ref(b[maxabsrow], b[k]);
            for (int l = 0; l < n; l++) {
                swap_ref(A[k][l], A[maxabsrow][l]);
            }
        }
        for (int i = k+1; i<=n-1; i++) {
            if(A[i][k]!=0) {
                quo = A[k][k] / A[i][k];
                for (int j = k; j<=n-1; j++) {
                    A[i][j] = A[k][j] - A[i][j]*quo;
                }
                b[i] = b[k] - b[i] * quo;
            }
            //
        }
    }
   /* //Printing of A and b
   std::cout << "A = " << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
	        std::cout << A[i][j] << " ";
        }
        // Newline for new row
        std::cout << std::endl;
    }
    
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "b = " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << b[i] << " ";
        // Newline for new row
        std::cout << std::endl;
    }
    */
    //Back-solving
    u[n-1] = b[n-1] / A[n-1][n-1];
    //std::cout << "u[n-1] = " << u[n-1] << std::endl;
    double sum_au;
    for (int i = n-2; i>=0; i--) {
        //std::cout << "f1: i = " << i << std::endl;
        sum_au = 0.0;
        for (int j = i+1; j<=n-1; j++) {
            /*
            std::cout << "f2: j = " << j << std::endl;
            std::cout << "f2: sum_au = " << sum_au << std::endl;
            std::cout << "f2: A[i][j] = " << A[i][j] << std::endl;
            std::cout << "f2: u[j] = " << u[j] << std::endl;
            */
            sum_au += A[i][j]*u[j];
        }
        /*
        std::cout << "f1: b[i] = " << b[i] << std::endl;
        std::cout << "f1: sum_au = " << sum_au << std::endl;
        std::cout << "f1: A[i][i] = " << A[i][i] << std::endl;
        */
        u[i] = (b[i] - sum_au) / A[i][i];
        //std::cout << "f1: u[i] = " << u[i] << std::endl;
    }
    /*
    std::cout << "u = " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << u[i] << " ";
        // Newline for new row
        std::cout << std::endl;
    }
    */
}