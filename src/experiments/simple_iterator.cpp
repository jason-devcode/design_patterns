#include <iostream>
#include <stdexcept>

template <typename ElementType>
class Vector
{
public:
    Vector(std::size_t size) : size(size), elements(new ElementType[size]) {}

    ~Vector() { delete[] elements; }

    std::size_t getSize() const { return size; }

    ElementType &operator[](int index)
    {
        if (index >= 0 && index < size)
            return elements[index];
        else
            throw std::out_of_range("Index out of range");
    }

    const ElementType &operator[](int index) const
    {
        if (index >= 0 && index < size)
            return elements[index];
        else
            throw std::out_of_range("Index out of range");
    }

    class Iterator
    {
    public:
        Iterator(Vector &vec, int index = 0) : m_vec(vec), cur_index(index) {}

        ElementType &operator*() const { return m_vec[cur_index]; }

        Iterator &operator++()
        {
            ++cur_index;
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return cur_index != other.cur_index;
        }

    private:
        Vector<ElementType> &m_vec;
        int cur_index;
    };

    Iterator begin() { return Iterator(*this, 0); }
    Iterator end() { return Iterator(*this, size); }

private:
    ElementType *elements;
    std::size_t size;
};

int main()
{
    Vector<float> v(10);
    int i = 0;
    for (float &e : v)
    {
        e = i++;
    }

    for (const float &e : v)
    {
        std::cout << e << std::endl;
    }

    return 0;
}