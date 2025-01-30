#include <iostream>
#include <memory>
#include <stdexcept>

class MySingleton {
  public:
    MySingleton()=default;
    ~MySingleton()=default;
    
    static std::shared_ptr<MySingleton> getInstance() {
      if( !MySingleton::instance ) {
        MySingleton::instance = std::make_shared<MySingleton>();
      }
      return MySingleton::instance;
    }

    void greeting() {
      std::cout << "Hello, Singleton!" << std::endl;
    }
  private:
    static std::shared_ptr<MySingleton> instance;
};
std::shared_ptr<MySingleton> MySingleton::instance;


int main() {
  std::shared_ptr<MySingleton> singletonGreeting = MySingleton::getInstance();
  singletonGreeting->greeting();

  return 0;
}
