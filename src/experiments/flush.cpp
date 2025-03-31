#include <iostream>
#include <chrono>
#include <thread>

inline void wait(unsigned int miliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

int main()
{
    std::cout << "Esto se imprime ahora" << std::endl;
    wait(1000);
    std::cout << "Esto se imprime luego de esperar...";
    return 0;
}