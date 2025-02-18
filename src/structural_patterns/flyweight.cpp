#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>

class Texture
{
public:
    Texture(int width, int height, std::string texture_name) 
        : m_width(width), m_height(height), m_texture_name(texture_name) {}

    void print_texture_info() const
    {
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "Texture name: " << m_texture_name << std::endl;
        std::cout << "Dimensions: " << m_width << "x" << m_height << " pixels" << std::endl;
        std::cout << std::string(40, '-') << std::endl;
    }

private:
    int m_width;
    int m_height;
    std::string m_texture_name;
};

class TextureFactory
{
public:
    static std::shared_ptr<Texture> get_texture(const std::string &name, int width, int height)
    {
        std::string key = name + "_" + std::to_string(width) + "x" + std::to_string(height);

        if (textures.find(key) == textures.end())
        {
            textures[key] = std::make_shared<Texture>(width, height, name);
        }

        return textures[key];
    }

private:
    static std::map<std::string, std::shared_ptr<Texture>> textures;
};

std::map<std::string, std::shared_ptr<Texture>> TextureFactory::textures;

class GameObject
{
public:
    GameObject(const std::string &name, const std::string &texture_name, int width, int height)
        : m_name(name), m_texture(TextureFactory::get_texture(texture_name, width, height)) {}

    void draw() const
    {
        std::cout << "Drawing object: " << m_name << std::endl;
        m_texture->print_texture_info();
    }

private:
    std::string m_name;
    std::shared_ptr<Texture> m_texture; // Flyweight
};

int main()
{
    GameObject tree1("Tree_1", "TreeTexture", 256, 256);
    GameObject tree2("Tree_2", "TreeTexture", 256, 256);
    GameObject rock("Rock_1", "RockTexture", 128, 128);

    tree1.draw();
    tree2.draw();
    rock.draw();

    return 0;
}
