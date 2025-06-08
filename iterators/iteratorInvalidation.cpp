/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
	// iterators invalidation in vector - example
	std::vector<int>vr = { 12,4,2,1,44,11,7,9 };

	std::vector<int>::iterator itr = vr.begin() + 1;
	std::vector<int>::iterator itr2 = itr + 2;

	// vr.erase(itr);
	// std::cout << *itr << "\n";
	// std::cout << *itr2 << "\n";
	// both the statemnts will result in crash!
	// reason : If you don’t receive the returned iterator, you still hold the old (now invalid) one — which leads to crash/undefined behavior when used.
	// solution ? 

	// correct way :

	itr = vr.erase(itr);
	std::cout << *itr << "\n";
	// and reassign itr2
	itr2 = itr + 2;
	std::cout << *itr2 << "\n";


	return 0;
}

*/