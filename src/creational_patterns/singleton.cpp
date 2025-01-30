#include <iostream>
#include <memory>
#include <stdexcept>

class MySingleton {
  public:
    MySingleton()=default;
    ~MySingleton()=default;
    
    // method to instantiate(if is not already instantiate) and get singleton instance
    static std::shared_ptr<MySingleton> getInstance() {
      if( !instance ) {
        instance = std::make_shared<MySingleton>();
      }
      return instance;
    }
    
    // a test method to test singleton instance
    void greeting() {
      std::cout << "Hello, Singleton!" << std::endl;
    }
  private:
    static std::shared_ptr<MySingleton> instance;
};
// initialize shared pointer member to singleton instance
std::shared_ptr<MySingleton> MySingleton::instance = nullptr;


int main() {
  std::shared_ptr<MySingleton> singletonGreeting = MySingleton::getInstance();
  singletonGreeting->greeting();

  return 0;
}
