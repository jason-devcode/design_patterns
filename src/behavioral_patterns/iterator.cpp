#include <iostream>
#include <vector>
#include <memory>

// ==============================
// Employee Class
// ==============================
class Employee {
private:
    std::string name;
    int age;

public:
    Employee(std::string n, int a) : name(n), age(a) {}

    void show() const {
        std::cout << "Employee: " << name << ", Age: " << age << '\n';
    }
};

// ==============================
// Iterator Interface
// ==============================
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;  // Is there another element?
    virtual T& next() = 0;             // Return the next element
};

// ==============================
// Concrete Iterator for Company
// ==============================
class CompanyIterator : public Iterator<Employee> {
private:
    std::vector<std::unique_ptr<Employee>>& employees;
    size_t index;

public:
    CompanyIterator(std::vector<std::unique_ptr<Employee>>& emps)
        : employees(emps), index(0) {}

    bool hasNext() const override {
        return index < employees.size();
    }

    Employee& next() override {
        return *employees[index++];
    }
};

// ==============================
// Company Collection
// ==============================
class Company {
private:
    std::vector<std::unique_ptr<Employee>> employees;

public:
    void addEmployee(std::string name, int age) {
        employees.push_back(std::make_unique<Employee>(name, age));
    }

    std::unique_ptr<Iterator<Employee>> getIterator() {
        return std::make_unique<CompanyIterator>(employees);
    }
};

// ==============================
// Using the Iterator Pattern
// ==============================
int main() {
    Company company;
    company.addEmployee("John", 30);
    company.addEmployee("Anna", 28);
    company.addEmployee("Carlos", 35);

    auto iterator = company.getIterator();

    while (iterator->hasNext()) {
        iterator->next().show();
    }

    return 0;
}
