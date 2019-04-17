#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Name_pairs {
public:
	void read_names();
	void read_ages();
	void sort_pairs();
	void print_pairs();
private:
	vector<string> names;
	vector<double> ages;
};