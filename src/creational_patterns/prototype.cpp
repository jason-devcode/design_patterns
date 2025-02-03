#include <iostream>
#include <memory>
#include <stdexcept>

/**
 * Define Abstract Class Prototype
 */
class Prototype
{
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() = 0;
};

/**
 * Abstract Class Car
 */
class Car : public Prototype
{
public:
    Car() = default;
    Car(int car_number) : car_number(car_number) {};
    virtual ~Car() = default;

    void printCarNumber()
    {
        std::cout << "Car number: " << this->car_number << std::endl;
    }

protected:
    int car_number;
};

/**
 * Concrete Prototype Car Class
 */
class ClassicCar : public Car
{
public:
    ClassicCar(int car_number)
    {
        this->car_number = car_number;
    }
    ~ClassicCar() = default;

    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<ClassicCar>(this->car_number);
    }
};

int main()
{
    try
    {
        std::unique_ptr<Car> car1 = std::make_unique<ClassicCar>(123);
        std::unique_ptr<Prototype> car2 = car1->clone(); 

        car1->printCarNumber();

        if (auto *car2_casted = dynamic_cast<Car *>(car2.get()))
        {
            car2_casted->printCarNumber();
        }
        else
        {
            std::cerr << "Error: Cast not valid." << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
