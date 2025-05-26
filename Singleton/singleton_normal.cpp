#include <iostream>

// The Singleton class ensures that only one instance of the class can be created.
class Singleton {
private:
	// Private constructor to prevent direct instantiation from outside the class.
	Singleton() {
	    std::cout << "singleton cons.. called\n"; // Indicates when the constructor is called (only once).
	}
	// Static member to hold the single instance of the class.
	// It's initialized to nullptr to indicate no instance has been created yet.
	static Singleton* instance;

public:
	int data=0; // A public data member for demonstration.

	// Static method to get the single instance of the class.
	// This is the only way to get an object of the Singleton class.
	static Singleton* getInstance() {
		// Lazy initialization: create the instance only if it doesn't exist yet.
		if(!instance) {
			instance = new Singleton; // Create the instance.
		}
		return instance; // Return the existing or newly created instance.
	}

	// Delete the copy constructor.
	// This prevents creating a new instance by copying an existing one (e.g., Singleton s2 = *ptr;).
	Singleton(const Singleton&) = delete;

	// Delete the assignment operator.
	// This prevents assigning one Singleton instance to another (e.g., *ptr2 = *ptr;).
	Singleton& operator=(const Singleton&) = delete;
	
	// Method to set the data member.
	void setData(int val){
	    data = val;
	}
	// Method to display the data member.
	void showData(){
	    std::cout << data << "\n";
	}
};

// Initialize the static instance pointer to nullptr outside the class definition.
// This must be done for static members.
Singleton* Singleton::instance = nullptr;

int main()
{
	//Singleton s; // This line would cause a compile-time error because the constructor is private.
	
	// Get the single instance of Singleton.
	// If it's the first time, the constructor will be called.
	Singleton* ptr = Singleton::getInstance();
	ptr->setData(10); // Set data using the first pointer.
	ptr->showData();  // Display data.
	
	// Get the instance again.
	// This will return the SAME instance created before, no new constructor call.
	Singleton* ptr2 = Singleton::getInstance();
	ptr2->showData(); // It shows data as 10 since we only have one instance of it.
	                  // ptr2 points to the same object as ptr, so changes via ptr are visible via ptr2.
	// if that was not the case (i.e., if a new object was created), it would have given output = 0 (the default value of data).
	
	// proof:
	// Check if both pointers point to the same memory address.
	if(ptr == ptr2) std::cout << "same\n"; // This will print "same", confirming they are the same instance.

	return 0;
}