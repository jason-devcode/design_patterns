#include <iostream>
#include <memory>
#include <stdexcept>

class Command
{
public:
    virtual void execute() = 0;
};

class Invoker
{
public:
    using SharedCommand = std::shared_ptr<Command>;

    ~Invoker() = default;
    void executeCommand()
    {
        m_command->execute();
    }

    void setCommand(SharedCommand command)
    {
        m_command = command;
    }

private:
    SharedCommand m_command;
};

class Button
{
public:
    ~Button() = default;
    virtual void press() = 0;
};

int main()
{

    return 0;
}
