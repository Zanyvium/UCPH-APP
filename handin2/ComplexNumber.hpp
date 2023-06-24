#ifndef COMPLEXNUMBERHEADERDEF
#define COMPLEXNUMBERHEADERDEF

#include <iostream>

class ComplexNumber
{
    private:
        double mRealPart;
        double mImaginaryPart;
    public:
        ComplexNumber();
        ComplexNumber(double x, double y);
        double CalculateModulus() const;
        double CalculateArgument() const;
        ComplexNumber CalculatePower(double n) const;
        ComplexNumber& operator=(const ComplexNumber& z);
        ComplexNumber operator-() const;
        ComplexNumber operator+(const ComplexNumber& z) const;
        ComplexNumber operator-(const ComplexNumber& z) const;
        friend std::ostream& operator<<(std::ostream& output,const ComplexNumber& z);

        //exercise prototypes
        double GetRealPart() const; //GetRealPart() is a function that takes in a complex number, outputs a double, and does not change the complex number
        double GetImaginaryPart() const;
        friend double RealPart(const ComplexNumber& z);
        friend double ImaginaryPart(const ComplexNumber& z);
        ComplexNumber(const ComplexNumber& z);
        ComplexNumber(double real);
        //CalculateConjugate is a function that takes in a complex number, outputs a complex number, but does not change the original complex number 
        ComplexNumber CalculateConjugate() const; 
        void SetConjugate();

        //not mandatory, but useful for exercise 6.1.7
        ComplexNumber operator*(const ComplexNumber& z) const;

};

#endif
