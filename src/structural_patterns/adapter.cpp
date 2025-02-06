#include <iostream>
#include <memory>
#include <stdexcept>

// Base class for File
class File
{
public:
    virtual ~File() = default;
};

// Derived class for XMLFile
class XMLFile : public File
{
public:
    ~XMLFile() = default;

    void display() const
    {
        std::cout << "This is an XML file." << std::endl;
    }
};

// Derived class for JSONFile
class JSONFile : public File
{
public:
    ~JSONFile() = default;

    void display() const
    {
        std::cout << "This is a JSON file." << std::endl;
    }
};

// Adapter class to convert XML to JSON
class XMLtoJSONAdapter
{
public:
    ~XMLtoJSONAdapter() = default;

    std::unique_ptr<JSONFile> convert(std::unique_ptr<XMLFile> xmlFile)
    {
        // Convert XMLFile to JSONFile
        std::cout << "Converting XML to JSON..." << std::endl;
        return std::make_unique<JSONFile>();
    }
};

int main()
{
    // Create an XML file
    std::unique_ptr<XMLFile> xmlFile = std::make_unique<XMLFile>();

    // Create an adapter and convert the XML file to JSON
    XMLtoJSONAdapter adapter;

    // convert xml file to json file
    std::unique_ptr<JSONFile> jsonFile = adapter.convert(std::move(xmlFile));

    // Display the content of the JSON file
    jsonFile->display();

    return 0;
}
