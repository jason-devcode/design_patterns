#include <iostream>
#include <string>
#include <memory>

// Forward declaration
class Mediator;

// Abstract base class for components
class Component {
protected:
    Mediator* mediator;

public:
    explicit Component(Mediator* mediator = nullptr) : mediator(mediator) {}
    virtual ~Component() = default;

    void setMediator(Mediator* mediator) {
        this->mediator = mediator;
    }
};

// Mediator interface
class Mediator {
public:
    virtual void notify(Component* sender, const std::string& event) const = 0;
    virtual ~Mediator() = default;
};

// Concrete components
class Button : public Component {
public:
    using Component::Component;

    void click() {
        std::cout << "Button clicked.\n";
        if (mediator) {
            mediator->notify(this, "ButtonClicked");
        }
    }
};

class TextBox : public Component {
public:
    using Component::Component;

    void setText(const std::string& text) {
        std::cout << "TextBox text set to: " << text << "\n";
        if (mediator) {
            mediator->notify(this, "TextBoxTextChanged");
        }
    }
};

class Label : public Component {
public:
    using Component::Component;

    void setText(const std::string& text) {
        std::cout << "Label text set to: " << text << "\n";
    }
};

// Concrete Mediator
class Dialog : public Mediator {
private:
    Button* button;
    TextBox* textBox;
    Label* label;

public:
    Dialog(Button* button, TextBox* textBox, Label* label)
        : button(button), textBox(textBox), label(label) {
        this->button->setMediator(this);
        this->textBox->setMediator(this);
        this->label->setMediator(this);
    }

    void notify(Component* sender, const std::string& event) const override {
        if (event == "ButtonClicked") {
            std::cout << "Mediator reacts to ButtonClicked and triggers TextBox.\n";
            textBox->setText("Button was clicked!");
        } else if (event == "TextBoxTextChanged") {
            std::cout << "Mediator reacts to TextBoxTextChanged and updates Label.\n";
            label->setText("TextBox updated!");
        }
    }
};

int main() {
    Button button;
    TextBox textBox;
    Label label;

    Dialog dialog(&button, &textBox, &label);

    button.click();
    textBox.setText("New text");

    return 0;
}
