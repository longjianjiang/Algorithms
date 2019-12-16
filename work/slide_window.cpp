#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Store {
private:
	int window_size;
	int left = 0, right = 0;
	vector<int> arr;

public:
	Store(vector<int> source, int ws);
	vector<int> get_part();
	void moveLeft(int size = 1);
	void reset();
};

Store::Store(vector<int> source, int ws) {
	arr = source;
	window_size = ws;
	right = ws-1;
}

vector<int> Store::get_part() {
	int nsize = right-left+1;
	auto start = arr.begin()+left;
	if (start >= arr.end()) {
		return {};
	}
	auto end = start+nsize;
	if (end > arr.end()) { end = arr.end(); }
	return vector<int>(start, end);
}

void Store::moveLeft(int size) {
	left += size;
	right += size;
}

void Store::reset() {
	left = 0; right = window_size-1;
}

// 1
// 2
// 3
// 1
// 1
// 1

void show_arr_one_dimensional(vector<int> arr) {
	cout << "[";
	for (int i = 0; i < arr.size(); ++i) {
		int num = arr[i];
		if (i == arr.size()-1) {
			cout << num;
		} else {
			cout << num << " ";
		}
	}
	cout << "]\n";
}

void show_arr_two_dimensional(vector<vector<int>> arr) {
	for (auto v: arr) {
		show_arr_one_dimensional(v);
	}
}

void unit_test() {
	vector<int> source = {1, 2, 3, 1, 1, 1};
	Store s(source, 3);

	for (int i = 0; i < 7; ++i) {
		show_arr_one_dimensional(s.get_part());
		s.moveLeft(2);
	}
}

int main() {
	unit_test();
	return 0;
}
