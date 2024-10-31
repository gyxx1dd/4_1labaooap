#include <iostream>
#include <memory>
#include <string>

using namespace std;

class SalaryCalculator {
public:
    virtual double calculateSalary(double rate, double workAmount) = 0;
};

class HourlySalary : public SalaryCalculator {
public:
    double calculateSalary(double hourlyRate, double hoursWorked) override {
        return hourlyRate * hoursWorked;
    }
};

class PieceworkSalary : public SalaryCalculator {
public:
    double calculateSalary(double pieceRate, double piecesCompleted) override {
        return pieceRate * piecesCompleted;
    }
};

class Employee {
protected:
    string name;
    string position;
    shared_ptr<SalaryCalculator> salaryCalculator;

public:
    Employee(const string& name, const string& position, shared_ptr<SalaryCalculator> calculator)
        : name(name), position(position), salaryCalculator(calculator) {}

    virtual double calculatePay(double rate, double workAmount) = 0;

    void displayInfo(double rate, double workAmount) {
        cout << "Name: " << name << ", Position: " << position << endl;
        cout << "Salary: " << calculatePay(rate, workAmount) << " uan" << endl;
    }
};

class Engineer : public Employee {
public:
    Engineer(const string& name, shared_ptr<SalaryCalculator> calculator)
        : Employee(name, "Engineer", calculator) {}

    double calculatePay(double rate, double workAmount) override {
        return salaryCalculator->calculateSalary(rate, workAmount);
    }
};

class Manager : public Employee {
public:
    Manager(const string& name, shared_ptr<SalaryCalculator> calculator)
        : Employee(name, "Manager", calculator) {}

    double calculatePay(double rate, double workAmount) override {
        return salaryCalculator->calculateSalary(rate, workAmount);
    }
};

int main() {
    setlocale(LC_ALL, "Ukr");
    shared_ptr<SalaryCalculator> hourlyCalculator = make_shared<HourlySalary>();
    shared_ptr<SalaryCalculator> pieceworkCalculator = make_shared<PieceworkSalary>();

    Engineer engineer("Ivan", hourlyCalculator);
    Manager manager("Olena", pieceworkCalculator);

    double hourlyRate = 100.0;        
    double hoursWorked = 160;        
    engineer.displayInfo(hourlyRate, hoursWorked);

    double pieceRate = 50.0;          
    double piecesCompleted = 120;     
    manager.displayInfo(pieceRate, piecesCompleted);

    return 0;
}
