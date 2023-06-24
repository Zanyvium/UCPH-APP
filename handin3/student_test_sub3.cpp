#include <iostream>
#include <cstdlib>
//#include "./assign3/SparseVector.hpp"
//#include "./student_submissionA/SparseVector.hpp"
#include "SparseVector.hpp"

/*****************************/
/***** PRINTING METHODS ***/
/*****************************/

// these printing functions only assume getValue is correct
template <typename T>
void printSparseFull (SparseVector<T> x, int length, std::string vec_name) {
	std::cout << "Fully printing " << vec_name << ": ";
	for (int i=0; i<length; i++) {
		std::cout << "(" << i << ", " << x.getValue(i) << ") ";
	}
	std::cout << "\n";
}

template <typename T>
void printSparse (SparseVector<T> x, int length, std::string vec_name) {
	std::cout << "Printing non-zeroed " << vec_name << ": ";
	bool empty = true;
	for (int i=0; i<length; i++) {
		if (x.getValue(i) != T()) {
			std::cout << "(" << i << ", " << x.getValue(i) << ") ";
			empty = false;
		}
	}
	if (empty) {
		std::cout << "all 0's";
	}
	std::cout << "\n";
}

template <typename T>
void printSparseIndices (SparseVector<T> x, int length, std::string vec_name) {
	std::cout << vec_name << "'s indices:";
	bool empty = true;
	for (int i=0; i<length; i++) {
		if (x.getValue(i) != T()) {
			std::cout << " " << i;
			empty = false;
		}
	}
	if (empty) {
		std::cout << " all 0's";
	}
	std::cout << "\n";
}

template <typename T>
void printSparseValues (SparseVector<T> x, int length, std::string vec_name) {
	T value;
	bool empty = true;
	std::cout << vec_name << "'s values:";
	for (int i=0; i<length; i++) {
		value = x.getValue(i);
		if (value != T()) {
			std::cout << " " << value;
			empty = false;
		}
	}
	if (empty) {
		std::cout << " all 0's";
	}
	std::cout << "\n";
}

template <typename T>
void printSparseAll (SparseVector<T> x, int length, std::string vec_name) {
    std::cout << "ALL PRINTINGS FOR " << vec_name << ":\n";
	printSparseFull(x, length, vec_name);
	printSparse(x, length, vec_name);
	printSparseIndices(x, length, vec_name);
	printSparseValues(x, length, vec_name);
    std::cout << "\n";
}

/*****************************/
/***** AUXILIARY METHODS ***/
/*****************************/

template <typename T>
bool SparseEqual (SparseVector<T> x, SparseVector<T> y, int length) {
	bool equal = true;
	for (int i=0; i<length; i++) {
		if (x.getValue(i) != y.getValue(i)) {
			equal = false;
		}
	}
	return equal;
}

template <typename T>
bool SparseAddEqual (SparseVector<T> x, SparseVector<T> y, SparseVector<T> result, int length) {
	bool equal = true;
	for (int i=0; i<length; i++) {
		if ((x.getValue(i) + y.getValue(i)) != result.getValue(i)) {
			equal = false;
		}
	}
	return equal;
}

template <typename T>
bool SparseDiffEqual (SparseVector<T> x, SparseVector<T> y, SparseVector<T> result, int length) {
	bool equal = true;
	for (int i=0; i<length; i++) {
		if ((x.getValue(i) - y.getValue(i)) != result.getValue(i)) {
			equal = false;
		}
	}
	return equal;
}

/*****************************/
/****** TESTING METHODS ******/
/*****************************/

template <typename T>
void sizeTest (SparseVector<T> x, int length, std::string vec_name) {
	std::cout << "Testing that size of " << vec_name << " (" << x.size() << ") is equal to " << length;
	if (x.size() == length) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
}

void lengthConstructorTest () {
	std::cout << "CONSTRUCTOR TEST:\n";
	int length = 8;
	SparseVector<int> x(length);
    std::cout << "Succeeded in creating " << length << "-long int sparse vector x.\n";
	sizeTest(x, length, "x");
	length = 15;
    SparseVector<double> y(length);
    std::cout << "Succeeded in creating " << length << "-long double sparse vector y.\n";
	sizeTest(y, length, "y");
    std::cout << "\n";
}

template <typename T>
void getValueTestTemplate (SparseVector<T> x, int length, std::string vec_name) {
	std::cout << "Retrieving first element of " << vec_name << "(==0)";
	// FIRST ELEMENT
	if (x.getValue(0) == T()) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	// LAST ELEMENT
	std::cout << "Retrieving last element of " << vec_name << "(==0)";
	if (x.getValue(length-1) == T()) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	// MIDDLE ELEMENT
	if (length > 5) {
		std::cout << "Retrieving fifth element of " << vec_name << "(==0)";
		if (x.getValue(5) == T()) {
			std::cout << ": test passed \n";
		} else {
			std::cout << ": test not passed \n";
		}
	}
	printSparseAll(x, length, vec_name);
}

void getValueTest (int length) {
	std::cout << "RETRIEVING TEST:\n";
    std::cout << "Retrieving test after constructing with SparseVector<double>(length).\n";
    std::cout << "Succeeded in creating " << length << "-long double sparse vector x.\n";
	SparseVector<double> x(length);
    getValueTestTemplate(x, length, "x");

    std::cout << "Retrieving test after constructing with SparseVector<int>(length).\n";
    std::cout << "Succeeded in creating " << length << "-long int sparse vector y.\n";
	SparseVector<int> y(length);
    getValueTestTemplate(y, length, "y");
}

void setValueTests (SparseVector<double> &x, int length, std::string vec_name) {
    std::cout << "SET VALUE TEST FOR " << vec_name << ":\n";
	double val = -3.1415;
	// FIRST ELEMENT
    std::cout << "Setting first element of " << vec_name;
	x.setValue(0, val);
	if (x.getValue(0) == val) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	// LAST ELEMENT
	std::cout << "Setting last element of " << vec_name;
	x.setValue(length-1, val);
	if (x.getValue(length-1) == val) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	// MIDDLE ELEMENT
	if (length > 2) {
		std::cout << "Setting third element of " << vec_name;
		x.setValue(2, val);
		if (x.getValue(2) == val) {
			std::cout << ": test passed \n";
		} else {
			std::cout << ": test not passed \n";
		}
	}
	printSparse(x,length,vec_name);

	// SET FIRST ELEMENT TO 0
	val = 0.0;
    std::cout << "Setting first element of " << vec_name << " to 0";
	x.setValue(0, val);
	if (x.getValue(0) == val) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	// LAST ELEMENT
	std::cout << "Setting last element of " << vec_name << " to 0";
	x.setValue(length-1, val);
	if (x.getValue(length-1) == val) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	printSparse(x,length,vec_name);

	// UPDATING FIRST ELEMENT
	double upd = 1.1;
	std::cout << "Updating first element of " << vec_name << " with " << upd;
	x.setValue(0, upd);
	if (x.getValue(0) == upd) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	// UPDATING LAST ELEMENT
	upd = 3.4;
	std::cout << "Updating last element of " << vec_name << " with " << upd;
	x.setValue(length-1, upd);
	if (x.getValue(length-1) == upd) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	// UPDATING MIDDLE ELEMENTS
	if (length > 2) {
		upd = 8.9;
		val = -2.2;
		std::cout << "Updating second and third element of " << vec_name 
			<< " with " << upd << " and " <<val;
    	x.setValue(1, upd);
		x.setValue(2, val);
		if (x.getValue(1) == upd && x.getValue(2) == val) {
			std::cout << ": test passed \n";
		} else {
			std::cout << ": test not passed \n";
		}
	}
	printSparse(x,length,vec_name);
    std::cout << "\n";
}

SparseVector<double> copyConstructorTest (SparseVector<double> x, int length, std::string vec_name) {
    std::cout << "COPY CONSTRUCTOR TEST:\n";
	if (length > 5) {
		x.setValue(5, 2.1);
	}
	if (length > 9) {
		x.setValue(9, 5.2);
	}
	printSparseFull(x, length, vec_name);
    std::cout << "Copy-creating vector y from "<< vec_name;
    SparseVector <double> y(x);
	if (SparseEqual(x, y, length)) {
		std::cout << ": test passed \n";
	} else {
		std::cout << ": test not passed \n";
	}
	sizeTest(y,length,"y");
	printSparseAll(y, length, "y");
	return y;
}

void setAddDiffDoubleTestVals (SparseVector<double>& x, SparseVector<double>& y, SparseVector<double>& z, int length) {
	double first = 1.1;
	double last = 5.7;
	double middlex = 8.9;
	double middley = 2.3;
	x.setValue(0, first);
	x.setValue(1, middlex);
	x.setValue(length-3, 7.1);
	y.setValue(1, middley);
	y.setValue(length-2, -middley);
	y.setValue(length-1, last);
	z.setValue(0, -2.4);
	z.setValue(1, -middlex);
	z.setValue(length-3, 7.1);
	z.setValue(length-2, middley);
	z.setValue(length-1, -last);
}

void setAddDiffIntTestVals (SparseVector<int>& x, SparseVector<int>& y, SparseVector<int>& z, int length) {
	int first = 1;
	int last = 5;
	int middlex = 8;
	int middley = 2;
	x.setValue(0, first);
	x.setValue(1, middlex);
	x.setValue(length-3, 7);
	y.setValue(1, middley);
	y.setValue(length-2, -middley);
	y.setValue(length-1, last);
	z.setValue(0, -2);
	z.setValue(1, -middlex);
	z.setValue(length-3, 7);
	z.setValue(length-2, middley);
	z.setValue(length-1, -last);
}

template <typename T>
void singlePlusAssignTest (SparseVector<T> x, SparseVector<T> y, int length, std::string op_name) {
	SparseVector<T> result(x);
	result += y;
	printSparseFull(result, length, op_name);
	if (SparseAddEqual(x,y,result,length)) {
		std::cout << "Test passed \n";
	} else {
		std::cout << "Test not passed \n";
	}
	sizeTest(result, length, "result");
}

// assumes getValue, setValue, and constructors have been tested with previous methods
void plusAssignTest (int length) {
	std::cout << "+= TESTS:\n";
	SparseVector<double> x(length);
	SparseVector<double> y(length);
	SparseVector<double> z(length);
	setAddDiffDoubleTestVals(x, y, z, length);
	printSparseFull(x, length, "x");
	printSparseFull(y, length, "y");
	printSparseFull(z, length, "z");
	singlePlusAssignTest(x,y,length,"x+y");
	singlePlusAssignTest(y,x,length,"y+x");
	singlePlusAssignTest(x,z,length,"x+z");
	singlePlusAssignTest(z,x,length,"z+x");
	singlePlusAssignTest(y,z,length,"y+z");
	singlePlusAssignTest(z,y,length,"z+y");
	SparseVector<int> x0(length);
	SparseVector<int> y0(length);
	SparseVector<int> z0(length);
	setAddDiffIntTestVals(x0, y0, z0, length);
	printSparseFull(x0, length, "x0");
	printSparseFull(y0, length, "y0");
	printSparseFull(z0, length, "z0");
	singlePlusAssignTest(x0,y0,length,"x0+y0");
	singlePlusAssignTest(y0,x0,length,"y0+x0");
	singlePlusAssignTest(x0,z0,length,"x0+z0");
	singlePlusAssignTest(z0,x0,length,"z0+x0");
	singlePlusAssignTest(y0,z0,length,"y0+z0");
	singlePlusAssignTest(z0,y0,length,"z0+y0");
    std::cout << "\n";
}

template <typename T>
void singleDiffAssignTest (SparseVector<T> x, SparseVector<T> y, int length, std::string op_name) {
	SparseVector<T> result(x);
	result -= y;
	printSparseFull(result, length, op_name);
	if (SparseDiffEqual(x,y,result,length)) {
		std::cout << "Test passed \n";
	} else {
		std::cout << "Test not passed \n";
	}
	sizeTest(result, length, "result");
}

// assumes getValue, setValue, and constructors have been tested with previous methods
void diffAssignTest (int length) {
	std::cout << "-= TESTS:\n";
	SparseVector<double> x(length);
	SparseVector<double> y(length);
	SparseVector<double> z(length);
	setAddDiffDoubleTestVals(x, y, z, length);
	printSparseFull(x, length, "x");
	printSparseFull(y, length, "y");
	printSparseFull(z, length, "z");
	singleDiffAssignTest(x,y,length,"x-y");
	singleDiffAssignTest(y,x,length,"y-x");
	singleDiffAssignTest(x,z,length,"x-z");
	singleDiffAssignTest(z,x,length,"z-x");
	singleDiffAssignTest(y,z,length,"y-z");
	singleDiffAssignTest(z,y,length,"z-y");
	SparseVector<int> x0(length);
	SparseVector<int> y0(length);
	SparseVector<int> z0(length);
	setAddDiffIntTestVals(x0, y0, z0, length);
	printSparseFull(x0, length, "x0");
	printSparseFull(y0, length, "y0");
	printSparseFull(z0, length, "z0");
	singleDiffAssignTest(x0,y0,length,"x0-y0");
	singleDiffAssignTest(y0,x0,length,"y0-x0");
	singleDiffAssignTest(x0,z0,length,"x0-z0");
	singleDiffAssignTest(z0,x0,length,"z0-x0");
	singleDiffAssignTest(y0,z0,length,"y0-z0");
	singleDiffAssignTest(z0,y0,length,"z0-y0");
    std::cout << "\n";
}

template <typename T>
void singlePlusTest (SparseVector<T> x, SparseVector<T> y, int length, std::string op_name) {
	SparseVector<T> result(x+y);
	printSparseFull(result, length, op_name);
	if (SparseAddEqual(x,y,result,length)) {
		std::cout << "Test passed \n";
	} else {
		std::cout << "Test not passed \n";
	}
}

// assumes getValue, setValue, and constructors have been tested with previous methods
void plusTest (int length) {
	std::cout << "ADDITION TESTS:\n";
	SparseVector<double> x(length);
	SparseVector<double> y(length);
	SparseVector<double> z(length);
	double first = 1.1;
	double last = 5.7;
	double middlex = 8.9;
	double middley = 2.3;
	setAddDiffDoubleTestVals(x, y, z, length);
	printSparseFull(x, length, "x");
	printSparseFull(y, length, "y");
	printSparseFull(z, length, "z");
	singlePlusTest(x,y,length,"x+y");
	singlePlusTest(y,x,length,"y+x");
	singlePlusTest(x,z,length,"x+z");
	singlePlusTest(z,x,length,"z+x");
	singlePlusTest(y,z,length,"y+z");
	singlePlusTest(z,y,length,"z+y");
	SparseVector<int> x0(length);
	SparseVector<int> y0(length);
	SparseVector<int> z0(length);
	setAddDiffIntTestVals(x0, y0, z0, length);
	printSparseFull(x0, length, "x0");
	printSparseFull(y0, length, "y0");
	printSparseFull(z0, length, "z0");
	singlePlusAssignTest(x0,y0,length,"x0+y0");
	singlePlusAssignTest(y0,x0,length,"y0+x0");
	singlePlusAssignTest(x0,z0,length,"x0+z0");
	singlePlusAssignTest(z0,x0,length,"z0+x0");
	singlePlusAssignTest(y0,z0,length,"y0+z0");
	singlePlusAssignTest(z0,y0,length,"z0+y0");
    std::cout << "\n";
}

template <typename T>
void singleDiffTest (SparseVector<T> x, SparseVector<T> y, int length, std::string op_name) {
	SparseVector<T> result(x-y);
	printSparseFull(result, length, op_name);
	if (SparseDiffEqual(x,y,result,length)) {
		std::cout << "Test passed \n";
	} else {
		std::cout << "Test not passed \n";
	}
}

// assumes getValue, setValue, and constructors have been tested with previous methods
void diffTest (int length) {
	std::cout << "SUBTRACTION TESTS:\n";
	SparseVector<double> x(length);
	SparseVector<double> y(length);
	SparseVector<double> z(length);
	setAddDiffDoubleTestVals(x, y, z, length);
	printSparseFull(x, length, "x");
	printSparseFull(y, length, "y");
	printSparseFull(z, length, "z");
	singleDiffTest(x,y,length,"x-y");
	singleDiffTest(y,x,length,"y-x");
	singleDiffTest(x,z,length,"x-z");
	singleDiffTest(z,x,length,"z-x");
	singleDiffTest(y,z,length,"y-z");
	singleDiffTest(z,y,length,"z-y");
	SparseVector<int> x0(length);
	SparseVector<int> y0(length);
	SparseVector<int> z0(length);
	setAddDiffIntTestVals(x0, y0, z0, length);
	printSparseFull(x0, length, "x0");
	printSparseFull(y0, length, "y0");
	printSparseFull(z0, length, "z0");
	singleDiffAssignTest(x0,y0,length,"x0-y0");
	singleDiffAssignTest(y0,x0,length,"y0-x0");
	singleDiffAssignTest(x0,z0,length,"x0-z0");
	singleDiffAssignTest(z0,x0,length,"z0-x0");
	singleDiffAssignTest(y0,z0,length,"y0-z0");
	singleDiffAssignTest(z0,y0,length,"z0-y0");
    std::cout << "\n";
}


int main(int argc, char* argv[]) {
    std::cout << "Testing SparseVector methods.\n\n";
	std::srand(0);

	int length = 10;
    
	lengthConstructorTest();
    getValueTest(length);

	SparseVector<double> x(length);
    setValueTests(x, length, "x");

	SparseVector<double> y = copyConstructorTest(x, length, "x");

	plusAssignTest(length);
	diffAssignTest(length);
	plusTest(length);
	diffTest(length);

	std::cout << "NON ZEROES TESTS:\n";
    y.setValue(5, 3.7);
    y.setValue(8, -2.1);
    y.setValue(9, -4.1);
	printSparse(x, x.size(), "x");
	printSparse(y, y.size(), "y");
    std::cout << "Testing nonZero count x: " << x.nonZeroes() << "\n";
    std::cout << "Testing nonZero count y: " << y.nonZeroes() << "\n";
    std::cout << "Testing 0th non-zero index of x: " << x.indexNonZero(0) << "\n";
    std::cout << "Testing 2nd non-zero index of x: " << x.indexNonZero(2) << "\n";
    //std::cout << "Testing 9th non-zero index: " << x.indexNonZero(9) << "\n";
    std::cout << "Testing 0th non-zero value of x: " << x.valueNonZero(0) << "\n";
    std::cout << "Testing 2nd non-zero value of x: " << x.valueNonZero(2) << "\n";
    //std::cout << "Testing 9th non-zero value: " << x.valueNonZero(9) << "\n";
    std::cout << "\n";

	std::cout << "MATRIX MULTIPLICATION TESTS:\n";
	int ARows = 9;
	int ACols = y.size();
    std::cout << "Matrix A: \n";
	/* Matrix A: 
	0 0 0 0 0 0.508819 0 0 0 0.0447609
	0 0 0 0 0 0 0 0 0 0.61421
	0 0 0 0 0.986563 0 0 0 0 0.779993
	0 0 0 0 0.802385 0 0 0.520221 0 0.583847
	0 0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0.173743
	0 0 0.255705 0 0 0.539121 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	0 0.363481 0 0 0 0 0 0 0 0
	*/
	Matrix<double> A = Matrix<double>(ARows, ACols);
	for (int i=0; i<ARows; i++) {
		for (int j=0; j<ACols; j++) {
			double new_value = (double) std::rand() / RAND_MAX;
			if (new_value * 100 > 90) {
				double new_value2 = (double) std::rand() / RAND_MAX;
				A(i,j) = new_value - new_value2;
			}
			std::cout << " " << A(i,j) ;
		}
		std::cout << "\n";
	}
    std::cout << "times vector y: ";
	printSparse(y, y.size(), "y"); // (0, 1.1) (1, 8.9) (2, -2.2) (5, 3.7) (8, -2.1) (9, -4.1)

	Vector<double> c(A*y); // 1.69911 -2.51826 -3.19797 -2.39377 0 -0.712346 1.4322 0 3.23498
    std::cout << "is A*y: ";
	for (int i=0; i<ARows; i++) {
		std::cout << c[i] << " ";
	}
	std::cout << "\n";
    
	int BRows = y.size();
	int BCols = 5;
	std::cout << "Matrix B: \n";
	/* Matrix B: 
	0 0 0 0 0
	0 0 0 0.0668624 0
	0.969827 0 0 0 0.411013
	0 0 0 0.384341 0.634502
	0 0 0 0 0
	0 0 0 0 0.608414
	0 0 0 0 0
	0 0 0 0 0
	0 0 0 0.216316 0
	0 0 0 0 0
	*/
	Matrix<double> B = Matrix<double>(BRows, BCols);
	for (int i=0; i<BRows; i++) {
		for (int j=0; j<BCols; j++) {
			double new_value = (double) std::rand() / RAND_MAX;
			if (new_value * 100 > 90) {
				double new_value2 = (double) std::rand() / RAND_MAX;
				B(i,j) = new_value - new_value2;
			}
			std::cout << " " << B(i,j) ;
		}
		std::cout << "\n";
	}
    std::cout << "times vector y:";
	printSparse(y, y.size(), "y"); // (0, 1.1) (1, 8.9) (2, -2.2) (5, 3.7) (8, -2.1) (9, -4.1)
	Vector<double> d(y*B);
    std::cout << "is y*B: "; // -2.13362 0 0 0.140812 1.3469
	for (int i=0; i<BCols; i++) {
		std::cout << d[i] << " ";
	}
	std::cout << "\n\n";

	std::cout << "SETTING AND RETRIEVING VALUES OUT OF BOUNDS TESTS:\n";
	x.setValue(length+4, 2.1);
	sizeTest(x,length,"x"); 
	std::cout << "Should print the recently updated value: \n";
	printSparseFull(x, length+5,"x");
	//printSparseFull(y, length+5,"y");
	std::cout << "The non-zeroes of x should be 5. Non Zeroes = " << x.nonZeroes() << ".\n";
	std::cout << "We should be able to retrieve the last index. IndexNonZero(4) = " << x.indexNonZero(4) << ".\n";
	std::cout << "We should be able to retrieve the last value. IndexNonZero(4) = " << x.valueNonZero(4) << ".\n";
    return 0;
}