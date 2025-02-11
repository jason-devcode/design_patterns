#include <iostream>
#include <memory>

// Base class for all drinks
class Drink
{
public:
    virtual ~Drink() = default;
    virtual float getPrice() const = 0;
};

// Concrete drink: Coffee
class Coffee : public Drink
{
public:
    float getPrice() const override
    {
        return 20.0f;
    }
};

// Base decorator class
class DrinkDecorator : public Drink
{
protected:
    std::unique_ptr<Drink> drink; // Using smart pointers to avoid memory leaks

public:
    DrinkDecorator(std::unique_ptr<Drink> d) : drink(std::move(d)) {}
    virtual float getPrice() const override
    {
        return drink->getPrice();
    }
};

// Decorator to add Milk
class Milk : public DrinkDecorator
{
public:
    Milk(std::unique_ptr<Drink> d) : DrinkDecorator(std::move(d)) {}
    float getPrice() const override
    {
        return drink->getPrice() + 5.0f;
    }
};

// Decorator to add Chocolate
class Chocolate : public DrinkDecorator
{
public:
    Chocolate(std::unique_ptr<Drink> d) : DrinkDecorator(std::move(d)) {}
    float getPrice() const override
    {
        return drink->getPrice() + 7.0f;
    }
};

// Decorator to add Cinnamon
class Cinnamon : public DrinkDecorator
{
public:
    Cinnamon(std::unique_ptr<Drink> d) : DrinkDecorator(std::move(d)) {}
    float getPrice() const override
    {
        return drink->getPrice() + 3.0f;
    }
};

int main()
{
    // Create a base coffee
    std::unique_ptr<Drink> myDrink = std::make_unique<Coffee>();

    // Add milk
    myDrink = std::make_unique<Milk>(std::move(myDrink));

    // Add chocolate
    myDrink = std::make_unique<Chocolate>(std::move(myDrink));

    // Add cinnamon
    myDrink = std::make_unique<Cinnamon>(std::move(myDrink));

    // Display final price
    std::cout << "Final price: $" << myDrink->getPrice() << std::endl;

    return 0;
}
