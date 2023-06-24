#include "3_3.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <string>



// 3.3
  // std::cout << "euler\n";
  // We note that for the times x_n:=nh, for n = 0,...N-1
  // we get the times x_0 = 0, x_1 = 1*h, x_{N-1} = (N-1)*h = 1
  // thus for constant h, we get that (N-1)*h=1 <=> h = 1/(N-1)
  void implicit_Euler(int n) {
    assert(n>1);
    double h = 1.0/(n-1.0); //very important that we have 1.0 instead of 1, as the result is otherwise coerced to 0 instead of 1/99 for n=100
    double x[n];
    double y[n];
    x[0] = 0, y[0] = 1;
    std::ofstream write_output("xy.dat");
    assert(write_output.is_open());
    for (int i = 1; i<n; i++) {
      x[i] = i*h;
      y[i] = y[i-1] / (1+h);
      write_output << x[i] << "," << y[i] << "\n";
    }
    write_output.close();
  }

