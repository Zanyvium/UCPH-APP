#include "Student.hpp"

Student::Student() {
    name = "Not assigned yet";
    library_fines = 0;
    tuition_fees = 0;
}

Student::Student(std::string name, double fines, double fees) {
    Student::name = name;
    SetLibraryFines(fines);
    tuition_fees = fees;
}

double Student::MoneyOwed() const {
    return library_fines + tuition_fees;
}

void Student::SetLibraryFines(double amount) {
    if (amount < 0) amount = -amount;
    library_fines = amount;
}

double Student::GetLibraryFines() const {
    return library_fines;
}


