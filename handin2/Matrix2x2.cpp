#include "Matrix2x2.hpp"

// Overriding the default constructor
Matrix2x2::Matrix2x2() {
    val00 = 0; // first row, first column
	val01 = 0; // first row, second column
	val10 = 0; // second row, first colum
	val11 = 0; // second row, second column
}

//Copy constructor
Matrix2x2::Matrix2x2(const Matrix2x2& A) {
    val00 = A.Getval00();
    val01 = A.Getval01();
    val10 = A.Getval10();
    val11 = A.Getval11();
}

// Constructor that sets the four values of a 2x2 matrix.
Matrix2x2::Matrix2x2(double v00, double v01, double v10, double v11) {
    val00 = v00;
    val01 = v01;
    val10 = v10;
    val11 = v11;
}

//Calculate the determinant
double Matrix2x2::CalcDeterminant() const {
    return val00*val11 - val01*val10;
}

//Calculates the "regular" indouble verse for non-singular matrices. 
Matrix2x2 Matrix2x2::CalcInverse() const  {
    double det = CalcDeterminant();
    assert(det !=  0);
    double nv00 = 1/det * val11;
    double nv01 = -1/det * val01;
    double nv10 = -1/det * val10;
    double nv11 = 1/det * val00;
    return Matrix2x2(nv00, nv01, nv10, nv11);
}

// Overloading the = (assignment) operator
Matrix2x2& Matrix2x2::operator=(const Matrix2x2& A) {
    val00 = A.Getval00();
    val01 = A.Getval01();
    val10 = A.Getval10();
    val11 = A.Getval11();
   return *this;
}

// Overloading the unary - operator
Matrix2x2 Matrix2x2::operator-() const {
   Matrix2x2 B;
   B.val00 = -val00;
   B.val01 = -val01;
   B.val10 = -val10;
   B.val11 = -val11;
   return B;
}

// Overloading the binary + operator
Matrix2x2 Matrix2x2::operator+(const Matrix2x2& A) const {
   Matrix2x2 B;
   B.val00 = val00 + A.val00;
   B.val01 = val01 + A.val01;
   B.val10 = val10 + A.val10;
   B.val11 = val11 + A.val11;
   return B;
}

// Overloading the binary - operator
Matrix2x2 Matrix2x2::operator-(const Matrix2x2& A) const {
   Matrix2x2 B;
   B.val00 = val00 - A.val00;
   B.val01 = val01 - A.val01;
   B.val10 = val10 - A.val10;
   B.val11 = val11 - A.val11;
   return B;
}

void Matrix2x2::MultScalar(double scalar) {
    val00 = scalar * val00; // first row, first column
	val01 = scalar * val01; // first row, second column
	val10 = scalar * val10; // second row, first colum
	val11 = scalar * val11; // second row, second column11
}





