#include <iostream>
#include <tuple>
#include <utility>
#include <string>

template <typename Tuple, std::size_t... I>
void printTupleImpl(const Tuple &t, std::index_sequence<I...>)
{
    ((std::cout << std::get<I>(t) << std::endl), ...);
}

template <typename... Args>
void printAmountTypes()
{
    std::cout << "Types acount:" << sizeof...(Args) << std::endl;
}

template <typename... Args>
void printTuple(const std::tuple<Args...> &t)
{
    printTupleImpl(t, std::make_index_sequence<sizeof...(Args)>{});
}

template <typename... Args, std::size_t... I>
int sumImpl(std::index_sequence<I...>, Args... args)
{
    int total = sizeof...(args);
    std::string operationCollector = "( ";
    
    ((operationCollector += (std::to_string(args) + (I < (total - 1) ? " + " : " )"))), ...);

    int result = (... + args);

    operationCollector += " = " + std::to_string(result);
    std::cout << operationCollector << std::endl;
    return result;
}

template <typename... Args>
int sum(Args... args)
{
    return sumImpl(std::make_index_sequence<sizeof...(Args)>{}, args...);
}

int main()
{
    sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    // std::tuple<std::string, int> user(std::string("User123"), 23);
    // printTuple(user);

    return 0;
}
