#include <iostream>
#include <memory>
#include <string>
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
    Invoker() = default;
    Invoker(SharedCommand command) : m_command(command) {}
    ~Invoker() = default;

    void executeCommand()
    {
        if (m_command != nullptr)
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
    using SharedInvoker = std::shared_ptr<Invoker>;

    Button()
    {
        m_invoker = std::make_shared<Invoker>();
    }

    Button(SharedInvoker invoker) : m_invoker(invoker) {}

    ~Button() = default;

    virtual void press()
    {
        if (m_invoker != nullptr)
            m_invoker->executeCommand();
    };

    SharedInvoker m_invoker;
};

using SharedButton = std::shared_ptr<Button>;

// ---- CONCRETE CLASSES
class OpenFileCommand : public Command
{
public:
    OpenFileCommand() = default;
    OpenFileCommand(std::string filename) : m_filename(filename) {};

    ~OpenFileCommand() = default;

    void execute() override
    {
        std::cout << "Opening file: " + m_filename + "..." << std::endl;
    }

private:
    std::string m_filename;
};

int main()
{
    SharedButton openFileButton = std::make_shared<Button>();

    Invoker::SharedCommand openLogsFile = std::make_shared<OpenFileCommand>("logs.txt");

    openFileButton->m_invoker->setCommand(openLogsFile);
    openFileButton->press();

    return 0;
}
