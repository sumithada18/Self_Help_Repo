#include <iostream>
#include <functional>
#include <vector>
#include <string>

// Normal function (Function Pointer)
int squareFunction(int val) {
    return val * val;
}

// Functor (Function Object)
struct SquareFunctor {
    int operator()(int val) {
        return val * val;
    }
};

// Simulated API using a callback
void runProtectedAPI(int input, const std::string& password, std::function<int(int)> callback) {
    static std::string correctPassword = "sumit";
    
    if (password == correctPassword) {
        std::cout << "✅ Access Granted. Running API...\n";
        std::cout << "Result = " << callback(input) << "\n";
    } else {
        std::cout << "❌ Access Denied. Wrong password.\n";
    }
}

int main() {
    // Lambda stored in std::function
    auto lambdaSquare = [](int x) { return x * x; };
    
    // Function pointer
    int (*funcPtr)(int) = squareFunction;
    
    // Functor instance
    SquareFunctor functorInstance;

    // Store different callable types in std::function
    std::vector<std::function<int(int)>> callables = {
        lambdaSquare,    // Lambda
        squareFunction,  // Function pointer
        functorInstance  // Functor
    };

    // Demonstrate using each callable
    int multiplier = 1;
    for (const auto& callable : callables) {
        std::cout << "Output: " << callable(multiplier * 10) << "\n";
        ++multiplier;
    }

    // Demonstrate real use: pass callables as API callbacks
    std::string userPassword;
    for (const auto& callable : callables) {
        std::cout << "\nEnter password to access API: ";
        std::cin >> userPassword;
        runProtectedAPI(10, userPassword, callable);
    }

    return 0;
}
