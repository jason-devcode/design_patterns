#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <map>

using std::map;
using std::endl;
using std::cout;
using std::string;
using std::function;
using std::unique_ptr;
using std::make_unique;

/**
 * Abstract Product Types
 */
class Vehicle {
  public:
    virtual void printType() const = 0;
};

class Car : public Vehicle {};
class Motorcycle : public Vehicle {};
class Airplane : public Vehicle {};

/**
 * Modern Vehicles
 */
class ModernCar : public Car {
  public:
    void printType() const override {
      cout << "Modern Car" << endl;
    }
};

class ModernMotorcycle : public Motorcycle {
  public:
    void printType() const override {
      cout << "Modern Motorcycle" << endl;
    }
};

class ModernAirplane : public Airplane {
  public:
    void printType() const override {
      cout << "Modern Airplane" << endl;
    }
};

/**
 * Classic Vehicles
 */
class ClassicCar : public Car {
  public:
    void printType() const override {
      cout << "Classic Car" << endl;
    }
};

class ClassicMotorcycle : public Motorcycle {
  public:
    void printType() const override {
      cout << "Classic Motorcycle" << endl;
    }
};

class ClassicAirplane : public Airplane {
  public:
    void printType() const override {
      cout << "Classic Airplane" << endl;
    }
};

/**
 * Sport Vehicles
 */
class SportCar : public Car {
  public:
    void printType() const override {
      cout << "Sport Car" << endl;
    }
};

class SportMotorcycle : public Motorcycle {
  public:
    void printType() const override {
      cout << "Sport Motorcycle" << endl;
    }
};

class SportAirplane : public Airplane {
  public:
    void printType() const override {
      cout << "Sport Airplane" << endl;
    }
};


/**
 * abstract vehicle factory that provide the interface to create a family of objects
 */
class VehiclesAbstractFactory {
  public:
    virtual unique_ptr<Car> createCar() const = 0;
    virtual unique_ptr<Motorcycle> createMotorcycle() const = 0;
    virtual unique_ptr<Airplane> createAirplane() const = 0;
};

/**
 * concrete factories
 */
class ModernVehiclesFactory : VehiclesAbstractFactory {
  public:
    unique_ptr<Car> createCar() { return make_unique<ModernCar>(); }
    unique_ptr<Motorcycle> createMotorcycle() { return make_unique<ModernMotorcycle>(); }
    unique_ptr<Airplane> createAirplane() { return make_unique<ModernAirplane>(); }
};

class ClassicVehiclesFactory : VehiclesAbstractFactory {
  public:
    unique_ptr<Car> createCar() { return make_unique<ClassicCar>(); }
    unique_ptr<Motorcycle> createMotorcycle() { return make_unique<ClassicMotorcycle>(); }
    unique_ptr<Airplane> createAirplane() { return make_unique<ClassicAirplane>(); }
};

class SportVehiclesFactory : VehiclesAbstractFactory {
  public:
    unique_ptr<Car> createCar() { return make_unique<SportCar>(); }
    unique_ptr<Motorcycle> createMotorcycle() { return make_unique<SportMotorcycle>(); }
    unique_ptr<Airplane> createAirplane() { return make_unique<SportAirplane>(); }
};



int main() {


  return 0;
}


