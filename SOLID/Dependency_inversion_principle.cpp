"The Dependency Inversion Principle (DIP) states two key things:
1. High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g., interfaces).
2. Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.

=> Problem it Solves:
DIP addresses the problems caused by tight coupling between high-level and low-level modules:
 1. Rigidity: When high-level modules directly depend on low-level modules, changes in the low-level modules can force changes in the high-level modules, even if the high-level logic
    itself hasn't changed.
 2. Fragility: Changes in low-level details can easily break high-level modules.
 3. Immobility/Non-Reusability: High-level modules become difficult to reuse in different contexts if they are tied to specific low-level implementations.
 4. Difficult Testing: Testing high-level modules becomes hard because you have to bring in all their concrete low-level dependencies. It's difficult to replace low-level modules with 
    mocks or stubs for testing.

=> Why is this important? (Why invert the dependency?)
  - Decoupling: High-level modules become independent of the concrete implementations of the low-level modules they use. They only care about the abstraction (the contract).
  - Flexibility & Extensibility: You can easily swap out different low-level implementations without changing the high-level modules, as long as the new implementations adhere 
    to the abstraction. This is great for adding new features or adapting to changing requirements (e.g., switching from a file logger to a database logger).
  - Testability: High-level modules can be tested in isolation by providing mock implementations of their abstract dependencies.
  - Improved Design: It encourages designing around stable abstractions rather than volatile concrete details.

How is it typically achieved?
DIP is often implemented using:
1. Interfaces or Abstract Base Classes: Define an interface that represents the service or functionality the high-level module needs.
2. Dependency Injection (DI): The concrete implementation of the interface (the low-level module) is "injected" into the high-level module, typically via its constructor, 
   a setter method, or directly as a method parameter. The high-level module doesn't create its dependencies itself; it receives them.



Use Case: We have a NotificationService (high-level module) that needs to send notifications. Initially, it sends notifications via email.

Before DIP (High-Level Depends Directly on Low-Level)
#include <iostream>
#include <string>

// --- Before DIP ---

// Low-level module: Concrete implementation for sending emails
class EmailSender_BeforeDIP {
public:
    void sendEmail(const std::string& recipient, const std::string& message) {
        std::cout << "Sending email to " << recipient << ": " << message << std::endl;
        // Actual email sending logic would go here
    }
};

// High-level module: Directly depends on the concrete EmailSender_BeforeDIP
// If we want to switch to SMS or another notification method,
// we MUST MODIFY NotificationService_BeforeDIP.
class NotificationService_BeforeDIP {
private:
    EmailSender_BeforeDIP emailer; // Direct dependency on a concrete low-level class

public:
    NotificationService_BeforeDIP() {
        // The high-level module creates its own low-level dependency.
    }

    void sendNotification(const std::string& recipient, const std::string& message) {
        // Tightly coupled to EmailSender_BeforeDIP
        emailer.sendEmail(recipient, message);
    }
};

int main_before() {
    NotificationService_BeforeDIP notifier;
    notifier.sendNotification("user@example.com", "Hello from Before DIP!");

    // Problem: What if we want to send an SMS instead?
    // We'd have to change NotificationService_BeforeDIP to use an SMSSender,
    // or add if/else logic, making it more complex and less flexible.
    return 0;
}

After Applying DIP (Both Depend on Abstractions)
#include <iostream>
#include <string>
#include <memory> // For std::unique_ptr

// --- After DIP ---

// Step 1: Define an Abstraction (Interface)
// This is what the high-level module will depend on.
struct IMessageSender {
    virtual ~IMessageSender() = default;
    virtual void sendMessage(const std::string& recipient, const std::string& message) = 0;
};

// Step 2: Create Low-Level Modules (Concrete Implementations) that implement the abstraction.
// These "details" now depend on the abstraction (IMessageSender).
class EmailSender_AfterDIP : public IMessageSender {
public:
    void sendMessage(const std::string& recipient, const std::string& message) override {
        std::cout << "Sending email to " << recipient << ": " << message << std::endl;
        // Actual email sending logic
    }
};

class SMSSender_AfterDIP : public IMessageSender {
public:
    void sendMessage(const std::string& recipient, const std::string& message) override {
        std::cout << "Sending SMS to " << recipient << ": " << message << std::endl;
        // Actual SMS sending logic
    }
};

// Step 3: High-Level Module now depends on the Abstraction (IMessageSender).
// It does not know about concrete EmailSender or SMSSender.
class NotificationService_AfterDIP {
private:
    // The high-level module holds a reference/pointer to the abstraction.
    std::unique_ptr<IMessageSender> messageSender;

public:
    // Dependency Inversion: The concrete dependency is "injected" (passed in).
    // The NotificationService_AfterDIP does not create its own sender.
    NotificationService_AfterDIP(std::unique_ptr<IMessageSender> sender)
        : messageSender(std::move(sender)) {}

    void sendNotification(const std::string& recipient, const std::string& message) {
        // Works with any object that implements IMessageSender
        if (messageSender) {
            messageSender->sendMessage(recipient, message);
        }
    }
};


int main_after() {
    // We can choose the notification method at runtime (or configuration time)
    // by "injecting" the desired implementation.

    // Send via Email
    std::unique_ptr<IMessageSender> emailSender = std::make_unique<EmailSender_AfterDIP>();
    NotificationService_AfterDIP emailNotifier(std::move(emailSender));
    emailNotifier.sendNotification("user@example.com", "Hello from Email (After DIP)!");

    std::cout << "---" << std::endl;

    // Send via SMS
    std::unique_ptr<IMessageSender> smsSender = std::make_unique<SMSSender_AfterDIP>();
    NotificationService_AfterDIP smsNotifier(std::move(smsSender));
    smsNotifier.sendNotification("123-456-7890", "Hello from SMS (After DIP)!");

    // The NotificationService_AfterDIP class did not need to change to support SMS.
    // We just provided a different implementation of IMessageSender.
    return 0;
}

// To run one of them:
int main() {
    std::cout << "--- Running Before DIP ---" << std::endl;
    main_before();
    std::cout << "\n\n--- Running After DIP ---" << std::endl;
    main_after();
    return 0;
}

Explanation of Logic Changes:
=> Before DIP:
 - NotificationService_BeforeDIP (high-level) directly created and used an EmailSender_BeforeDIP (low-level).
 - The dependency arrow was: NotificationService_BeforeDIP ---> EmailSender_BeforeDIP.
 - To change how notifications are sent (e.g., to SMS), NotificationService_BeforeDIP itself would need to be modified.

After DIP:
 - We introduced an abstraction: IMessageSender.
 - NotificationService_AfterDIP (high-level) now depends only on the IMessageSender interface.
 - EmailSender_AfterDIP and SMSSender_AfterDIP (low-level details) now implement (and thus depend on) the IMessageSender interface.
 - The dependency arrows are now:
   - NotificationService_AfterDIP ---> IMessageSender
   - EmailSender_AfterDIP ---> IMessageSender (implements it)
   - SMSSender_AfterDIP ---> IMessageSender (implements it)
 - The concrete sender (EmailSender_AfterDIP or SMSSender_AfterDIP) is injected into NotificationService_AfterDIP (typically via the constructor). The high-level module doesn't control which concrete implementation is used; that decision is made externally.
 -   This "inverts" the dependency: the low-level details depend on the abstraction defined by/for the high-level module.



 Simplified Recap:
 - High-Level: The "what to do" (e.g., "I need to notify a user").
 - Low-Level: The "how to do it" (e.g., "Send an email using GMail's API," or "Send an SMS via Twilio").
 - Abstraction: A common contract (e.g., an INotifier interface with a send(message) method).
DIP:
 - The High-Level module uses the INotifier abstraction.
 - The Low-Level "GMailNotifier" and "TwilioNotifier" implement the INotifier abstraction.
 - Dependency Injection: Some other part of your system decides whether the GMailNotifier or TwilioNotifier gets given to (injected into) the High-Level module when it needs an INotifier.
