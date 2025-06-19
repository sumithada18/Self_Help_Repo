ISP:
The Interface Segregation Principle (ISP) states that clients should not be forced to depend on interfaces (or methods)
they do not use.

In simpler terms, it's better to have many small, specific interfaces tailored to particular client needs rather than
one large, general-purpose ("fat") interface that tries to do everything. If a class implements an interface, it 
shouldn't be forced to implement methods it doesn't actually need or use.

=> Problem it Solves:
- ISP addresses the issues that arise from "fat" interfaces:
  - Unnecessary Dependencies & Coupling: When a class implements a large interface but only uses a subset of 
    its methods, it's still forced to depend on the entire interface. If an unused part of that interface changes,
    the class might still need to be recompiled or re-evaluated, even though its core functionality is unaffected.
  - "Interface Pollution": Classes end up with methods they don't care about, often leading to empty implementations or methods that throw "NotSupportedException." This is a code smell and can lead to runtime errors (violating LSP).
  - Low Cohesion: Fat interfaces often group unrelated responsibilities, making them less cohesive.
  - Reduced Understandability & Maintainability: Large interfaces are harder to understand, implement, and maintain.
  - Difficult Testing: Mocking or stubbing a fat interface for testing can be cumbersome.


=> Why is this important? (Why not just have one big interface?)
  - Decoupling: By depending only on what they need, clients are less affected by changes in parts of the system 
    they don't use.
  - Cohesion & Clarity: Smaller, focused interfaces are easier to understand and have a clearer purpose (similar to 
    SRP for classes).
  - Flexibility & Reusability: It's easier to implement and reuse smaller, specific interfaces. A class can implement 
    multiple small interfaces if it needs to fulfill multiple distinct roles.
  - Prevents "Dummy" Implementations: Classes aren't forced to provide empty or throwing implementations for methods
    they don't support.

=> How is it typically achieved?
The main way to achieve ISP is by breaking down large interfaces into smaller, more cohesive ones. Each smaller
interface serves a specific role or capability. A class can then implement multiple of these smaller interfaces as needed.

Analogy:
Think of a multi-tool. If you only ever need a screwdriver and a bottle opener, but your multi-tool also has a saw, 
pliers, scissors, and a toothpick, you're carrying around (and potentially being affected by changes to) features 
you don't use. ISP suggests you might be better off with a separate screwdriver and a separate bottle opener if those 
are your only needs, or a smaller multi-tool that only has those two functions.


Use Case: We have different types of workers in a system. Some can work, some can eat, and some can do both.
Before ISP(One fat interface):
#include <iostream>
#include <string>
#include <stdexcept> // For exceptions

// --- Before ISP ---
// This is a "fat" interface. Not all workers will need both methods.
// Clients will depend on this whole interface even if they only care about one part.
struct IWorker_BeforeISP {
    virtual ~IWorker_BeforeISP() = default;
    virtual void work() = 0;
    virtual void eat() = 0;
};

// A HumanWorker can both work and eat. This class is fine.
class HumanWorker_BeforeISP : public IWorker_BeforeISP {
public:
    void work() override {
        std::cout << "Human worker is working hard." << std::endl;
    }
    void eat() override {
        std::cout << "Human worker is eating lunch." << std::endl;
    }
};

// A RobotWorker can only work. It CANNOT eat.
// It is FORCED to provide an implementation for eat(), even if it's meaningless or throws.
// This is "interface pollution" and can lead to LSP violations if not handled carefully.
class RobotWorker_BeforeISP : public IWorker_BeforeISP {
public:
    void work() override {
        std::cout << "Robot worker is performing tasks efficiently." << std::endl;
    }
    void eat() override {
        // Option 1: Empty implementation (misleading, looks like it can eat)
        // Option 2: Throw exception (can lead to runtime errors if client isn't careful)
        // std::cout << "Robot tries to eat... but it's a robot." << std::endl; // Misleading
        throw std::logic_error("RobotWorker cannot eat!");
    }
};

// Client code that only cares about working
void makeSomeoneWork(IWorker_BeforeISP& worker) {
    worker.work();
    // This client doesn't care about eat(), but the worker object
    // might still have a problematic eat() method (like in RobotWorker_BeforeISP).
}

// Client code that might try to make someone eat
void makeSomeoneEat(IWorker_BeforeISP& worker) {
    try {
        worker.eat();
    } catch (const std::logic_error& e) {
        std::cerr << "Error during eating: " << e.what() << std::endl;
    }
}

int main_before() {
    HumanWorker_BeforeISP human;
    RobotWorker_BeforeISP robot;

    std::cout << "--- Human Worker (Before ISP) ---" << std::endl;
    makeSomeoneWork(human);
    makeSomeoneEat(human);

    std::cout << "\n--- Robot Worker (Before ISP) ---" << std::endl;
    makeSomeoneWork(robot);
    makeSomeoneEat(robot); // This will cause an issue or print a misleading message.

    return 0;
}



After ISP(segregated interface):
#include <iostream>
#include <string>
#include <stdexcept>

// --- After ISP ---

// Interface 1: For things that can work
struct IWorkable {
    virtual ~IWorkable() = default;
    virtual void work() = 0;
};

// Interface 2: For things that can eat
struct IEatable {
    virtual ~IEatable() = default;
    virtual void eat() = 0;
};

// HumanWorker implements both interfaces because it can do both.
class HumanWorker_AfterISP : public IWorkable, public IEatable {
public:
    void work() override {
        std::cout << "Human worker is working hard." << std::endl;
    }
    void eat() override {
        std::cout << "Human worker is eating lunch." << std::endl;
    }
};

// RobotWorker ONLY implements IWorkable because it can only work.
// It is NOT forced to implement an eat() method it doesn't support.
class RobotWorker_AfterISP : public IWorkable {
public:
    void work() override {
        std::cout << "Robot worker is performing tasks efficiently." << std::endl;
    }
    // No eat() method here!
};

// This client ONLY depends on the IWorkable interface.
// It doesn't know or care about IEatable.
void makeWorkableThingWork(IWorkable& worker) {
    worker.work();
}

// This client ONLY depends on the IEatable interface.
void makeEatableThingEat(IEatable& eater) {
    eater.eat();
}

int main_after() {
    HumanWorker_AfterISP human;
    RobotWorker_AfterISP robot;

    std::cout << "--- Human Worker (After ISP) ---" << std::endl;
    makeWorkableThingWork(human); // Human is IWorkable
    makeEatableThingEat(human);   // Human is IEatable

    std::cout << "\n--- Robot Worker (After ISP) ---" << std::endl;
    makeWorkableThingWork(robot); // Robot is IWorkable

    // makeEatableThingEat(robot); // This would be a COMPILE ERROR!
                                 // RobotWorker_AfterISP does not implement IEatable.
                                 // The type system prevents calling eat() on a robot.
                                 // This is much safer than a runtime error.

    return 0;
}

// To run one of them:
int main() {
    std::cout << "--- Running Before ISP ---" << std::endl;
    main_before();
    std::cout << "\n\n--- Running After ISP ---" << std::endl;
    main_after();
    return 0;
}

Explanation of Logic Changes:

=> Before ISP: We had one IWorker_BeforeISP interface with both work() and eat().
  - HumanWorker_BeforeISP was fine.
  - RobotWorker_BeforeISP was forced to provide an eat() method, which it couldn't meaningfully implement. 
    This led to either an empty/misleading implementation or throwing an exception (a runtime risk).
  - Clients like makeSomeoneWork depended on the whole IWorker_BeforeISP, even if they only needed work().

=> After ISP:
  - We segregated the interface into IWorkable and IEatable.
  - HumanWorker_AfterISP implements both, as it has both capabilities.
  - RobotWorker_AfterISP only implements IWorkable. It is no longer forced to deal with eat().
  - Client functions like makeWorkableThingWork now depend only on the IWorkable interface.
  - Client functions like makeEatableThingEat now depend only on the IEatable interface.
  - Crucially, trying to pass a RobotWorker_AfterISP to makeEatableThingEat results in a compile-time error, which is much better than a potential runtime error. The system is safer and clearer.
