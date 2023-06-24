#include "PhdStudent.hpp"

PhdStudent::PhdStudent(std::string name, double fines, double fees, bool fullTime) : GraduateStudent() {
    PhdStudent::name = name; //possibly this should be removed
    SetLibraryFines(fines); //possibly this should be removed
    tuition_fees = fees; // = 0?
    PhdStudent::fullTime = fullTime; //=true ?
}

double PhdStudent::MoneyOwed() const {
    return 0;
}