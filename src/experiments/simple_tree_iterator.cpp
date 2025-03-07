#include <iostream>
#include <memory>
#include <stdexcept>

template <typename DataType>
class BinaryTree
{
public: // inner classes
    class TreeNode;
    class Iterator;

public: // interface
    virtual void insertData() = 0;

private:
    std::shared_ptr<TreeNode> root = nullptr;
};

template <typename DataType>
class BinaryTree<DataType>::TreeNode
{
public:
    using SharedNode = std::shared_ptr<TreeNode>;

    TreeNode() = default;
    TreeNode(DataType data) : m_data(data) {};
    ~TreeNode() = default;

    void setData(DataType data)
    {
        m_data = data;
    }

    void setParentNode(SharedNode parentNode) { parent = parentNode; }
    void insertLeftChildNode(SharedNode leftNode) { leftChild = leftNode; }
    void insertRightChildNode(SharedNode rightNode) { rightChild = rightNode; }

    SharedNode getLeftNode() const
    {
        return leftChild;
    }

    SharedNode getRightNode() const
    {
        return rightChild;
    }

    DataType getData() const
    {
        return m_data;
    }

private:
    SharedNode parent = nullptr;
    SharedNode leftChild = nullptr;
    SharedNode rightChild = nullptr;

private:
    DataType m_data;
};

template <typename DataType>
class BinaryTree<DataType>::Iterator
{
};

using TreeFloats = BinaryTree<float>;

int main()
{
    try
    {
        std::unique_ptr<TreeFloats> tree = std::make_unique<TreeFloats>();
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}
