#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>

int main()
{

    try
    {
    }
    catch (const std::exception &error)
    {
        std::cout << error.what() << std::endl;
    }

    return 0;
}
