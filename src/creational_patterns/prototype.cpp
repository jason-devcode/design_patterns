#include <iostream>
#include <memory>
#include <stdexcept>

/**
 * Abstract Class Car
 */
class Car
{
public:
    Car() = default;
    virtual ~Car() = default;

    Car(int car_number) : car_number(car_number) {};

    /**
     * method to clone objects - prototype pattern
     */
    virtual std::unique_ptr<Car> clone() const = 0;

    virtual void printCarNumber() const
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

    std::unique_ptr<Car> clone() const override
    {
        return std::make_unique<ClassicCar>(this->car_number);
    }

    virtual void printCarNumber() const override
    {
        std::cout << "Classic Car number: " << this->car_number << std::endl;
    }
};

/**
 * Factory method to complement prototype example
 */
class CarFactory
{
public:
    ~CarFactory() = default;
    virtual std::unique_ptr<Car> createCar(int car_number) const = 0;
};

/**
 * Concrete Car Factories
 */
class ClassicCarFactory : public CarFactory
{
public:
    ~ClassicCarFactory() = default;
    std::unique_ptr<Car> createCar(int car_number) const override
    {
        return std::make_unique<ClassicCar>(car_number);
    }
};

int main()
{
    try
    {
        std::unique_ptr<CarFactory> carFactory = std::make_unique<ClassicCarFactory>();

        std::unique_ptr<Car> car1 = carFactory->createCar(123);
        std::unique_ptr<Car> car2 = car1->clone();

        car1->printCarNumber();
        car2->printCarNumber();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
