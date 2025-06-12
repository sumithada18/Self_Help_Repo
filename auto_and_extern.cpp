=> Storage Class 1: auto (The Temporary Local)
This is the default, most common storage class for any variable you declare inside a function or a block { ... }. You use it all the time without even typing the word auto.
 -> Core Idea: It creates a temporary, private variable for a function.
 -> Lifetime (How long it exists):
    - Automatic. The variable is "born" when the function is called and it "dies" (its memory is freed) as soon as the function finishes.
    - If you call the same function again, a brand new variable is created.
-> Visibility (Where it can be seen):
    - Local. It is only visible inside the function or block where it is defined. No other function can see or access it.
-> Default Value:
    - Garbage. If you don't explicitly initialize it, its value is unpredictable.
-> Example:
//-------------------------------------------------------------------------
#include <iostream>

void myFunction() {
    // 'local_score' has 'auto' storage class by default.
    int local_score = 100; // Born here, initialized to 100.
    std::cout << "Inside myFunction, score is: " << local_score << std::endl;
    local_score = 50; // We can change it here.
} // 'local_score' dies here.

int main() {
    myFunction(); // Prints "Inside myFunction, score is: 100"
    myFunction(); // Prints "Inside myFunction, score is: 100" again (a new variable was created)

    // local_score = 10; // COMPILE ERROR! 'local_score' is not visible here.
    return 0;
}
//-------------------------------------------------------------------------
(C++ Note: In modern C++ (C++11 and later), the auto keyword was given a new job: automatic type deduction. But the original meaning as a storage class still exists as the default for local variables.)

=> Storage Class 2: extern (The Global Link)
This storage class is used to share a global variable across multiple source files (.cpp). It's a promise to the compiler.
-> Core Idea: It declares a variable without defining it, promising that the "real" variable is defined in another file.
-> Lifetime (How long it exists):
    - Static/Permanent. The variable exists for the entire duration of the program's run. It's created when the program starts and destroyed only when it ends.
-> Visibility (Where it can be seen):
    - Global. It can be accessed from any file in the project that includes its extern declaration.
-> Default Value:
    - Zero. If not explicitly initialized in its definition, it defaults to zero.
-> Example (requires multiple files):
globals.cpp (This file has the one, single definition)
//-------------------------------------------------------------------------
// The one and only DEFINITION of this global variable.
// It exists for the whole life of the program.
int g_player_health = 100;
//-------------------------------------------------------------------------

main.cpp (This file uses the shared variable)
//-------------------------------------------------------------------------
#include <iostream>

// DECLARATION: We promise the compiler that 'g_player_health'
// is defined somewhere else.
extern int g_player_health;

void some_other_function(); // A function from another file

int main() {
    std::cout << "Health at start: " << g_player_health << std::endl; // Prints 100
    g_player_health -= 20; // We can modify it
    std::cout << "Health after taking damage: " << g_player_health << std::endl; // Prints 80

    some_other_function(); // Let's call a function from another file

    std::cout << "Health after enemy's turn: " << g_player_health << std::endl; // Prints 55
    return 0;
}
//-------------------------------------------------------------------------

enemy.cpp (Another file that also uses the same shared variable)
//-------------------------------------------------------------------------
#include <iostream>

// Another declaration to access the same global variable
extern int g_player_health;

void some_other_function() {
    std::cout << "An enemy attacks!" << std::endl;
    g_player_health -= 25; // Modifies the SAME variable defined in globals.cpp
}
//-------------------------------------------------------------------------
