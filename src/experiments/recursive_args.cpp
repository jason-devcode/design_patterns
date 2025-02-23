#include <iostream>

std::size_t sum_impl() {
    return 0;
}

template<typename T, typename... Rest>
std::size_t sum_impl(T value, Rest... rest) {
    return value + sum_impl(rest...);
}

template<std::size_t... I>
std::size_t sum() {
    return sum_impl(I...);
}

int main() {
    std::cout << sum<1,2,3,4,5,6,7,8,9,10>() << std::endl;
    return 0;
}
