## Software Design Principies

**Encapsulate what varies:**
This principle focuses on identifying and isolating the parts of a system that are most likely to change, encapsulating them so that any modifications to those parts do not affect the behavior or functionality of the rest of the system. By doing so, it simplifies code maintenance, enhances extensibility, and minimizes the risk of errors by reducing dependencies between stable and variable components.

**Program to an interface, not to an implementation**  
This principle emphasizes that, whenever possible, dependencies in our classes—whether through composition, aggregation, simple dependency, or inheritance—should always be abstractions rather than concrete classes. This ensures that our classes are not tightly coupled to a specific implementation but instead rely on abstractions. This approach makes our classes more flexible, efficient, and easier to maintain.

**Favor Composition Over Inheritance**  
Inheritance might seem like the most obvious way to reuse code between classes, but if not managed properly, it can lead to complex hierarchies that are hard to maintain and prone to errors. A better alternative is composition: analyze the dependencies between classes and design a structure based on object collaboration. This simplifies hierarchies, creates more flexible structures, and makes maintenance easier.
