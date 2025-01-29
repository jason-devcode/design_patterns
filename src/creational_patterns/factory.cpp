#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <stdexcept>

enum class VehicleType {
  CAR,
  MOTORCYCLE,
};

class Vehicle {
  public:
    Vehicle()=default;
    ~Vehicle()=default;
    virtual void printVehicleType() const = 0;
};

class Motorcycle : public Vehicle {
  public:
    Motorcycle()=default;
    ~Motorcycle()=default;

    void printVehicleType() const override {
      std::cout << "Motorcycle" << std::endl;
    }
};

class Car : public Vehicle {
  public:
    Car()=default;
    ~Car()=default;

    void printVehicleType() const override {
      std::cout << "Car" << std::endl;
    }
};

using AbstractVehicleCreatorFunction = std::function<std::unique_ptr<Vehicle>()>;

using MapConcreteVehicleFactory = std::map<VehicleType, AbstractVehicleCreatorFunction>;

#define REGISTER_FACTORY_LAMBDA( factories_map, keyType, ConcreteClassType )\
  factories_map[ keyType ] = []() -> std::unique_ptr<ConcreteClassType> { return std::make_unique<ConcreteClassType>(); }

class VehicleFactoriesManagement {
  public:
    /**
     * Static method to register all concrete lambda factories in a map register.
     *
     * TODO: Modify this to add or remove concrete types.
     */
    static void registerAllFactories() {
      MapConcreteVehicleFactory& vehicles_factories = VehicleFactoriesManagement::factories;
      REGISTER_FACTORY_LAMBDA( vehicles_factories, VehicleType::CAR, Car );
      REGISTER_FACTORY_LAMBDA( vehicles_factories, VehicleType::MOTORCYCLE, Motorcycle );
    }

    /**
     * Static Method to get a factory lambda to make an unique pointer to an instance of a concrete class.
     */
    static AbstractVehicleCreatorFunction getVehicleFactory(VehicleType vehicleType) {
      auto it = VehicleFactoriesManagement::factories.find(vehicleType);
      if (it != VehicleFactoriesManagement::factories.end()) {
        return it->second;
      }
      throw std::runtime_error("Factory not found for vehicle type");
    }

  private:
    static MapConcreteVehicleFactory factories;
};
MapConcreteVehicleFactory VehicleFactoriesManagement::factories;

class VehicleFactory {
  public:
    static std::unique_ptr<Vehicle> createVehicle(VehicleType vehicleType) {
      auto factoryLambda = VehicleFactoriesManagement::getVehicleFactory( vehicleType );
      return factoryLambda();
    }
};

void initializeFactories() {
  VehicleFactoriesManagement::registerAllFactories();
}

int main() {
  try {
    initializeFactories();

    auto car = VehicleFactory::createVehicle(VehicleType::CAR);
    car->printVehicleType();

    auto motorcycle = VehicleFactory::createVehicle(VehicleType::MOTORCYCLE);
    motorcycle->printVehicleType();
  }
  catch ( const std::runtime_error runTimeError ) {
    std::cerr << runTimeError.what() << std::endl;
  }
  catch ( const std::exception& unknown_error ) {
    std::cerr << unknown_error.what() << std::endl;
  }
  return 0;
}

