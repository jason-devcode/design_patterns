#include <iostream>
#include <vector>
#include <memory>

// Base Component
class FileSystemComponent {
public:
    virtual void show(int depth = 0) const = 0;
    virtual ~FileSystemComponent() {}
};

// Leaf: File
class File : public FileSystemComponent {
private:
    std::string name;
public:
    File(const std::string& name) : name(name) {}
    void show(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "[File] " << name << std::endl;
    }
};

// Composite: Folder
class Folder : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
public:
    Folder(const std::string& name) : name(name) {}
    void add(std::shared_ptr<FileSystemComponent> component) {
        children.push_back(component);
    }
    void show(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "[Folder] " << name << std::endl;
        for (const auto& child : children) {
            child->show(depth + 2);
        }
    }
};

int main() {
    auto root = std::make_shared<Folder>("Root");
    auto folder1 = std::make_shared<Folder>("Documents");
    auto folder2 = std::make_shared<Folder>("Pictures");
    
    auto file1 = std::make_shared<File>("file1.txt");
    auto file2 = std::make_shared<File>("file2.docx");
    auto file3 = std::make_shared<File>("image1.png");
    
    folder1->add(file1);
    folder1->add(file2);
    folder2->add(file3);
    
    root->add(folder1);
    root->add(folder2);
    
    root->show();
    return 0;
}
