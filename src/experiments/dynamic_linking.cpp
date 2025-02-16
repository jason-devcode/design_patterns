#include <iostream>
#include <vector>

class Graphic
{
public:
    virtual void draw() const = 0;
};

class Shape : public Graphic
{
public:
    ~Shape() = default;
    virtual void draw() const
    {
        std::cout << "Dibujando una forma" << std::endl;
    };
};

class Circle : public Shape
{
public:
    ~Circle() = default;
    void draw() const override
    {
        std::cout << "Dibujando un circulo" << std::endl;
    }
};

class Rectangle : public Shape
{
public:
    ~Rectangle() = default;
    void draw() const override
    {
        std::cout << "Dibujando un rectangulo" << std::endl;
    }
};

class Triangle : public Shape
{
public:
    ~Triangle() = default;
    void draw() const override
    {
        std::cout << "Dibujando un triangulo" << std::endl;
    }
};

class CompoundGraphic : public Graphic
{
public:
    void draw() const override
    {
        for (Graphic *const g : graphics)
        {
            g->draw();
        }
    }

    void add_graphic(Shape *graphic)
    {
        if (graphic == nullptr)
            return;
        this->graphics.push_back(graphic);
    }
    ~CompoundGraphic()
    {
        for (Graphic *g : graphics)
        {
            if (g == nullptr)
                continue;
            ;
            delete g;
        }
    }
    std::vector<Shape *> graphics;
};

class ShapeExporter
{
public:
    void export_shape(Shape *shape)
    {
        std::cout << "exportando forma" << std::endl;
    }

    void export_shape(Circle *circle)
    {
        std::cout << "exportando circulo" << std::endl;
    }

    void export_shape(Rectangle *rectangle)
    {
        std::cout << "exportando rectangulo" << std::endl;
    }

    void export_shape(Triangle *triangle)
    {
        std::cout << "exportando triangulo" << std::endl;
    }
};


void export_shapes_to_xml(CompoundGraphic &cg)
{
    ShapeExporter se;
    for (Shape *g : cg.graphics)
    {
        se.export_shape(g);
    }
}

int main()
{
    CompoundGraphic cg;
    cg.add_graphic(new Circle());
    cg.add_graphic(new Rectangle());
    cg.add_graphic(new Triangle());

    export_shapes_to_xml(cg);

    cg.draw();

    return 0;
}
