#include <iostream>
#include <string>
#include <utility>

std::string sumImpl()
{
    return ")";
}

template <typename Head, typename... Tail>
std::string sumImpl(Head head, Tail... tail)
{
    auto extendOperator = sizeof...(Tail) > 0 ? " + " : " ";
    return std::to_string(head) + extendOperator + sumImpl(tail...);
}

template <typename... Args>
std::string sum(Args... args)
{
    auto result = " = " + std::to_string((... + args));
    return "( " + sumImpl(args...) + result;
}

int main()
{

    std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;

    return 0;
}
