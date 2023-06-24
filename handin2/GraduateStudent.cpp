#include "GraduateStudent.hpp"

GraduateStudent::GraduateStudent() : Student() {
    //tuition_fees = 0;
}

GraduateStudent::GraduateStudent(std::string name, double fines, double fees, bool fullTime) : Student(name, fines, 0) {
/*     GraduateStudent::name = name; //possibly this should be removed
    SetLibraryFines(fines); //possibly this should be removed
    tuition_fees = 0; */
    GraduateStudent::fullTime = fullTime;
}

double GraduateStudent::MoneyOwed() const {
    return GetLibraryFines();
}




