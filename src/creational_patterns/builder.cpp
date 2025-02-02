#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

/**
 * @class Burger
 * @brief Represents a burger with various ingredients.
 */
class Burger
{
private:
    std::string bun;
    std::string meat;
    std::string cheese;
    std::vector<std::string> vegetables;
    std::vector<std::string> sauces;

public:
    /**
     * @brief Constructs a Burger with specified ingredients.
     * @param bun Type of bun.
     * @param meat Type of meat.
     * @param cheese Type of cheese.
     * @param vegetables List of vegetables.
     * @param sauces List of sauces.
     */
    Burger(const std::string &bun, const std::string &meat, const std::string &cheese,
           const std::vector<std::string> &vegetables, const std::vector<std::string> &sauces)
        : bun(bun), meat(meat), cheese(cheese), vegetables(vegetables), sauces(sauces) {}

    /**
     * @brief Displays the burger details.
     */
    void display() const;

    friend class BurgerBuilder;
};

/**
 * @brief Prints burger composition.
 */
void Burger::display() const
{
    std::cout << "Burger with " << bun << ", " << meat << ", " << cheese;

    if (!vegetables.empty())
    {
        std::cout << ", Vegetables: ";
        for (const auto &v : vegetables)
            std::cout << v << " ";
    }

    if (!sauces.empty())
    {
        std::cout << ", Sauces: ";
        for (const auto &s : sauces)
            std::cout << s << " ";
    }

    std::cout << std::endl;
}

/**
 * @class BurgerBuilder
 * @brief Abstract builder class for creating Burger objects.
 */
class BurgerBuilder
{
public:
    virtual ~BurgerBuilder() = default;

    /// Sets the bun type.
    virtual BurgerBuilder &setBun(const std::string &bunType) = 0;

    /// Sets the meat type.
    virtual BurgerBuilder &setMeat(const std::string &meatType) = 0;

    /// Sets the cheese type.
    virtual BurgerBuilder &setCheese(const std::string &cheeseType) = 0;

    /// Adds a vegetable.
    virtual BurgerBuilder &addVegetable(const std::string &vegetable) = 0;

    /// Adds a sauce.
    virtual BurgerBuilder &addSauce(const std::string &sauce) = 0;

    /// Builds and returns a unique pointer to a Burger.
    virtual std::unique_ptr<Burger> build() = 0;
};

/**
 * @class ConcreteBurgerBuilder
 * @brief Implements BurgerBuilder to create custom burgers.
 */
class ConcreteBurgerBuilder : public BurgerBuilder
{
protected:
    std::string bun = "Classic Bun";
    std::string meat = "Beef";
    std::string cheese = "Cheddar";
    std::vector<std::string> vegetables;
    std::vector<std::string> sauces;

public:
    BurgerBuilder &setBun(const std::string &bunType) override;
    BurgerBuilder &setMeat(const std::string &meatType) override;
    BurgerBuilder &setCheese(const std::string &cheeseType) override;
    BurgerBuilder &addVegetable(const std::string &vegetable) override;
    BurgerBuilder &addSauce(const std::string &sauce) override;
    std::unique_ptr<Burger> build() override;
};

BurgerBuilder &ConcreteBurgerBuilder::setBun(const std::string &bunType)
{
    if (bunType.empty())
        throw std::invalid_argument("Bun type cannot be empty");
    bun = bunType;
    return *this;
}

BurgerBuilder &ConcreteBurgerBuilder::setMeat(const std::string &meatType)
{
    if (meatType.empty())
        throw std::invalid_argument("Meat type cannot be empty");
    meat = meatType;
    return *this;
}

BurgerBuilder &ConcreteBurgerBuilder::setCheese(const std::string &cheeseType)
{
    if (cheeseType.empty())
        throw std::invalid_argument("Cheese type cannot be empty");
    cheese = cheeseType;
    return *this;
}

BurgerBuilder &ConcreteBurgerBuilder::addVegetable(const std::string &vegetable)
{
    if (vegetable.empty())
        throw std::invalid_argument("Vegetable name cannot be empty");
    vegetables.push_back(vegetable);
    return *this;
}

BurgerBuilder &ConcreteBurgerBuilder::addSauce(const std::string &sauce)
{
    if (sauce.empty())
        throw std::invalid_argument("Sauce name cannot be empty");
    sauces.push_back(sauce);
    return *this;
}

std::unique_ptr<Burger> ConcreteBurgerBuilder::build()
{
    return std::make_unique<Burger>(bun, meat, cheese, vegetables, sauces);
}

/**
 * @class Director
 * @brief Manages burger creation using a builder.
 */
class Director
{
private:
    BurgerBuilder *builder;

public:
    /**
     * @brief Sets the builder to use.
     * @param newBuilder Pointer to a BurgerBuilder instance.
     */
    void setBuilder(BurgerBuilder *newBuilder);

    /**
     * @brief Constructs a classic burger.
     * @return A unique pointer to the created Burger.
     */
    std::unique_ptr<Burger> constructClassicBurger();

    /**
     * @brief Constructs a custom burger.
     * @return A unique pointer to the created Burger.
     */
    std::unique_ptr<Burger> constructCustomBurger();
};

void Director::setBuilder(BurgerBuilder *newBuilder)
{
    builder = newBuilder;
}

std::unique_ptr<Burger> Director::constructClassicBurger()
{
    return builder->setBun("Sesame Bun")
        .setMeat("Beef")
        .setCheese("Cheddar")
        .addVegetable("Lettuce")
        .addVegetable("Tomato")
        .addSauce("Mayonnaise")
        .addSauce("Ketchup")
        .build();
}

std::unique_ptr<Burger> Director::constructCustomBurger()
{
    return builder->setBun("Artisan Bun")
        .setMeat("Grilled Chicken")
        .setCheese("Gouda")
        .addVegetable("Pickles")
        .addSauce("Mustard")
        .build();
}

/**
 * @brief Entry point of the application.
 * @return Program exit status.
 */
int main()
{
    try
    {
        Director director;
        std::unique_ptr<BurgerBuilder> builder = std::make_unique<ConcreteBurgerBuilder>();

        director.setBuilder(builder.get());

        auto classicBurger = director.constructClassicBurger();
        classicBurger->display();

        auto customBurger = director.constructCustomBurger();
        customBurger->display();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
