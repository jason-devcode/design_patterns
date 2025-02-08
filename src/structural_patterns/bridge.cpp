#include <memory>
#include <iostream>
#include <stdexcept>

class Notification {
public:
    virtual void showMessage() const = 0;
    virtual ~Notification() = default;
};

class TextNotification : public Notification {
public:
    void showMessage() const override {
        std::cout << "Text Notification sent!" << std::endl;
    }
};

class EmailNotification : public Notification {
public:
    void showMessage() const override {
        std::cout << "Email Notification sent!" << std::endl;
    }
};

class CommunicationChannel {
protected:
    std::unique_ptr<Notification> notification;
public:
    CommunicationChannel(std::unique_ptr<Notification> notif) : notification(std::move(notif)) {}
    virtual void sendNotification() = 0;
    virtual ~CommunicationChannel() = default;
};

class EmailChannel : public CommunicationChannel {
public:
    EmailChannel(std::unique_ptr<Notification> notif) : CommunicationChannel(std::move(notif)) {}
    void sendNotification() override {
        std::cout << "Sending via Email..." << std::endl;
        notification->showMessage();
    }
};

class SMSChannel : public CommunicationChannel {
public:
    SMSChannel(std::unique_ptr<Notification> notif) : CommunicationChannel(std::move(notif)) {}
    void sendNotification() override {
        std::cout << "Sending via SMS..." << std::endl;
        notification->showMessage();
    }
};

int main() {
    std::unique_ptr<Notification> emailNotif = std::make_unique<EmailNotification>();
    std::unique_ptr<CommunicationChannel> emailChannel = std::make_unique<EmailChannel>(std::move(emailNotif));
    emailChannel->sendNotification();
    
    std::unique_ptr<Notification> textNotif = std::make_unique<TextNotification>();
    std::unique_ptr<CommunicationChannel> smsChannel = std::make_unique<SMSChannel>(std::move(textNotif));
    smsChannel->sendNotification();
    
    return 0;
}
