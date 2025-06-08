#include <iostream>
using namespace std;

class Base {
	virtual void msg() {
		cout << "base msg" << endl;
	}
};

class Derived : public Base
{

};

//=======================================================================
//a sceneraio: all beings belong to a grand class called character. some are player, while others are enemy
//each character can speak but only player can attak - game engine uses a single reference (Character*) to manage all characters
//it needs a way to check whether a character is really a Player before allowing them to attack.
class character { //polymorphic base class
public:
	virtual void speak() {
		cout << "i am a character" << endl;
	}
};

class player : public character {
public:
	void speak() {
		cout << "i am player" << endl;
	}
	void attack() {
		cout << "player is attacking!" << endl;
	}
};

class enemy : public character {
	void speak() {
		cout << "i am enemy" << endl;
	}
};

void performAction(character* c) {
	player* p = dynamic_cast<player*>(c); //is it really a player
	if (p) {
		p->attack();
	}
	else {
		cout << "not a player" << endl;
	}
}

//====================== const_cast ========================
void func(int* ptr) {
	cout << *ptr << endl;
}

int main()
{
	//snippet 1
	// int num1 = 9;
	// double num2;
	// num2 = num1;
	// cout << "int value: " << num1 << endl;
	// cout << "double value: " << num2 << endl;

	//snippet 2
	// int num1;
	// double num2 = 9.87;
	// num1 = num2;
	// cout << "int value: " << num1 << endl;
	// cout << "double value: " << num2 << endl;

	//first snippet shows - implicit widening conversion(int->double, no data loss)
	//second snippet shows - implicit narrowing conversion(double->int, truncating decimal part)


	/*
	order of typecast in implicit conversion:
	bool -> char -> short int -> int -> usigned int -> long int -> unsigned long int -> long long int ->
	float -> double -> long double
	*/

	// int number1 = 7;
	// int number2 = 3;
	// float result;
	// cout << "implicit conversion: " << number1/number2 << endl;

	// result = (float)number1/number2;
	// cout << "explicit conversion: " << result << endl;   


	/*
	static_cast
	1. capable enough that can perform all the conversions carried out by the implicit cast.
	2. Compile casting

	syntax:
	static_cast < new_data_type > (expression);
	*/

	double multiplication = 3.6 * 1.7;
	int result;
	result = static_cast<int>(multiplication);
	cout << "result: " << result << endl;

	//================================================================

	/*
	Dynamic Cast
	1. dynamic_cast is a runtime cast operator used to perform conversion of one type variable
	to another only on class pointers and references.
	2. It means it checks the valid casting of the variables at run time, and if casting fails, it returns a null value.

	syntax:
	dynamic_cast < new_data_type > (expression);
	*/

	/*  Base b;
	  Derived d;

	  Base *basePtr = dynamic_cast<Base*>(&d); //works (derives -> base)
	  Derived* derPtr = dynamic_cast<Derived*>(&b); //fails (base is not necessarily derived)

	  cause of error:
	  Upcasting (Derived → Base) is always safe.
  Downcasting (Base → Derived) is unsafe unless the object is originally of Derived type.


	  */

	  //Base* ptr = new Derived;
	  //Derived* derPtr = dynamic_cast<Derived*>(ptr); //we are casting base class type pointer into derived class type pointer using dynamic-cast 
	  //if (derPtr) {
	  //    cout << "success" << endl;
	  //}
	  //else {
	  //    cout << "failed" << endl;
	  //}

	//character* c1 = new player;
	//character* c2 = new enemy;

	//performAction(c1); //should attack
	//performAction(c2); //should print "not a player

	/*
	* If (c1's vtable == Player's vtable) {
	return a valid Player pointer;
} else {
	return nullptr;
}

	*/

	/*
	Reinterpret cast
	1. it is used to convert a pointer of some data type into a pointer of another data type,
	even if the data types before and after conversion are different.
	2. it does not check if the pointer type and data pointed by the pointer is same or not.

	syntax:
	reinterpret_cast<new_data_type> (expression);
	*/

	//int* ptr = new int(67);
	//char* chrPtr = reinterpret_cast<char*>(ptr); //chrPtr points to the same memory address as ptr, but it treats the data as char instead of int.

	//cout << "ptr: " << ptr << endl;
	//cout << "chrPtr: " << chrPtr << endl;


	//cout << "*ptr: " << *ptr << endl;
	//cout << "*chrPtr: " << *chrPtr << endl;


	/*
	 //Const Cast
	 1. The const cast is used to change or manipulate the behaviour of the source pointer.
	 It means we can perform to the const in two ways:
	 seting a const pointer to a non-const pointer or deleting or removing the const from a const pounter.
	 Syntax:
	 const_cast < new_data_type > (expression)
	 */

	const int num1 = 100;
	const int* constPtr = &num1; // 'constPtr' -> pointer to a constant integer - means you cannot change the variable via this pointer

	//func(constPtr); //func() is expecting a int* but we are passing const int* -> error
	func(const_cast<int*>(constPtr)); //we casted 'const int*' to 'int*'



	//casting a non const to const:
	int* pointer = new int(123);
	*pointer = 234; //changing pointer's value
	//printing it:
	cout << *pointer << endl;
	//now casting it as const 
	const int* newPtr = const_cast<const int*>(pointer);

	//this should give error
	//*newPtr = 123; // yes, gives error! since newPtr is const
	newPtr++; //pointer is not const so it can be modified


	return 0;
}
