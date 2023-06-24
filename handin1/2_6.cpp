#include "2_6.h"
#include <cmath>

double newton_Raphson(double initialGuess, double epsilon) {
    int n = 100;
    double xprev;
    double xnext;
    xprev = initialGuess;
    for (int i=1; i<n; i++) {
      xnext = xprev - (exp(xprev)+pow(xprev,3)-5.0) / (exp(xprev)+3.0*pow(xprev,2));
      if (fabs(xnext-xprev) < epsilon) {
        return xnext;
      } else {
        xprev = xnext;
      }
    }
    return xnext;
  }