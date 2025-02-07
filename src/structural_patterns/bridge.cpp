#include <memory>
#include <iostream>
#include <stdexcept>


class Notification {};

class CommunicationChannel {
    public:
        
        virtual void sendNotification( Notification notification ) = 0;
};


int main() {



    return 0;
}
