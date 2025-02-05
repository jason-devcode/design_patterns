#include <iostream>

class File {};

class XMLFile : public File {
    public:
        ~XMLFile()=default;

};

class JSONFile : public File {
    public:
        ~JSONFile()=default;

};



int main() {


    return 0;
}
