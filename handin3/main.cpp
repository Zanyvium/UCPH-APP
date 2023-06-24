// Next steps would be to allow sending of vectors to the testSuites that they might then pass on
// Also, we should have clearer abruptions if result of test is not as was to be expected.
// <- currently it requires expertise to see whether the output was as expected.
//

#include <iostream>
#include <string>
#include <cassert>
#include <typeinfo>
//#include <type_traits>

#include <vector>
#include <algorithm>

//#include <CxxTest>

#include "Vector.hpp"
#include "VectorOld.hpp"

#include "Matrix.hpp"
#include "SparseVector.hpp"

void printSimple(std::string text) {
    std::cout << text << std::endl;
}

template<class T> VectorOld assignVectorOld(const std::vector<T>& v) {
    // T can only really be double in VectorOld.
    int v_size = v.size();
    VectorOld v1(v_size);
    for (int i = 0; i < v_size; i++) {
        v1[i] = v[i];
    }
    return v1;
}

template<class T, class V> V assignVector(const std::vector<T>& v) {
    // General custom Vector<T> assignment based on std::vector<T> input
    int v_size = v.size();
    V v1(v_size);
    for (int i = 0; i < v_size; i++) {
        v1[i] = v[i];
    }
    return v1;
}

template<class V> V assignCopyVector(const V& v) {
    //General custom Vector assignment based on V class input
    int v_size = v.size();
    V v1 = V(v_size);
    for (int i = 0; i < v_size; i++) {
        v1[i] = v[i];
    }
    return v1;
}


template<class T> void printVectorP(const std::vector<T>& v, const std::string v_name = "") {
    //proper std::vector printing
    std::cout << v_name << std::endl;
    for (const T& entry : v) {
        std::cout << entry << " ";
    }
    std::cout << std::endl;
}

void printVectorOld(const VectorOld& v, const std::string v_name = "") {
    //VectorOld printing
    std::cout << v_name << std::endl;
    
    int v_size = v.size();
    for (int i = 0; i<v_size; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

template<class V> void printVector(const V& v, const std::string v_name = "") {
    //General Custom Vector printing.
    //Requires a .size() method for V
    std::cout << v_name << std::endl;
    int v_size = v.size();
    for (int i = 0; i<v_size; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

template<class V> void printVectorWithInfo(const V& v, const std::string v_name = "") {
    //General Custom Vector printing.
    //Requires a .size() method for V
    //As above, but with more info.
    std::cout << v_name << std::endl;
    int v_size = v.size();
    std::cout << "length of " << v_name << ": " << v_size << std::endl; 
    std::cout << "content:  ";
    for (int i = 0; i<v_size; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "obj type: ";
    for (int i = 0; i<v_size; i++) {
        std::cout << typeid(v[i]).name() << " ";
    }
    
    std::cout << std::endl;
}

template<class V1, class V2> void compareVectors(V1& v1, V2& v2, double epsilon = 1e-4, std::string v1_name = "v1", std::string v2_name = "v2") {
    
    // Function for comparing entries of vectors numerically and that the content is of the same data type.
    // i.e. shouldn't, for example, complane if one is int type and the other is double. -> see testAssert()

    int v1_size = v1.size();
    int v2_size = v2.size();

    //testing that the vectors are of the same length
    assert(v1_size == v2_size);
    
    //test that v1, v2 are of the same type T
    //assert(std::is_same<decltype(v1)::value_type, decltype(v2)::value_type>::value);
   /*  if (std::is_same<typename decltype(v1)::value_type, typename decltype(v2)::value_type>::value) {
        std::cout << "v1 and v2 have the same class T." << std::endl;
    } else {
        std::cout << "v1 and v2 have different classes T." << std::endl;
    } */

    //running through the values of the vectors
    //checking they are the same
    for (int i = 0; i < v1_size; i++) {
        std::cout << "(fabs("<< v1_name << "[" << i << "] - "<< v2_name << "[" << i << "]) = " << fabs(v1[i] - v2[i])  << " <= " << epsilon << " = epsilon) = " << (fabs(v1[i] - v2[i]) <= epsilon) << std::endl;
        /* std::cout << "typeid(v1[" << i << "]).name(): " << typeid(v1[i]).name() 
        << "    " << "typeid(v2[" << i << "]).name(): " 
        << typeid(v2[i]).name() << std::endl; */
        std::cout << typeid(v1[i]).name() << "  " << typeid(v2[i]).name() << std::endl; 
        //assert(typeid(v1[i]).name() == typeid(v2[i]).name());
    }

    std::cout << "\ncompareVectors checks completed" << std::endl;
}



//// Matrix stuff:
int mTV(int i, int j, int nCols) {
    //shorthand for matrixIndexToVectorConvert
    return i*nCols+j;
}

void vTM(const int s, const int nCols, int& i, int& j) {
    // i,j -> s
    j = s % nCols;
    i = (s - j)/ nCols;
}


template<class M> void printMatrix(const M& m, std::string m_name = "m") {
    //print matrix of class M
    int m_Rows = m.GetNumberOfRows();
    int m_Cols = m.GetNumberOfColumns();
    std::cout << m_name << std::endl;
    for (int i = 0; i < m_Rows; i++) {
        for (int j = 0; j < m_Cols; j++) {
            std::cout << m(i,j) << " ";
        }
        std::cout << std::endl;
    }
}

template<class M> void printMatrixWithInfo(const M& m, const std::string m_name = "") {
    //General Custom Vector printing.
    //Requires a .size() method for V
    //As above, but with more info.
    std::cout << m_name << std::endl;
    int m_rows = m.GetNumberOfRows();
    int m_cols = m.GetNumberOfColoumns();

    std::cout << m_name << std::endl;
    std::cout << "number of rows: " << m_rows << std::endl;
    std::cout << "number of columns: " << m_cols << std::endl;
    std::cout << "obj type: " << typeid(m(0,0)).name() << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            std::cout << m(i,j) << " ";
        }
        std::cout << std::endl;
    }
}



template<class T, class M> M assignMatrix(const std::vector<T>& input, const int nRows, const int nCols) {
    // General custom Matrix<T> assignment based on std::vector<T> input
    //as Matrix is row-major-stored, this function defines a matrix which
    //is rowfilled by the content of input
    int input_size = input.size();
    assert(input_size = nRows*nCols);
    M m(nRows, nCols);
    /* for (int s = 0; s < nRows*nCols; s++) {
        
    } */
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m(i,j) = input[mTV(i,j,nCols)];
        }
    }

    return m;
}


template<class M> M assignCopyMatrix(const M& m) {
    //General custom Matrix assignment based on M class input
    int m_Rows = m.GetNumberOfRows();
    int m_Cols = m.GetNumberOfColoumns();
    M m1 = M(m_Rows, m_Cols);
    for (int i = 0; i < m_Rows; i++) {
        for (int j = 0; j < m_Cols; j++) {
            m1(i,j) = m(i,j);
        }
    }
    return m1;
}

template<class M1, class M2> void compareMatrices(M1& m1, M2& m2, double epsilon = 1e-4, std::string m1_name = "m1", std::string m2_name = "m2") {
    
    // Function for comparing entries of vectors numerically and that the content is of the same data type.
    // i.e. shouldn't, for example, complane if one is int type and the other is double. -> see testAssert()

    int m1_rows = m1.GetNumberOfRows();
    int m1_cols = m1.GetNumberOfColumns();
    int m2_rows = m2.GetNumberOfRows();
    int m2_cols = m2.GetNumberOfColumns();

    //testing that the vectors are of the same length
    assert(typeid(m1(0,0)).name() == typeid(m2(0,0)).name());
    assert(m1_rows == m2_rows);
    assert(m1_cols == m2_cols);
    
    //test that v1, v2 are of the same type T
    //assert(std::is_same<decltype(v1)::value_type, decltype(v2)::value_type>::value);
   /*  if (std::is_same<typename decltype(v1)::value_type, typename decltype(v2)::value_type>::value) {
        std::cout << "v1 and v2 have the same class T." << std::endl;
    } else {
        std::cout << "v1 and v2 have different classes T." << std::endl;
    } */

    //running through the values of the vectors
    //checking they are the same

    std::cout << "obj types: " << typeid(m1(0,0)).name() << std::endl;
    for (int i = 0; i < m1_rows; i++) {
        for (int j = 0; j < m1_cols; j++) {
            std::cout << "(fabs("<< m1_name << "(" << i << ", " << j << ") - " << m2_name << "()" << i << ", " << j << ")) = " << fabs(m1(i,j) - m2(i,j))  << " <= " << epsilon << " = epsilon) = " << (fabs(m1(i,j) - m2(i,j)) <= epsilon) << std::endl;
        }
    }
    std::cout << "\ncompareVectors checks completed" << std::endl;
}


/////////////

void testBasic() {
    printSimple("\ntestBasic");
    printSimple("std::vector<int> std_vec = {1,2,3,4,5}");
    std::vector<int> std_vec = {1,2,3,4,5};

    //!!! Note interestingly enough, though we should write "printVectorP<int>(std_vec)"
    //!!! as std_vec is a std::vector<int>, we do not have to, as this is automatically inferred.
    printSimple("printVectorP(std_vec)");
    printVectorP(std_vec);

    printSimple("printVectorP<int>(std_vec)");
    printVectorP<int>(std_vec);

    //Let's try to add 1 to std_vec
    //!!! std_vec += 1; //<- doesn't work!?
    //!!! std_vec = std_vec + 1; //<- doesn't work!?

    // std::vector<int> vec1 = {1,1,1,1,1};
    //!!! std::vector<int> std_vec = std_vec + vec1; //<- doesn't even work either!? very wierd!

}

void testAssert() {
    printSimple("\ntestAssert");

    printSimple("Compare int t1 = 1, with double t2 = 1.0");
    int t1 = 1;
    double t2 = 1.0;
    assert(t1 == t2);

    printSimple("No assertion tripped");
    //printf("printf check");
    //printf_s("printf_s check");
    printSimple("std::vector<int> vs. std::vector<double> check");
    std::vector<int> int_vec = {1,2,3};
    std::vector<double> double_vec = {1.0,2.0,3.0};
    int size_vec = int_vec.size();

    for  (int i = 0; i < size_vec; i++) {
        assert(int_vec[i] == double_vec[i]);
    }
    printSimple("succesfully done asserting");
}

void testTemplateControl() {
    printSimple("\ntestTemplateControl");
    int size_v = 5;
    VectorOld v(size_v);
    v[0] = 0;
    v[1] = 1;
    v[2] = 2;
    v[3] = 3;
    v[4] = 4;
    printSimple("printVectorOld(v)");
    printVectorOld(v);
    printSimple("printVector<VectorOld>(v)");
    printVector<VectorOld>(v);
}

void testAssignment() {
    std::cout << "\ntestAssignment" << std::endl;
    std::vector<int> std_vec = {1,2,3,4,5};
    
    //!!! Note once again, that T = int is automatically inferred.
    printSimple("VectorOld v1 = assignVectorOld(std_vec)");
    VectorOld v1 = assignVectorOld(std_vec);

    //!!!/* printSimple("assignVectorOld<int>(std_vec)");
    //!!! VectorOld v1 = assignVectorOld<int>(std_vec); */

    //!!! Automatic inferrence also extends to VectorOld class:
    printSimple("printVector(v1)");
    printVector(v1);

    //!!! Compared to the "full":
    printSimple("printVector<VectorOld>(v1)");
    printVector<VectorOld>(v1);

    //!!! Note however that for two class/typename arguments, both have to be specified.
    //VectorOld v2 = assignVector(std_vec); // <- doesn't work!

    printSimple("VectorOld v2 = assignVector<int,VectorOld>(std_vec)");
    VectorOld v2 = assignVector<int,VectorOld>(std_vec);
    //!!! utilising automatic type inferrence once again:
    printSimple("printVector(v2)");
    printVector(v2);
}

template<class T> void testAssignCompareVectorVectorOld(std::vector<T>& std_vec) {
    printSimple("\ntestAssignCompareVectorVectorOld");

    //!!! Note how, if class T is included as part of declaration, 
    //!!! we can pass it on as an argument
    printSimple("VectorOld vO = assignVector<T,VectorOld>(std_vec)");
    VectorOld vO = assignVector<T,VectorOld>(std_vec);
    
    //std::vector<int> alt_std_vec = {1,1,1,1,1};
    //Vector v = assignVector<T,Vector>(alt_std_vec);

    printSimple("Vector v = assignVector<T,Vector>(std_vec)");
    Vector<T> v = assignVector<T,Vector<T>>(std_vec);

    printSimple("compareVectors(vO,v)");
    compareVectors(vO,v);
}

//////////////////
//// test copy constructor 
template<class T> void testCopyConstructorVectorVectorOld(const std::vector<T>& std_vec) {
    printSimple("\ntestCopyConstructorVectorVectorOld");
    //Vi vil gerne test at når vi har ændret Vector til at være generel, 
    // vil Vector med Generel datatype med double indsat være 
    VectorOld vO = assignVector<T, VectorOld>(std_vec);
    Vector<T> v = assignVector<T, Vector<T>>(std_vec);

    VectorOld vO_c = VectorOld(vO);
    Vector<T> v_c = Vector(v); //<- skal ændres når vi har ændret generalitet på Vector klassen.
    printSimple("vO_c");
    printVector(vO_c);
    printSimple("v_c");
    printVector(v_c);
    compareVectors(vO_c, v_c);
}

template<class V> void testCopyConstructor(V& v, std::string v_name = "v") {
    printSimple("\ntestCopyConstructor");
    V v_c = V(v); //Copy contructor of the class V
    printVector(v, v_name);
    printVector(v_c, "v_c");
    compareVectors(v, v_c, 0.01, v_name, "v_c");
}

//// test "set size" constructor
template<class V> void testSetSizeConstructor(const int sizeV) {
    printSimple("\ntestSetSizeConstructor");
    V v = V(sizeV);
    printSimple("v");
    printVector(v);
}

/* template<class V> int testGetSizeMethod(const V& v) {
    printSimple("\ntestGetSizeMethod");
    return v.size();
} */

template<class V> void testGetElementOperator(const V& v, const int extraction_index, std::string v_name = "v"){
    printSimple("\ntestGetElementOperator");
    //read element i of vector-class V
    std::cout << v_name << "[" << extraction_index << "] = " << v[extraction_index] << std::endl;
}

template<class T, class V> void testSetElementOperator(V& v, const int insertion_index, T insertion_val, std::string v_name = "v") {
    printSimple("\ntestSetElementOperator");
    //edit element i of vector-class V to be = val
    std::cout << v_name << " before insertion:" << std::endl;
    printVector(v, v_name);
    v[insertion_index] = insertion_val;
    std::cout << v_name << " after insertion:" << std::endl;
    printVector(v, v_name);
}

//try out the new print name capability of printVector, by overloading the testAssignmentOperator function
template<class V> void testAssignmentOperator(const V& v, const std::string v_name = "") {
    printSimple("\ntestAssignmentOperator");
    V v_c = v;
    printVectorWithInfo(v, v_name);
    printVectorWithInfo(v_c, "v_c");
    compareVectors(v,v_c);
}

template<class V> void testUniMinusOperator(const V& v, const std::string v_name = "") {
    printSimple("\ntestUniMinusOperator");
    V v_c = -v;
    printVectorWithInfo(v, v_name);
    printVectorWithInfo(v_c, "v_c");
}

/*  //overload testBinPlusOperator for allowing adding of double and ints.
    template<class T, class T1, class V, class V<T>, class V<T1>> void testBinPlusOperator(const V<T>& v1, const V<T1>& v2, const std::string v1_name = "", const std::string v2_name = "") {
    printSimple("\ntestBinPlusOperator");

    V1 v = v1 + v2; //does it make a difference whether we state V1 or V2 here? //<- yes!
    printVectorWithInfo(v1, v1_name);
    printVectorWithInfo(v2, v2_name);
    std::string v_name = v1_name + " + " + v2_name; 
    printVectorWithInfo(v, v_name);
} */


template<class V> void testBinPlusOperator(const V& v1, const V& v2, const std::string v1_name = "", const std::string v2_name = "") {
    printSimple("\ntestBinPlusOperator");

    V v = v1 + v2; 
    printVectorWithInfo(v1, v1_name);
    printVectorWithInfo(v2, v2_name);
    std::string v_name = v1_name + " + " + v2_name; 
    printVectorWithInfo(v, v_name);
}

/*  //overload testBinMinusOperator for allowing subtraction of double and ints.
    template<class T, class T1, class V, class V<T>, class V<T1>> void tesMinusOperator(const V<T>& v1, const V<T1>& v2, const std::string v1_name = "", const std::string v2_name = "") {
    printSimple("\ntestBinMinusOperator");

    V1 v = v1 - v2; //does it make a difference whether we state V1 or V2 here? //<- yes!
    printVectorWithInfo(v1, v1_name);
    printVectorWithInfo(v2, v2_name);
    std::string v_name = v1_name + " - " + v2_name; 
    printVectorWithInfo(v, v_name);
} */


template<class V> void testBinMinusOperator(const V& v1, const V& v2, const std::string v1_name = "", const std::string v2_name = "") {
    printSimple("\ntestBinMinusOperator");

    V v = v1 - v2; 
    printVectorWithInfo(v1, v1_name);
    printVectorWithInfo(v2, v2_name);
    std::string v_name = v1_name + " - " + v2_name; 
    printVectorWithInfo(v, v_name);
}

template<class V> void testScalarMultOTROperator(const V& v, const double a, const std::string v_name = "", const std::string a_name = "a") {
    printSimple("\ntestScalarMultOTROperator");
    V va = v*a;
    std::cout << a_name << ": " << a << std::endl;
    printVectorWithInfo(v, v_name);
    std::cout << "v*a" << std::endl; 
    printVectorWithInfo(va, "v*a");
}

/* template<class V> void testScalarMultOTLOperator(const V& v, const double a, const std::string v_name = "", const std::string a_name = "a") {
    printSimple("\ntestScalarMultOTLOperator");
    V va = a*v;
    std::cout << a_name << ": " << a << std::endl;
    printVectorWithInfo(v, v_name);
    std::cout << "a*v" << std::endl; 
    printVectorWithInfo(va, "a*v");
} */

template<class V> void testScalarAddOTROperator(const V& v, const double a, const std::string v_name = "", const std::string a_name = "a") {
    printSimple("\ntestScalarAddOTROperator");
    V va = v+a;
    std::cout << a_name << ": " << a << std::endl;
    printVectorWithInfo(v, v_name);
    std::cout << "v+a" << std::endl; 
    printVectorWithInfo(va, "v+a");
}

/* template<class V> void testScalarAddOTLOperator(const V& v, const double a, const std::string v_name = "", const std::string a_name = "a") {
    printSimple("\ntestScalarAddOTLOperator");
    V va = a+v;
    std::cout << a_name << ": " << a << std::endl;
    printVectorWithInfo(v, v_name);
    std::cout << "a+v" << std::endl; 
    printVectorWithInfo(va, "a+v");
} */

template<class V> void testScalarSubtOTLOperator(const V& v, const double a, const std::string v_name = "", const std::string a_name = "a") {
    printSimple("\ntestScalarSubtOTLOperator");
    V va = v-a;
    std::cout << a_name << ": " << a << std::endl;
    printVectorWithInfo(v, v_name);
    std::cout << "v-a" << std::endl; 
    printVectorWithInfo(va, "v-a");
}

template<class V> void testCalculateNorm(const V& v, const int p = 2, const std::string v_name = "", const std::string p_name= "p=2") {
    printSimple("\ntestCalculateNorm");
    double p_norm = v.CalculateNorm(p);
    std::cout << "p = " << p << std::endl;
    printVectorWithInfo(v, v_name);
    std::cout << "||" << v_name << "||_" << p_name << " = " << p_norm << std::endl; 
}

/* template<class V> void testGetStorage(const V& v, const std::string v_name = "") {
    printSimple("\ntestGetStorage");
    std::vector v1 = v.getStorage();
    printVectorP(v1, "storage " + v_name);
} */

//////////////////
//Matrix

void testPrintMatrix() {
    Matrix m = Matrix<double>(2,3);
    printMatrix(m,"m");
}

void testAssignmentMatrixBasic() {
    std::vector<double> v = {1.1,1.2,1.3,1.4,1.5,1.6};
    Matrix<double> m = assignMatrix<double,Matrix<double>>(v, 2, 3);
    printMatrix(m,"m");
}



/* template<class V> int testGetSizeMethod(const V& v) {
    printSimple("\ntestGetSizeMethod");
    return v.size();
} */





/*  //overload testBinPlusOperator for allowing adding of double and ints.
    template<class T, class T1, class V, class V<T>, class V<T1>> void testBinPlusOperator(const V<T>& v1, const V<T1>& v2, const std::string v1_name = "", const std::string v2_name = "") {
    printSimple("\ntestBinPlusOperator");

    V1 v = v1 + v2; //does it make a difference whether we state V1 or V2 here? //<- yes!
    printVectorWithInfo(v1, v1_name);
    printVectorWithInfo(v2, v2_name);
    std::string v_name = v1_name + " + " + v2_name; 
    printVectorWithInfo(v, v_name);
} */



/*  //overload testBinMinusOperator for allowing subtraction of double and ints.
    template<class T, class T1, class V, class V<T>, class V<T1>> void tesMinusOperator(const V<T>& v1, const V<T1>& v2, const std::string v1_name = "", const std::string v2_name = "") {
    printSimple("\ntestBinMinusOperator");

    V1 v = v1 - v2; //does it make a difference whether we state V1 or V2 here? //<- yes!
    printVectorWithInfo(v1, v1_name);
    printVectorWithInfo(v2, v2_name);
    std::string v_name = v1_name + " - " + v2_name; 
    printVectorWithInfo(v, v_name);
} */


//Test suites:
void testSuite0(){
    int a = 4;
    int b = 3;
    std::cout << (a <= b) << std::endl;
    printSimple("testSuite0 complete");
}

void testSuite1() {
    //doing basic tests;
    testBasic();
    testAssert();
    testTemplateControl();
    testAssignment();
    printSimple("testSuite1 complete");
}

void testSuite2() {
    //Tests the comparing of VectorOld vectors.
    std::vector<double> std_vec = {1.0,2.0,3.0,4.0,5.0};

    const int size = 5;
    const int const_value = 4;
    std::vector<int> std_vec2(size, const_value); //!!! <- this works apparently as one of the constructors of the vector class. 
    printVectorP(std_vec2, "std_vec2");

    VectorOld vO_std_vec = assignVector<double, VectorOld>(std_vec);
    //VectorOld can't be int and will thus be coerced to double automatically,
    //such that compareVectors will report it to be composed of double entries.
    VectorOld vO_std_vec2 = assignVector<int, VectorOld>(std_vec2); 
    compareVectors(vO_std_vec, vO_std_vec2, 3);
    printSimple("testSuite2 complete");
}

void testSuite3() {
    //tests assignment for std::vector input in terms of preserving datatype for Vector class
    std::vector<int> v1 = {1,2,3,4};
    std::vector<double> v2 = {4.0,3.0,2.0,1.0};
    printSimple("std vectors:");
    std::cout << typeid(v1[0]).name() << std::endl;
    std::cout << typeid(v2[0]).name() << std::endl;

    printSimple("Vector Class:");
    Vector v1O = assignVector<int, Vector<int>>(v1);
    Vector v2O = assignVector<double, Vector<double>>(v2);
    compareVectors(v1O, v2O, 3);
    printSimple("testSuite3 complete");
}

void testSuite4() {
    //tests Copying function based on Vector input
    std::vector<int> v1 = {1,2,3,4};
    std::vector<double> v2 = {4.0,3.0,2.0,1.0};
    printSimple("std vectors:");
    std::cout << typeid(v1[0]).name() << std::endl;
    std::cout << typeid(v2[0]).name() << std::endl;

    printSimple("Vector Class:");
    //!!! note that the two commented lines below actually also work,
    //!!! but that it won't work to remove <int> and <double for the assignCopyVector
    //!!! functions further below, as these do not have a specification of their type T
    //!!! in their function, unlike assignVector.

    //Vector v1O = assignVector<int, Vector<int>>(v1);
    //Vector v2O = assignVector<double, Vector<double>>(v2);
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);
    
    Vector<int> v1O_2 = assignCopyVector(v1O);
    Vector<double> v2O_2 = assignCopyVector(v2O);

    compareVectors(v1O, v1O_2, 3, "v1O", "v1O_2");
    compareVectors(v2O, v2O_2, 3, "v2O", "v2O_2");
    compareVectors(v1O_2, v2O_2, 3, "v1O_2", "v2O_2");
    printSimple("testSuite4 complete");
}

void testSuite5() {
    //tests copy constructor
    std::vector<int> v1 = {1,2,3,4};
    std::vector<double> v2 = {4.0,3.0,2.0,1.0};

    //Vector v1O = assignVector<int, Vector<int>>(v1);
    //Vector v2O = assignVector<double, Vector<double>>(v2);
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

    //!!! Note once again that the following two lines can be used, as inference on V1O being a Vector<int>
    //!!! as well as V2O being a Vector<double> is automatically done
    //!!! Try for example to let mouse hover over testCopyConstructor calls below to see this.

    //testCopyConstructor(v1O, "v1O");
    //testCopyConstructor(v2O, "v2O");
    testCopyConstructor<Vector<int>>(v1O, "v1O");
    testCopyConstructor<Vector<double>>(v2O, "v2O");

    printSimple("testSuite 5 complete");
}

void testSuite6() {
    //Tests size constructor
    int size_of_vector = 4;
    std::vector<int> v1 = {1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,2.1,1.1};

    //!!! hovering over V1O or V2O of the above shows that the specification
    //!!! of T on the RHS transfers to the LHS
    //Vector v1O = Vector<int>(size_of_vector);
    //Vector v2O = Vector<double>(size_of_vector);

    Vector<int> v1O = Vector<int>(size_of_vector);
    Vector<double> v2O = Vector<double>(size_of_vector);
    printVectorWithInfo(v1O, "v1O");
    printVectorWithInfo(v2O, "v2O");

    printSimple("testSuite6 Complete");
}

void testSuite7() {
    //tests size method
    int v1_size = 12;
    int v2_size = 6;

    std::vector<int> v1(v1_size);
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);

    std::vector<double> v2(v2_size);
    Vector<double> v2O = assignVector<double,Vector<double>>(v2);
    
    std::cout << "v1O.size(): " << v1O.size() << std::endl;
    std::cout << "v2O.size(): " << v2O.size() << std::endl;
    printSimple("testSuite7 Complete");
}

void testSuite8() {
    //tests getting and setting using operator []

    int element_index1 = 3;
    int element_index2 = 2;

    int insertion_element1 = 9;
    double insertion_element2 = 7.7;


    std::vector<int> v1 = {1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

    testGetElementOperator(v1O, element_index1,"v1O");
    testGetElementOperator(v2O, element_index2,"v2O");

    testSetElementOperator<int, Vector<int>>(v1O, element_index1, insertion_element1, "v1O");
    testSetElementOperator(v2O, element_index2, insertion_element2, "v2O");

    printSimple("testSuite8 Complete");
}

void testSuite9() {
    //tests the assignment operator to copy objects.
    //because of the use of reference variables in definition, we get a deep copy.
    std::vector<int> v1 = {1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);


    testAssignmentOperator(v1O, "v1O");
    testAssignmentOperator(v2O, "v2O");

    /* Vector<int> v1O_2 = v1O;
    Vector<double> v2O_2 = v2O;
    printVectorWithInfo(v1O_2);
    printVectorWithInfo(v2O_2); */
    printSimple("testSuite9 complete");
}

void testSuite10() {
    //tests unitary - operator
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

    testUniMinusOperator(v1O, "v1O");
    testUniMinusOperator(v2O, "v2O");

    printSimple("testSuite10 complete");
}

void testSuite11() {
    //tests binary + operator with same datatype
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<int> v1_2 = {1,3,2,-5};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    std::vector<double> v2_2 = {-4.1,2,2.1,0};

    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<int> v1_2O = assignVector<int, Vector<int>>(v1_2);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);
    Vector<double> v2_2O = assignVector<double, Vector<double>>(v2_2);


    printSimple("int:");
    testBinPlusOperator(v1O, v1_2O, "v1O", "v1_2O");
    printSimple("\ndouble:");
    testBinPlusOperator(v2O, v2_2O, "v2O", "v2_2O");

    printSimple("testSuite11 complete");
}

void testSuite12() {
    //tests binary + operator with different datatypes
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<int> v1_2 = {1,3,2,-5};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    std::vector<double> v2_2 = {-4.1,2,2.1,0};

    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<int> v1_2O = assignVector<int, Vector<int>>(v1_2);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);
    Vector<double> v2_2O = assignVector<double, Vector<double>>(v2_2);


//uncomment when ready ->
/*     printSimple("mixed. int first");
    testBinPlusOperator(v1O, v2O, "v1O", "v2O");
    printSimple("mixed. double first");
    testBinPlusOperator(v2O, v1O, "v2O", "v1O"); 
*/

    printSimple("testSuite12 complete");
}

void testSuite13() {
    //tests binary - operator with same datatype
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<int> v1_2 = {1,3,2,-5};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    std::vector<double> v2_2 = {-4.1,2,2.1,0};

    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<int> v1_2O = assignVector<int, Vector<int>>(v1_2);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);
    Vector<double> v2_2O = assignVector<double, Vector<double>>(v2_2);


    printSimple("int:");
    testBinMinusOperator(v1O, v1_2O, "v1O", "v1_2O");
    printSimple("\ndouble:");
    testBinMinusOperator(v2O, v2_2O, "v2O", "v2_2O");

    printSimple("testSuite13 complete");
}

void testSuite14() {
    //tests binary - operator with different datatypes
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<int> v1_2 = {1,3,2,-5};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    std::vector<double> v2_2 = {-4.1,2,2.1,0};

    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<int> v1_2O = assignVector<int, Vector<int>>(v1_2);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);
    Vector<double> v2_2O = assignVector<double, Vector<double>>(v2_2);


//uncomment when ready ->
/*     printSimple("mixed. int first");
    testBinMinusOperator(v1O, v2O, "v1O", "v2O");
    printSimple("mixed. double first");
    testBinMinusOperator(v2O, v1O, "v2O", "v1O"); 
*/

    printSimple("testSuite14 complete");
}

void testSuite15() {
    //tests double-type scalar multiplication on right side of Vector
    double a = 1.5;
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

    testScalarMultOTROperator(v1O, a, "v1O", "a");
    testScalarMultOTROperator(v2O, a, "v2O", "a");
    
    printSimple("testSuite15 complete");
}

void testSuite16() {
    //tests double-type scalar multiplication on left side of Vector 
    double a = 1.5;
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

/*     testScalarMultOTLOperator(v1O, a, "v1O", "a");
    testScalarMultOTLOperator(v2O, a, "v2O", "a"); */

    printSimple("testSuite16 complete");
}

void testSuite17() {
    //tests double-type scalar addition on right side of Vector 
    double a = 1.5;
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

    testScalarAddOTROperator(v1O, a, "v1O", "a");
    testScalarAddOTROperator(v2O, a, "v2O", "a");

    printSimple("testSuite17 complete");
}

void testSuite18() {
    //tests double-type scalar addition on left side of Vector
    double a = 1.5;
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

/*     testScalarAddOTLOperator(v1O, a, "v1O", "a");
    testScalarAddOTLOperator(v2O, a, "v2O", "a");
     */

    printSimple("testSuite18 complete");
}

void testSuite19() {
    //tests double-type scalar subtraction on left side of Vector
    double a = 1.5;
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

    testScalarSubtOTLOperator(v1O, a, "v1O", "a");
    testScalarSubtOTLOperator(v2O, a, "v2O", "a");
    
    printSimple("testSuite19 complete");
}

void testSuite20() {
    //tests CalculateNorm
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);

    int p1 = 1;
    int p2 = 2;
    int p3 = 3;

    testCalculateNorm(v1O, p1, "v1O", "1");
    testCalculateNorm(v2O, p1, "v2O", "1");

    testCalculateNorm(v1O, p2, "v1O", "2");
    testCalculateNorm(v2O, p2, "v2O", "2");

    testCalculateNorm(v1O, p3, "v1O", "3");
    testCalculateNorm(v2O, p3, "v2O", "3");

    printSimple("testSuite20 complete");
}

void testSuite21() {
/*     //tests getStorage method.
    std::vector<int> v1 = {-1,2,3,4};
    std::vector<double> v2 = {4.1,3.1,-2.1,1.1};
    Vector<int> v1O = assignVector<int, Vector<int>>(v1);
    Vector<double> v2O = assignVector<double, Vector<double>>(v2);
    
    printVector(v1O, "v1O");
    printVector(v2O, "v2O");
    testGetStorage(v1O, "v1O");
    testGetStorage(v2O, "v2O");

    printSimple("testSuite21 Complete"); */
}

void testSuiteLATE() {
    //tests Vector and VectorOld copies of std_vector against each other,
    //using self-built vectorAssign (not class assign(=)) function, and
    //the class copy constructor functionality.

    //requires Vector class to be operational.

    std::vector<double> std_vec = {1.0,2.0,3.0,4.0,5.0};
    ////tests that the Assignment of std_vec
    //// to Vector and VectorOld yield same entries in Vector as in VectorOld
    testAssignCompareVectorVectorOld(std_vec); 
    
    ////tests that the Assignment of std_vec
    ////to Vector and VectorOld, and the subsequent copying using the copyconstructor
    ////in each class, yield the same copied vector in terms of entries.
    testCopyConstructorVectorVectorOld(std_vec);
    printSimple("testSuiteLATE complete");
}

void testSuiteSparse1() {
    unsigned int mDim = 6;
    unsigned int index = 7;
    double value = 22.1;

/*     std::vector<unsigned int> v1 = {1,2,3,4,5};
    std::vector<unsigned int> v2 = {6,7,8,9,10};
    std::vector<unsigned int> res; */
/*     std::vector<double> v = {0,3,1,0,6,0};
    std::vector<unsigned int> mIndices = {1,2,4};
    std::vector<double> mValues = {3,1,6}; */
    std::vector<unsigned int> mIndices = {0};
    std::vector<double> mValues = {5.5};

/*     v2.insert(v2.end()-1, v1.begin(), v1.end());
    printVectorP(v2); */



    mDim = (mDim>=index) ? mDim : index;
    


    std::vector<double>::iterator val_it = mValues.begin();
    if (mIndices.size() == 0) {
		//there are no other non-zero entries.
		//we insert the index and value provided directly.
		
		mValues.push_back(value);
		mIndices.push_back(index);
		//for mIndices.size() != 0 "else case" below, method below would work if not for segmentation
		//problems with the conditional checking whether bound content is equal to index in case of the "empty vector".
		//!!! <- (see tests)

	} else {
        auto bound = std::lower_bound(mIndices.begin(), mIndices.end(), index);
        auto relative_steps_in_i = bound - mIndices.begin();

        if (*bound == index) {
            mValues.erase(val_it + relative_steps_in_i);
            printSimple("Yes, index is already in mIndices. Thus we replace the element at mValues[index]");
        } else {
            mIndices.insert(bound, index);
            printSimple("No, index is not already in mIndices. Thus we add a record to mIndices and mValues at the location");
        }
        mValues.insert(val_it + relative_steps_in_i, value);

        //mValues.insert(val_it + bound_distance, value);

        printVectorP(mValues,"mValues");
        printVectorP(mIndices,"mIndices");


        /* if (*bound == index) {
            mValues.erase(val_it + bound_distance);
        }  else {
            mIndices.insert(bound, index);
        }
        mValues.insert(val_it+bound_distance, value); */
    /*
        //std::cout << mDim << std::endl;
        printVectorP(mIndices);
        printVectorP(mValues);
        printSimple("*bound");
        std::cout << *bound << std::endl;
        printSimple("*val_it + bound_distance");
        std::cout << *val_it + bound_distance << std::endl; */
    }
}

void testSuiteSparse2() {
    //tests getValue

    unsigned int mDim = 6;
    unsigned int index = 2;
    double value = 22.1;

/*     std::vector<unsigned int> v1 = {1,2,3,4,5};
    std::vector<unsigned int> v2 = {6,7,8,9,10};
    std::vector<unsigned int> res; */
/*     std::vector<double> v = {0,3,1,0,6,0};
    std::vector<unsigned int> mIndices = {1,2,4};
    std::vector<double> mValues = {3,1,6}; */
    std::vector<unsigned int> mIndices = {0,2,5};
    std::vector<double> mValues = {8.8,3.2,9.6};

/*     v2.insert(v2.end()-1, v1.begin(), v1.end());
    printVectorP(v2); */



    mDim = (mDim>=index) ? mDim : index;

    auto search_it = std::find(mIndices.begin(), mIndices.end(), index);
	if (search_it != mIndices.end()) {
		int position_found = search_it - mIndices.begin();
        std::cout << "Position: " << index << " found: " << position_found << std::endl;
        //std::cout << "Value at position: " << mValues[position_found] << std::endl;

		auto mValues_begin_it = mValues.begin();
        std::cout << "Value at position: " << *(mValues_begin_it + position_found) << std::endl;
	} else {
		std::cout << "Position: " << index << " not found, must thus be 0" << std::endl;
	}
}

void testSuiteSparse3() {
    //sets basic insertions and readings
    SparseVector<double> sv(6);
    sv.setValue(4,2.1);
    sv.setValue(1,6.1);
    sv.setValue(3,3.1);
    printSparse(sv, "sv");
    int n_nonzero = sv.nonZeroes();
    for(int i = 0; i < n_nonzero; i++) {
        std::cout << "valueNonZero(" << i << ") = " << sv.valueNonZero(i) << std::endl;
    }
}

void testSuiteSparse4() {
    //tests setting and reading of values from beyond the dimensionality
    SparseVector<double> sv(6);
    sv.setValue(4,2.1);
    sv.setValue(1,6.1);
    sv.setValue(3,3.1);
    sv.setValue(8,1.3);
    printSparse(sv, "sv"); //printSparse uses getSparse which uses getValues
    int n_nonzero = sv.nonZeroes();
    for(int i = 0; i < n_nonzero; i++) {
        std::cout << "valueNonZero(" << i << ") = " << sv.valueNonZero(i) << std::endl;
    }
}

void testSuiteSparse5() {
    //test copy constructor
    SparseVector<double> sv(6);
    sv.setValue(4,2.1);
    sv.setValue(1,6.1);
    sv.setValue(3,3.1);
    sv.setValue(8,1.3);
    SparseVector<double> sv2(sv);
    printSparse(sv2, "sv2");

    sv2.setValue(4,3.3);
    std::cout << "sv2 with inserted value" << std::endl;
    printSparse(sv2, "sv2");

    std::cout << "sv1 after sv2 had inserted value" << std::endl;
    printSparse(sv, "sv");
}

void testSuiteSparse6() {
    //test size 0 cases with nonZeroes(), size(), indexNonZero() and valueNonZero()
    SparseVector<int> sv;
    std::cout << "sv.size() = " << sv.size() << std::endl;
    std::cout << "sv.nonZeros() = " << sv.nonZeroes() << std::endl;
    std::cout << "sv.indexNonZero()" << sv.indexNonZero(3) << std::endl;
    std::cout << "sv.valueNonZero()" << sv.valueNonZero(3) << std::endl;
}

void testSuiteSparse7() {
    //test setSparse function
    std::vector<double> v = {0,1.2,0,0,0,5.3,0,6.6,7.7,0};
    SparseVector<double> sv = setSparse(v);
    printSparse(sv);
}

void testSuiteSparse8() {
    //tests += operator and -= operator
    std::vector<double> v = {0,1.2,0,0,0,5.3,0,6.5,7.7,0};
    std::vector<double> v1 = {0,0,1.2,0,0,5.3,0,6.5,0,7.7};

    SparseVector<double> sv = setSparse(v);
    SparseVector<double> sv1 = setSparse(v1);

    printSparse(sv, "sv before");

    sv+=sv1;
    printSparse(sv, "sv+=sv1");

    sv-=sv1;
    printSparse(sv, "sv-=sv1 (=sv?)");
}

void testSuiteSparse9() {
    //tests + and - operators.
    std::vector<double> v = {0,1.2,0,0,0,5.3,0,6.5,7.7,0};
    std::vector<double> v1 = {0,0,1.2,0,0,5.3,0,6.5,0,7.7};

    SparseVector<double> sv = setSparse(v);
    SparseVector<double> sv1 = setSparse(v1);

    printSparse(sv, "sv");
    printSparse(sv1, "sv1");

    SparseVector sv2 = sv + sv1;
    printSparse(sv2, "sv2 = sv + sv1");
    SparseVector sv3 = sv - sv1;
    printSparse(sv3, "sv3 = sv - sv1");
}

void testSuiteSparse10() {
    //tests matrix-vector and vector-matrix products.
    std::vector<double> v = {0,1.2,0,0,0,5.3,0,6.5,7.7,0};

    SparseVector<double> sv = setSparse(v);
    printSparse(sv, "sv");

    int m_nrow = 10;
    int m_ncol = 2;
    int m2_nrow = 2;
    int m2_ncol = 10;
    Matrix<double> m(m_nrow,m_ncol);
    Matrix<double> m2(m2_nrow,m2_ncol);
    for (int i = 0; i<m_nrow; i++) {
        for (int j = 0; j <m_ncol; j++) {
            m(i,j) = i*m_ncol+j;
        }
    }
    for (int i = 0; i<m2_nrow; i++) {
        for (int j = 0; j <m2_ncol; j++) {
            m2(i,j) = i*m2_ncol+j;
        }
    }
    printMatrix(m, "m");
    printMatrix(m2, "m2");

    Vector nv = sv*m;
    Vector nv2 = m2*sv;

    printVector(nv, "sv*m");
    printVector(nv2, "m2*sv");
}


void testSparse() {
    //taken from Github
/*     std::cout << "s: Empty vector of size 10:\n";
    SparseVector<int> s(10);
    printSparse(s);

    std::cout << "\ns2: Empty vector of size 0:\n";
    SparseVector<int> s2;
    printSparse(s2);

    std::cout << "\nSet 4 values of s, out of order.\n";
    s.setValue(1, 3);
    s.setValue(3, 4);
    s.setValue(6, 1);
    s.setValue(2, 5);


    std::cout << "Then print s:\n";
    for (int i = 0; i<10; i++)
    {
        std::cout << i << ", " << s.getValue(i) << "\n";
    }

    std::cout << "\ns3\n"; 
    SparseVector<int> s3(10);
    s3.setValue(1, 4);
    s3.setValue(0, 3);
    printSparse(s3);

    std::cout << "\ns+s3:\n";
    printSparse(s+s3);

    std::cout << "\ns-s3:\n";
    printSparse(s-s3);

    Matrix<int> sm(5, 5);
    sm(0,0) = 1;
    sm(1,1) = 1;
    sm(0,3) = 1;
    sm(2,0) = 1;
    sm(2,2) = 1;
    sm(3,3) = 1;
    sm(4,4) = 1;

    SparseVector<int> s4(5);
    s4.setValue(1, 3);
    s4.setValue(3, 2); */

/*     std::cout << "\ntesting matrix-vector product. Matrix:\n";
    sm.print();
    std::cout << "vector [0, 3, 0, 2, 0]. Result should be [2,3,0,2,0]\n";
    (sm*s4).print();

    std::cout << "vector-matrix product of same matrix/vector.\n"
              << "Result should be [0, 3, 0, 2, 0]\n";
    (s4*sm).print(); */
}


//main
int main() {
    //testSuite0();
    //testSuite1();
    //testSuite2();
    //testSuite3();
    //testSuite4();
    //testSuite5();
    //testSuite6();
    //testSuite7();
    //testSuite8();
    //testSuite9();
    //testSuite10();
    //testSuite11();
    //testSuite12(); // <- remain unchecked, until mixed + operator overload functional
    //testSuite13();
    //testSuite14(); // <- remain unchecked, until mixed - operator overload functional
    //testSuite15(); //!?! <- Notice that the int vectors remain int, and thus, the multiplication acts counter to intuition.
    //testSuite16(); // <- remain unchecked until OTL operators are functional
    //testSuite17(); //!?! <- Notice that the int vectors remain int, and thus, the multiplication acts counter to intuition.
    //testSuite18(); // <- remain unchecked until OTL operators are functional
    //testSuite19(); //!?! <- Notice that the int vectors remain int, and thus, the multiplication acts counter to intuition.
    //testSuite20();
    //testSuite21();

    //testPrintMatrix();
    //testAssignmentMatrixBasic();

    //testSuiteSparse1();
    //testSuiteSparse2();
    //testSuiteSparse3();
    //testSuiteSparse4();
    //testSuiteSparse5();
    //testSuiteSparse6();
    //testSuiteSparse7();
    //testSuiteSparse8();
    //testSuiteSparse9();
    testSuiteSparse10();
    
    //testSparse();

    return 0;
}