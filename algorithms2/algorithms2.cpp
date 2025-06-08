#include <iostream>
#include<vector>
#include <unordered_map>
#include <algorithm>

int main() {

	// set_union()
	int first[5] = {1,3,5,8,9};
	int second[5] = { 1,2,5,6,10 };
	std::vector<int>result(10);

	std::vector<int>::iterator itr;
	itr = std::set_union(first, first+5, second, second+5, result.begin());
	// set_union returns an iterator to the position just after the last inserted element in the result array.
	
	result.resize(itr - result.begin()); // free unused space

	printf("resultant array: ");
	for (auto& it : result) {
		std::cout << it << " ";
	}
	printf("\n");

	// unique()
	/*std::vector<int>arr = { 1,1,2,3,3 };
	auto it = std::unique(arr.begin(), arr.end());
	arr.erase(it, arr.end());
	for (int& i : arr) {
		std::cout << i << " ";
	}
	printf("\n");*/

	// make_heap()
	std::vector<int>heap_data = {4, 1, 7, 9, 3};
	std::make_heap(heap_data.begin(), heap_data.end());
	printf("heap: ");
	for (auto& num : heap_data) {
		std::cout << num << " ";
	}


	// task: find and print only duplicates
	/*std::unordered_map<int, int>umap;
	std::vector<int>vecr = { 1,1,2,3,3,4,4 };
	for (auto& it : vecr) {
		umap[it]++;
	}
	std::vector<int>anss;
	for (auto& it : umap) {
		if (it.second >= 2)anss.push_back(it.first);
	}

	printf("duplicate ones: ");
	for (auto& it : anss) {
		std::cout << it << " ";
	}*/
	return 0;
}