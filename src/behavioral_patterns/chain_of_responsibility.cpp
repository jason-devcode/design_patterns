#include <iostream>
#include <memory>

template <typename ReturnT>
class Handler
{
public:
    virtual void setNextHandler(Handler *nextHandler) = 0;
    virtual ReturnT handler() = 0;
};

template <typename ReturnT>
class BaseHandler : public Handler<ReturnT>
{
public:
    void setNextHandler(Handler<ReturnT> *nextHandler) override
    {
        this->nextHandler = nextHandler;
    }
    virtual ReturnT handler() override
    {
        return this->nextHandler->handler();
    }

protected:
    Handler<ReturnT> *nextHandler;
};

class ConcreteIntHandler : public BaseHandler<int>
{
public:
    int handler() override
    {
        if (this->nextHandler != nullptr)
            return this->nextHandler->handler() + 2;

        return 2;
    }
};

int main()
{
    ConcreteIntHandler *c1 = new ConcreteIntHandler();
    ConcreteIntHandler *c2 = new ConcreteIntHandler();
    ConcreteIntHandler *c3 = new ConcreteIntHandler();
    ConcreteIntHandler *c4 = new ConcreteIntHandler();

    c1->setNextHandler(c2);
    c2->setNextHandler(c3);
    c3->setNextHandler(c4);

    std::cout << "Output: " << c1->handler() << std::endl;

    return 0;
}
