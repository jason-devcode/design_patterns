#include <iostream>

class ClassB {
  public:
    ClassB() = default;
  
    void greeting() {
      std::cout << "Hello, from B class!" << std::endl;
    }
};

class ClassA {
  public:
    ClassA() = default;
  
    void dependencyGreeting( ClassB& B ) {
      B.greeting();
    }
};


int main() {
  ClassA A;
  ClassB B;
  A.dependencyGreeting( B );

  return 0;
}

