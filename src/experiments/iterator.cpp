#include <iostream>
#include <vector>

template <typename T>
class Iterator
{
public:
    ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual T &getNext() = 0;
};

class PlaceableObject
{
public:
    PlaceableObject(float x = 0, float y = 0) : m_x(x), m_y(y) {}

    ~PlaceableObject() = default;

    PlaceableObject &setCoordinateValues(float x, float y)
    {
        m_x = x;
        m_y = y;
        return *this;
    }

    PlaceableObject &setX(float x)
    {
        m_x = x;
        return *this;
    }

    PlaceableObject &setY(float y)
    {
        m_y = y;
        return *this;
    }

    float getX() const { return m_x; }
    float getY() const { return m_y; }

private:
    float m_x, m_y;
};

class Entity : PlaceableObject
{
public:
    Entity() = default;
    ~Entity() = default;
};

class GridMapCell
{
public:
    using ObjectsVector = std::vector<PlaceableObject &>;
    using Iterator = ObjectsVector::iterator;

    GridMapCell() = default;
    ~GridMapCell() = default;

    void appendObject(PlaceableObject &object)
    {
        objects.push_back(object);
    }

    Iterator begin() { return objects.begin(); }
    Iterator end() { return objects.begin(); }

private:
    std::vector<PlaceableObject &> objects;
};

int main()
{
    Entity *player;
    player->setX(10.0f).setY(15.0f);

    return 0;
}
