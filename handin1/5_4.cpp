#include "5_4.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>

//double calc_mean(double a[], int length);
//double calc_std(double a[], int length);
//
//int main() {
////    int age = 19;
////    int* pAge = &age;
////    cout << "int age = 19;" << endl;
////    cout << "int* pAge = &age;" << endl;
////    cout << "pAge = " << pAge << endl;
////    cout << "&pAge = " << &pAge << endl;
////    cout << "*pAge = " << *pAge << endl;
////    cout << "&age = " << &age << endl; // = pAge = location of memory storing age.
//    int n = 1;
//    double* x = new double [n];
//    double* y = new double [n];
//    x[0] = 1.0; // x[1] = 4.0; x[2] = -7.0;
//    y[0] = 4.4; // y[1] = 4.3; y[2] = 76.7;
//    cout << "Mean of x = " << calc_mean(x,n) << endl;
//    cout << "Mean of y = " << calc_mean(y,n) << endl;
//    cout << "Sd of x = " << calc_std(x,n) << endl;
//    cout << "Sd of y = " << calc_std(y,n) << endl;
//    delete[] x;
//    delete[] y;
//    return 0;
//}





double calc_mean(double a[], int length) {
    double summation = 0.0;
    for (int i=0; i<length; i++) {
            summation += a[i];
    }
    return summation/length;
}


double calc_std(double a[], int length) {
    double summation = 0.0;
    double am = calc_mean(a, length);
    for (int i=0; i<length; i++) {
            summation += (a[i]-am)*(a[i]-am);
        }
    double sd;
    if (length>1) {
        sd = sqrt(summation/(length-1));
    } else {
        sd = 0;
    }
    return sd;
}



