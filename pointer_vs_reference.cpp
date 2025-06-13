C++ Notes: Pointers vs. References
  
The Golden Rule
-> Start with References. They are safer and have cleaner syntax.
-> Switch to Pointers only when you must. You must use a pointer if you need either nullability or re-assignment.
  
=> Use a Reference (&) - The Safe Alias
A reference is an alias for an existing object. Use it when you are sure you'll be working with a valid, non-null object.
  
Use Case 1: Safer Function Arguments
-> The Logic: Guarantees that a function receives a valid object, eliminating the need for nullptr checks 
   and simplifying the code.
Example:
//========================================================================
// This function's "contract" is: "You MUST give me a real Player object."
void printPlayerHealth(Player& player) {
    // No need to check if 'player' is null. We can just use it.
    std::cout << player.getHealth() << std::endl;
}

int main() {
    Player p1;
    printPlayerHealth(p1); // Clean syntax, guaranteed to be safe.
}
//========================================================================

Use Case 2: Modifying Elements in a Loop
The Logic: The natural, idiomatic way to get direct, non-copying access to modify elements inside a container.
Example:
  //========================================================================
std::vector<int> scores = { 10, 20, 30 };

// Use a reference `&` to directly modify each score.
for (int& score : scores) {
    score += 5;
}
// `scores` is now { 15, 25, 35 }
//========================================================================



=> Use a Pointer (*) - The Flexible Address
A pointer stores the memory address of an object. Use it when you need flexibility that a reference cannot provide.
Use Case 1: Optional Relationships (Nullability)
-> The Logic: A pointer can be nullptr, which is perfect for modeling a link that might or might not exist. 
   A reference cannot be null.
Example: An employee might not have a manager.
  //========================================================================
  class Employee {
public:
    // A pointer is necessary here.
    // `nullptr` indicates this employee is at the top (e.g., CEO).
    Employee* manager;
};
//========================================================================

Use Case 2: Changing What is Pointed To (Re-assignment)
-> The Logic: A pointer's value (the address it holds) can be changed to point to different objects over 
   its lifetime. A reference is permanently bound to its initial object. This is essential for many data structures.
Example: Implementing a Linked List node.
  //========================================================================
class Node {
public:
    int data;
    // The `next` member MUST be a pointer.
    // It needs to be nullptr for the last node and must be
    // re-assigned when inserting or deleting nodes.
    Node* next;
};
//========================================================================

Use Case 3: Interfacing with C-style APIs
-> The Logic: Older C/C++ libraries often allocate memory and return raw pointers. You must use a pointer to work 
  with these APIs and to correctly handle NULL return values, which often indicate an error.


  Quick Reference Table
Feature	                          Pointer (int* ptr)	                               Reference (int& ref)
Can it be re-assigned?	      Yes. Can point to a different object later.        	 No. Bound to one object for life.
Can it be null?               Yes. Can hold nullptr.	                             No. Must refer to a valid object.
Must it be initialized?       No. Can be dangerously uninitialized.                Yes. Must be initialized at creation.
Syntax for access	            Indirectly, using * (dereference) and -> (arrow).    Directly, like it's the original variable.
