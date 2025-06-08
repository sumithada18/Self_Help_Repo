#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

// comparator for sorting in ascending - no use since sort() by defaults sorts in ascending
//bool comp(int a, int b) {
//	if (a <= b) {
//		return true;
//	}
//	return false;
//}

// sort array in descending
//bool comp(int a, int b) {
//	if (a >= b) {
//		return true;
//	}
//	return false;
//}

// sort array of std::pair 
bool comp(std::pair<int,int>p1, std::pair<int, int>p2) {
	if (p1.first < p2.first) {
		return true;
	}
	if (p1.first == p2.first) {
		if (p1.second < p2.second) return false;
		else return true;
	}
	return false;
}


int main() {
	// sort 
	int n = 5;
	int arr[5] = { 12,4,9,25,42 };
	std::sort(arr, arr + n); // n log n 

	// std::vector<int>vec = { 12,4,5,2,11 };
	// below sorts the whole array 
	// sort(vec.begin(), vec.end()); 

	// sort only middle 3 values : {12, 9, 7, 8, 99} -> {12, 7, 8, 9, 99}
	std::vector<int>vec = { 12,9,7,8,99 };
	printf("before sorting: ");
	for (auto& it : vec) std::cout << it << " ";
	printf("\n");
	std::sort(vec.begin() + 1, vec.begin() + 4);
	printf("after sorting: ");
	for (auto& it : vec) std::cout << it << " ";
	printf("\n");


	// reverse

	//printf("before reverse: ");
	//for (int i = 0;i < 5;i++) printf("%d ", arr[i]);
	//printf("\n");
	//std::reverse(arr, arr + n);
	//printf("after reverse: ");
	//for (int i = 0;i < 5;i++) printf("%d ", arr[i]);
	//printf("\n");

	//// we can also do
	//reverse(vec.begin() + 1, vec.begin() + 4);


	// finding max elem in any index range
	int a[5] = { 33,6,71,8,44 };
	int maxi = INT_MIN;
	// let 
	int i = 0, j = 4;
	for (int k = i;k <= j;k++) {
		if (a[k] > maxi) {
			maxi = a[k];
		}
	}
	std::cout << "max elem is: " << maxi << "\n";

	// this can also be done as:
	int el = *std::max_element(arr, arr + n); // std::max_element() returns an iterator 
	std::cout << "max of arr is: " << el << "\n";

	// also
	int minElem = *std::min_element(arr, arr + n);
	std::cout << "min elem is: " << minElem << "\n";

	// same can be done with vector as well as
	// int el = *std::max_element(v.begin(), v.end());


	// given a range and we need to find the sum of that range. ex: i and j are given  - tell me sum in the range i to j
	int sum = 0;
	i = 0, j = 3;
	for (int k = i;k <= j;k++) {
		sum += arr[k];
	}

	// another way - use accumulate(startIterator, endIterator, initialSum);
	int rangeSum = std::accumulate(arr, arr + n, 0);
	std::cout << "sum from begin to end of arr: " << rangeSum << "\n";

	// nums[] -> [1,4,5,2,1,12,1,13]
	// tell how many times element 1 has occured in the array
	int nums[8] = { 1, 4, 5, 2, 1, 12, 1, 2 };
	int cnt = 0, x=1;
	for (int i = 0;i < 8;i++) {
		if (nums[i] == x)cnt++;
	}
	std::cout << cnt << "\n";

	// using other way - count()
	// count(firstIterator, lastIterator, x)
	std::cout << "count of 1: " << std::count(nums, nums + 8, 1) << "\n";

	// finding an element 
	int ind = -1;
	x = 2;
	for (int i = 0;i < 8;i++) {
		if (nums[i] == x) {
			ind = i;
			break;
		}
	}
	//std::cout << "2 found at ind: " << ind << "\n";
	// using find():
	auto it = std::find(nums, nums + 8, 2); // returns an iterator 
	// pointing to the first instance of 2 or else pointing to the end() / arr+n
	ind = it - nums;
	std::cout << "2 found at ind: " << ind << "\n";

	//auto it2 = std::find(nums, nums + n, 10); // 10 is not present 
	//if (it2 == nums + 8) std::cout << "elem not present \n";
	//int elem;
	//printf("provide elem to find: ");
	//std::cin >> elem;
	//auto it2 = std::find(vec.begin(), vec.end(), elem);
	//if (it2 == vec.end()) printf("elem not found! \n");
	//else printf("elem found at index: %d \n", it2 - vec.begin());


	// searching - binary search algo
	// this algo only works on sorted arrays
	// arr[] -> {1, 5, 7, 9, 10}
	// x = 9
	// return true if 9 exists otherwise false

	std::sort(arr, arr + n);
	bool res = std::binary_search(arr, arr + n, 25); // log n complexity
	std::cout << (res ? "25 is present \n" : "not present \n");

	// works same for vectors as well

	// lower bound function
	// returns an iter. to the first element which is not less than x
	// 	arr[] ={1, 5, 7, 7, 8, 10, 10, 11, 11, 12};
	// x=10
	//int nums2[10] = { 1, 5, 7, 7, 8, 10, 10, 11, 11, 12 };
	//x = 10;
	//auto iter = std::lower_bound(nums2, nums2 + 10, 10);
	//std::cout << "lower bound of 10: " << *iter << "\n";

	//// for x =6
	//iter = std::lower_bound(nums2, nums2 + 10, 6);
	//std::cout << "lower bound of 6: " << *iter << "\n";


	// upper bound
	// returns an iterator which points to an element which is its just greater than x
	/*x = 10;
	iter = std::upper_bound(nums2, nums2 + 10, 10);
	std::cout << "upper bound of 10: " << *iter << "\n";*/

	// problem : find last occurence of x in arr
	// arr[] ={1, 5, 7, 7, 8, 10, 10, 11, 11, 12};
	// x = 8 solution: linear search, better: upper bound
	// answer: 4 for x==8
	//int index = -1;
	//x = 8;
	//index = std::upper_bound(nums2, nums2+10, 8) - nums2;
	//index -= 1;
	//if (index >= 0 && nums2[index] == x) {
	//	printf("first occ. at: %d \n", index); // prints 4
	//}
	//else {
	//	printf("not found \n");
	//}

	// problem : number of times x appear in array
	// if array is sorted, simple solution: upperbound - lowerbound
	/*int ans = std::upper_bound(nums2, nums2+10, 11) - std::lower_bound(nums2, nums2+10, 11);
	std::cout << "no. of 11: " << ans << "\n";*/

	// next permutation
	// string s = "abc"
	// all permutations are as follows:
	// abc
	// acb
	// bac
	// bca
	// cab
	// cba

	//std::string s = "abc";
	//std::cout << "string then: " << s << "\n";
	//bool res2 = std::next_permutation(s.begin(), s.end()); // if it gets to the next permutation it return a true otherwise false
	//// example if we do next_permutation("cba") - it returns a false
	//std::cout << "string now: " << s << "\n";

	// problem: given any random string print all its permutations
	// solution:
	/*std::string str = "bca";
	std::cout << str << "\n";
	while (std::next_permutation(str.begin(), str.end()))
	{
			std::cout << str << std::endl;
	}*/

	// we also have prev_permutation(iter1, iter2)


	// COMPARATOR
	//int arr2[5] = { 12,5,11,6,19 };
	//std::cout << "before sorting: ";
	//for (auto& it : arr2) {
	//	std::cout << it << " ";
	//}
	//std::sort(arr2, arr2+5, comp); // sorting in the descending order using comparator
	//std::cout << "after soting: ";
	//for (auto& it : arr2) {
	//	std::cout << it << " ";
	//}

	// task: sort pair as: first values in ascending, second values in descending if first is same
	std::pair<int, int>p[] = {{2,1},{1,3},{2,5}, {4,5}};
	/*std::sort(p, p+4);
	printf("after sort: \n");
	for (auto& it : p) {
		std::cout << it.first << " " << it.second << "\n";
	}*/

	std::sort(p, p + 4, comp);
	printf("after sort: \n");
	for (auto& it : p) {
		std::cout << it.first << " " << it.second << "\n";
	}
	// task done! 
	printf("\n");

	return 0;
}
