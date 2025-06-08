#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

// minimal mockup of how std::vector might define its iterator
template<typename T>
class myVector {
public:
	typedef T* iterator; // nested typedef for iterator

	// example begin() and end() using the nested iterator
	iterator begin() { return data; }
	iterator end() { return size + data; }
private:
	T* data;
	size_t size;
};


struct Point {
	int x;
	int y;
};

int main() {
	// iterators are pointer like objects that are used to point to the memory address of STL containers
	
	// iterator vs pointer 
	// feature				iterator									pointer
	// what is it?			abstract object for container nav			memory address
	// syntax				it++, *it									ptr++, *ptr
	// safety				type-safe, container-aware					unsafe if misused 
	// invalidation on		container structure change					memory dealloaction

	// an iterator helps us loop through a container (like vector, list, etc) similar to how a pointer works for arrays
	
	// how are iterators implemented internally?
	// For simple containers like vector, array - iterator is just a pointer under the hood
	// For list, map, set, etc - iterator is a class or struct and overloads operator like ++, --, *, != to behave like a pointer

	std::vector<std::pair<int, char>>vpic;
	std::vector<std::pair<int, char>>::iterator it;
	// this iterator is a type alias (typedef) defined by vector class

	// internally it's like typedef pair<int,char>* iterator; so it becomes a pointer to pair<int,char> 
	// all resolved at compile time using templates

	// typedef?
	// it gives a new name to an existing type
	// it is a shortuct or alias

	// nested type ? 
	// is a type declared inside another class or struct

// All STL containers (vector, list, map, etc.) define their own nested iterator, const_iterator, etc.

	/*
	 Yes — every STL container defines its own iterator as a nested type, like:
	 std::vector<T>::iterator
	std::list<T>::iterator
	std::map<K, V>::iterator
	This way, each container provides the correct iterator type for its internal structure (pointer-based or class-based).

	They also define:
	 - const_iterator
	 - reverse_iterator
	 - const_reverse_iterator
	*/


	/*
	 - Containers like set, map, and list have custom internal structures (trees, linked lists).
	 - So they provide a nested iterator class with overloaded operators (++, --, *, etc.).
	 - When you do it++, it means it.operator++() is called.
	 - That overloaded function contains the exact logic for in-order traversal (in case of set/map) or next node (in case of list).
	*/


	// in C++ iterators are of 5 types:
	// 1. input: used to read values from a sequence once and only move forward
	// 2. ouput: used to write values into a sequence once and only move forward
	// 3. forward: they combine features of both i/p and o/p iterators
	// 4. bidirectional: support all operations of forward iterators & additionally can move backwards
	// 5. random access: support all operations od bidirectional iterators + additionally provide efficient random access to elements.

	// input iterator example
	/*
	std::cout << "Enter 5 integers: ";
	std::istream_iterator<int> inIt(std::cin);         // input iterator from cin
	std::istream_iterator<int> eos;                    // end of stream iterator

	std::vector<int> vec(inIt, eos);

	sort(vec.begin(), vec.end());

	for (auto& it : vec) {
		std::cout << it << " ";
	}
	std::cout << "\n";

	std::vector<int>v = {11,4,33,7,8};
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));



	*/

	
	// example one: when iterator points to a class/struct and you want to access a member
	std::vector<Point>points = { {2,3},{0,0},{3,7} };
	std::vector<Point>::iterator itrOP = points.begin();
	std::cout << itrOP->x << "\n"; // prints 2
	// (same as (*itr).x)
	std::cout << (*itrOP).x << "\n"; // prints 2

	// example two: use *itr when you want to access thr object the iterator opints to
	std::vector<int>a = { 1,3,6,9,12 };
	auto p = a.begin();
	p=a.begin()+(a.size()/2);
	std::cout << "middle elem is " << *p << "\n";


	// example three and four: use itr. when cakking a method on the iterator itself, not the elements it points to:
	std::vector<int>vtr = { 21,42,81,162 };
	auto ivi = vtr.begin(); //( ivi - iterator on vector of int)
	// using the iterators own member function
	if (ivi != vtr.end()) {
		std::cout << "first elem of vtr: " << ivi.operator*() << std::endl; // same as *itr
	}

	// ex four: 
	ivi.operator++(); 
	if (ivi != vtr.end()) {
		std::cout << "next elem: " << ivi.operator*() << std::endl;
	}


	// const iterator 
	std::vector<std::pair<int, std::string>>vpis = { {1,"dog"},{2,"cat"},{3,"tiger"},{4,"mouse"}};
	for (std::vector<std::pair<int, std::string>>::const_iterator itr = vpis.begin();itr != vpis.end();itr++) {
		// itr->first += 1; // throws error since the iterator is const
		std::cout << itr->first << " " << itr->second<<"\n";
	}
	/*
	A const pointer disallows changing the value it points to by making the object being pointed to constant, not the pointer itself.
	*/



	// reverse iterator
	std::vector<int>::reverse_iterator rit= vtr.rbegin();
	std::cout << "vtr: [ ";
	for (;rit != vtr.rend();rit++) {
		std::cout << *rit << " ";
	}
	std::cout << "]\n";
	// rbegin and rend is different from normal begin and end
	// rbegin -> points to last element of container
	// rend -> points to just before the first element(not possible to dereference)


// Reverse Iterator Implementation:
// Internally, a `reverse_iterator` is typically implemented as a wrapper around a normal iterator, 
// which points to the last element of the container. It overrides the increment (`++`) and decrement (`--`) 
// operators to move backwards through the container, effectively providing reverse traversal.

	// const_reverse_iterator
	std::vector<int>::const_reverse_iterator cri = vtr.rbegin();
	for (;cri != vtr.rend();cri++) {
		// *cri += 5; throws error since it's a const pointer under the hood 
		std::cout << *cri << " ";
	}


	return 0;
}

