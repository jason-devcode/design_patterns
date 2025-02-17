#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>

// Simulates a texture data
class Texture
{
public:
    Texture() = default;
    Texture(int width, int height, std::string texture_name) : m_width(width), m_height(height), m_texture_name(texture_name) {}
    ~Texture() = default;

    int get_width() const
    {
        return m_width;
    }
    int get_height() const
    {
        return m_height;
    }
    std::string get_name() const
    {
        return m_texture_name;
    }

    void print_texture_info() const
    {
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "Texture name: " << this->get_name() << std::endl;
        std::cout << "Dimensions: " << this->get_width() << "x" << this->get_height() << " pixels" << std::endl;
        std::cout << std::string(40, '-') << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &out, const Texture &tex)
    {
        tex.print_texture_info();
        return out;
    }

protected:
    int m_width;
    int m_height;
    std::string m_texture_name;
};

using TextureDictionary = std::map<int, Texture>;

// Model Mesh simulate
class Mesh3D
{
public:
protected:
};

int main()
{
    Texture tex(512, 512, "bricks");

    std::cout << tex;

    return 0;
}
