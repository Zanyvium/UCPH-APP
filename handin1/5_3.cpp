#include "5_3.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>

//int main(int argc, char* argv[]) {
//    double x[3] = {0.0, 1.0, 0.0};
//    double y[3] = {0.0, 0.0, 1.0};
//    std::ofstream write_output("Output.dat");
//    assert(write_output.is_open());
//    for (int i=0; i<3; i++) {
//        write_output << x[i] << " " << y[i] << "\n";
//    }
//    write_output.close();
//    // Det ses
//    return 0;
//}

//void swap_pointer(double* px, double* py);
//void swap_ref(double& a, double& b);

//int main() {
////    int age = 19;
////    int* pAge = &age;
////    cout << "int age = 19;" << endl;
////    cout << "int* pAge = &age;" << endl;
////    cout << "pAge = " << pAge << endl;
////    cout << "&pAge = " << &pAge << endl;
////    cout << "*pAge = " << *pAge << endl;
////    cout << "&age = " << &age << endl; // = pAge = location of memory storing age.
//
//    double x = 2, y = 3;
//    cout << "Before: x = " << x << ", y = " << y << endl;
//    Swapn(&x, &y);
//    cout << "After: x = " << x << ", y = " << y << endl;
//
//    double a = 6, b = 9;
//    cout << "Before: a = " << a << ", b = " << b << endl;
//    Swapn(a, b);
//    cout << "After: a = " << a << ", b = " << b << endl;
//
//    return 0;
//}




void swap_pointer(double* px, double* py) {
    //No temp variable swap technique
    *px = *px + *py;
    *py = *px - *py;
    *px = *px - *py;
    //Alternatively one might use the std "swap" function, which does the reassignment for us.
    // Equivalent to

    //    *px += *py; // -> *px = *px + *py
    //    *py -= -*px // -> *py = -(*py-*px) = *px - *py
    //    *px -= *py // -> *px = *px - *py

}


//// We can seemingly do function overloading with pointer/reference difference.
//void Swapn(double& a1, double& a2) {
//    a1 = a1 + a2;
//    a2 = a1 - a2;
//    a1 = a1 - a2;
//
//}

// We can seemingly do function overloading, and scoping works fine as well.
void swap_ref(double& a, double& b) {
    a = a + b;
    b = a - b;
    a = a - b;
}




