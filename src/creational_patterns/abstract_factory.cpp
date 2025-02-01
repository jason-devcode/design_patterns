/**
 * @file abstract_factory.cpp
 * @brief Implementation of the Abstract Factory pattern for vehicles.
 */

#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <map>
#include <stdexcept>

/**
 * @class Vehicle
 * @brief Abstract base class for all vehicles.
 */
class Vehicle
{
public:
  virtual ~Vehicle() = default;
  virtual void printType() const = 0;
};

/***********************************
 * Abstract Vehicle Types
 ***********************************/
class Car : public Vehicle
{
};
class Motorcycle : public Vehicle
{
};
class Airplane : public Vehicle
{
};

/***********************************
 * Concrete Vehicle Types
 ***********************************/

/**
 * Modern Vehicles
 */
class ModernCar : public Car
{
public:
  void printType() const override
  {
    std::cout << "Modern Car" << std::endl;
  }
};

class ModernMotorcycle : public Motorcycle
{
public:
  void printType() const override
  {
    std::cout << "Modern Motorcycle" << std::endl;
  }
};

class ModernAirplane : public Airplane
{
public:
  void printType() const override
  {
    std::cout << "Modern Airplane" << std::endl;
  }
};

/**
 * Classic Vehicles
 */
class ClassicCar : public Car
{
public:
  void printType() const override
  {
    std::cout << "Classic Car" << std::endl;
  }
};

class ClassicMotorcycle : public Motorcycle
{
public:
  void printType() const override
  {
    std::cout << "Classic Motorcycle" << std::endl;
  }
};

class ClassicAirplane : public Airplane
{
public:
  void printType() const override
  {
    std::cout << "Classic Airplane" << std::endl;
  }
};

/**
 * Sport Vehicles
 */
class SportCar : public Car
{
public:
  void printType() const override
  {
    std::cout << "Sport Car" << std::endl;
  }
};

class SportMotorcycle : public Motorcycle
{
public:
  void printType() const override
  {
    std::cout << "Sport Motorcycle" << std::endl;
  }
};

class SportAirplane : public Airplane
{
public:
  void printType() const override
  {
    std::cout << "Sport Airplane" << std::endl;
  }
};

/**
 * @class VehicleAbstractFactory
 * @brief Abstract factory interface for creating families of vehicle objects.
 */
class VehicleAbstractFactory
{
public:
  virtual ~VehicleAbstractFactory() = default; // Virtual destructor

  virtual std::unique_ptr<Car> createCar() const
  {
    throw std::runtime_error("Error: createCar() is not implemented.");
  }

  virtual std::unique_ptr<Motorcycle> createMotorcycle() const
  {
    throw std::runtime_error("Error: createMotorcycle() is not implemented.");
  }

  virtual std::unique_ptr<Airplane> createAirplane() const
  {
    throw std::runtime_error("Error: createAirplane() is not implemented.");
  }
};

/***********************************
 * Concrete Factories
 ***********************************/

/**
 * @class ModernVehicleFactory
 * @brief Concrete factory for creating modern vehicles.
 */
class ModernVehicleFactory : public VehicleAbstractFactory
{
public:
  std::unique_ptr<Car> createCar() const override { return std::make_unique<ModernCar>(); }
  std::unique_ptr<Motorcycle> createMotorcycle() const override { return std::make_unique<ModernMotorcycle>(); }
  std::unique_ptr<Airplane> createAirplane() const override { return std::make_unique<ModernAirplane>(); }
};

class ClassicVehicleFactory : public VehicleAbstractFactory
{
public:
  std::unique_ptr<Car> createCar() const override { return std::make_unique<ClassicCar>(); }
  std::unique_ptr<Motorcycle> createMotorcycle() const override { return std::make_unique<ClassicMotorcycle>(); }
  std::unique_ptr<Airplane> createAirplane() const override { return std::make_unique<ClassicAirplane>(); }
};

class SportVehicleFactory : public VehicleAbstractFactory
{
public:
  std::unique_ptr<Car> createCar() const override { return std::make_unique<SportCar>(); }
  std::unique_ptr<Motorcycle> createMotorcycle() const override { return std::make_unique<SportMotorcycle>(); }
  std::unique_ptr<Airplane> createAirplane() const override { return std::make_unique<SportAirplane>(); }
};

/***********************************
 * Factories Management Utils
 ***********************************/

/**
 * @enum VehicleFactoryType
 * @brief Enum representing the different types of vehicle factories.
 */
enum class VehicleFactoryType
{
  MODERN,
  CLASSIC,
  SPORT
};

/**
 * Defining Vehicle Factories Management used to avoid concrete associations
 * between concrete factories and client code.
 */

/**
 * @typedef VehicleFactoryFunction
 * @brief Alias for a function that creates an instance of a concrete vehicle factory.
 */
using VehicleFactoryFunction = std::function<std::unique_ptr<VehicleAbstractFactory>()>;

/**
 * @typedef MapVehicleFactories
 * @brief Type definition for a map of factory functions.
 */
using MapVehicleFactories = std::map<VehicleFactoryType, VehicleFactoryFunction>;


/**
 * @brief Creates a vehicle factory instance.
 * 
 * This template function creates a `VehicleAbstractFactory` instance using the specified
 * concrete factory class.
 * 
 * @tparam FactoryType Concrete factory class type that inherits from `VehicleAbstractFactory`.
 * 
 * @return A unique pointer to the requested concrete factory instance.
 */
template <typename FactoryType>
std::unique_ptr<VehicleAbstractFactory> createFactory()
{
  return std::make_unique<FactoryType>();
}

/**
 * @class VehicleFactoryManagement
 * @brief Manages the registration and retrieval of vehicle factories.
 */
class VehicleFactoryManagement
{
public:
  /**
   * @brief Registers all concrete vehicle factories.
   */
  static void registerAllVehicleFactories()
  {
    factories[VehicleFactoryType::SPORT] = createFactory<SportVehicleFactory>;
    factories[VehicleFactoryType::MODERN] = createFactory<ModernVehicleFactory>;
    factories[VehicleFactoryType::CLASSIC] = createFactory<ClassicVehicleFactory>;
  }

  /**
   * @brief Retrieves a factory instance based on the provided key.
   * @param factoryKey The type of factory to retrieve.
   * @return A unique pointer to the factory instance.
   */
  static std::unique_ptr<VehicleAbstractFactory> getFactory(VehicleFactoryType factoryKey)
  {
    auto factoryIterator = factories.find(factoryKey);

    if (factoryIterator == factories.end())
      throw std::runtime_error("Error: Cannot find this factory type.");

    auto factoryLambda = factoryIterator->second;

    if (!factoryLambda)
      throw std::runtime_error("Error: This factory lambda is unavailable.");

    return factoryLambda();
  }

private:
  static MapVehicleFactories factories;
};
// initializing static member
MapVehicleFactories VehicleFactoryManagement::factories;

/**
 * @brief Initializes the vehicle factories.
 */
void initializeAll()
{
  VehicleFactoryManagement::registerAllVehicleFactories();
}

/**
 * @brief Main function demonstrating the use of the abstract factory pattern.
 * @return Execution status.
 */
int main()
{
  try
  {
    initializeAll();

    std::unique_ptr<VehicleAbstractFactory> factorySelected = VehicleFactoryManagement::getFactory(VehicleFactoryType::MODERN);

    std::unique_ptr<Car> car = factorySelected->createCar();
    std::unique_ptr<Motorcycle> motorcycle = factorySelected->createMotorcycle();
    std::unique_ptr<Airplane> airplane = factorySelected->createAirplane();

    car->printType();
    motorcycle->printType();
    airplane->printType();
  }
  catch (const std::runtime_error &error)
  {
    std::cerr << error.what() << std::endl;
  }
  catch (const std::exception &unknown_error)
  {
    std::cerr << unknown_error.what() << std::endl;
  }

  return 0;
}
