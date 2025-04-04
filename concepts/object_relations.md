# Object and Class Relations

**Dependency:**
Dependency is the weakest relationship between classes. It indicates that a change made in the class being depended on can also affect the dependent class. This type of dependency can be found in methods that receive objects of a certain class or internally create temporary instances of it. In this sense, the dependency relationship also extends to the use of temporary instances within a class, which do not affect the global behavior of the class.

**Inheritance (or Generalization) and Polymorphism:**
The relationship of inheritance or generalization arises when we identify a set of specific classes that share common attributes and behaviors. This process allows us to abstract and generalize these shared elements into a more abstract form, which we call a **general class** or **abstract class**. As a result, the specific classes become particular cases of this general class, inheriting its attributes and behaviors, and forming a **class hierarchy**.  

This relationship is based on the principle that a subclass must represent a specialization of the general class under the rule that a specific class **is a** type of the general class. This is known as the **"is-a" relationship**.  

For example, in a system modeling animals, we can say that:  
- A **Dog** "is a" **Animal**.  
- A **Cat** "is a" **Animal**.  
- Therefore, both share the general characteristics of an **Animal**, such as `name`, `age`, and behaviors like `eat()` or `sleep()`, while adding their own specific characteristics.  

**Polymorphism and the "is-a" Relationship:**
Thanks to inheritance, instances of subclasses can also be treated as instances of the general class due to the "is-a" relationship. This means that an object of type `Dog` or `Cat` can be treated as if it were an object of type `Animal`. This is the foundation of **polymorphism**, which allows us to write more flexible and reusable code.

**Implementation (or realization):**
The implementation or realization of an interface or protocol in a class requires that class to adhere to a contract that defines a set of behaviors or methods. This ensures that objects of that class can communicate with other objects or be used in contexts where compliance with that interface or protocol is required.

**Association:**
In an association relationship, the objects of one class can interact with the objects of another class. For example, the objects of class A are aware of the existence of objects of class B and can interact with them, either by maintaining internal instances of these objects and managing their lifecycle, or by holding references to objects external to the object itself.

**Aggregation:**
In aggregation relationship, the objects of one class can interact with the objects of another class, and objects of one class can act as containers or collections of objects from the other class. For example, by maintaining an array, vector, matrix, or a set of references to objects from the other class, which are added to the collection through a series of methods that allow adding and removing references from the collection.

**Composition:**
In composition, the objects of one class rely on the existence of objects from another class and are responsible for managing their lifecycle.

**Multiplicity:**
**Multiplicity** (or **reciprocity**) in the context of class relationships describes the number of instances of one class that can be associated with instances of another class. This relationship can take several forms, such as:

- **One-to-one (1:1):** Each instance of a class is associated with exactly one instance of the other class.
- **One-to-many (1:N):** One instance of a class can be associated with multiple instances of the other class.
- **Zero-to-many (0:N):** An instance may have no associated instances or may be associated with multiple ones.
- **Many-to-many (M:N):** Several instances of one class can be associated with several instances of another class.
