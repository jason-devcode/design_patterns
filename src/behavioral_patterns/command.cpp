#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>

/**
 * Text editor that supports text insertion and undo/redo functionality.
 */
class TextEditor {
public:
    const std::string& getText() const {
        return m_text;
    }
    
    void setText(const std::string& text) {
        m_text = text;
    }
    
    void insertText(const std::string& text) {
        m_text += text;
    }
    
private:
    std::string m_text;
};

/**
 * Command interface: declares the execute and undo operations.
 */
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

/**
 * Concrete command to insert text into the editor.
 */
class InsertCommand : public Command {
public:
    InsertCommand(std::shared_ptr<TextEditor> editor, const std::string& text)
        : m_editor(editor), m_text(text) {}

    void execute() override {
        // Save the previous state for undo purposes.
        m_prevState = m_editor->getText();
        m_editor->insertText(m_text);
    }

    void undo() override {
        // Restore the previous state.
        m_editor->setText(m_prevState);
    }
    
private:
    std::shared_ptr<TextEditor> m_editor;
    std::string m_text;
    std::string m_prevState;
};

/**
 * CommandManager (Invoker): Manages command execution, undo, and redo.
 */
class CommandManager {
public:
    void executeCommand(std::unique_ptr<Command> cmd) {
        cmd->execute();
        m_undoStack.push(std::move(cmd));
        // Clear the redo stack when executing a new command.
        while (!m_redoStack.empty()) {
            m_redoStack.pop();
        }
    }
    
    void undo() {
        if (m_undoStack.empty()) {
            throw std::runtime_error("No commands to undo.");
        }
        auto cmd = std::move(m_undoStack.top());
        m_undoStack.pop();
        cmd->undo();
        m_redoStack.push(std::move(cmd));
    }
    
    void redo() {
        if (m_redoStack.empty()) {
            throw std::runtime_error("No commands to redo.");
        }
        auto cmd = std::move(m_redoStack.top());
        m_redoStack.pop();
        cmd->execute();
        m_undoStack.push(std::move(cmd));
    }
    
private:
    std::stack<std::unique_ptr<Command>> m_undoStack;
    std::stack<std::unique_ptr<Command>> m_redoStack;
};

int main() {
    auto editor = std::make_shared<TextEditor>();
    CommandManager manager;
    
    // Execute an insert command.
    manager.executeCommand(std::make_unique<InsertCommand>(editor, "Hello "));
    manager.executeCommand(std::make_unique<InsertCommand>(editor, "world!"));
    
    std::cout << "Current text: " << editor->getText() << std::endl;
    
    // Undo the last action.
    manager.undo();
    std::cout << "After undo: " << editor->getText() << std::endl;
    
    // Redo the undone action.
    manager.redo();
    std::cout << "After redo: " << editor->getText() << std::endl;
    
    return 0;
}
