
**Single Responsibility Principe (SRP):**
A class should have a single responsibility or purpose. One way to evaluate whether a class complies with this principle is by analyzing the reasons it has to change. If a class has reasons to change beyond its main purpose, it is most likely performing more work than it should, and it would be more appropriate to delegate this work to another class.

**Open/Close Principle:**
A class should be open to extensions and closed to modifications. This means that once a class is considered complete, it should not be modified unless there is a functionality issue that needs to be fixed.

**Liskov Substitution Principle:**
A subclass must be able to replace its base class without altering the behavior expected by the client.
For a subclass to comply with this principle, it must meet the following requirements:

1. The typing of the parameters of a subclass method must be the same or use abstractions of the typing of the same method in the superclass.  
2. The return type of a subclass method must be the same or an extension of the return type used in the method in the superclass.  
3. A subclass method must not throw exception types that are not expected to be thrown by the method in the superclass, as this changes the behavior expected by the method's client.  
4. A subclass must not strengthen the preconditions.  
5. A subclass must not weaken the preconditions.  
6. The invariants of the superclass must be preserved; invariants are conditions under which an object makes sense.  
7. A subclass must not be able to modify private fields of the superclass.

**Interface Segregation Principle:**
An interface should not force a class to implement methods that are irrelevant or unnecessary for it. Therefore, it is better to divide (segregate) the interface into smaller and more specific interfaces so that classes only have to implement the methods they actually use.

**Dependency Inversion Principle:**
High-level classes should not depend on low-level classes, and vice versa. To achieve this, both types of classes must depend on interfaces or abstractions, and abstractions should not depend on details.

