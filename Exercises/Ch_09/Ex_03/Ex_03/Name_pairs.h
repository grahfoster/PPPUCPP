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
	vector<string> get_names() const { return names; }
	vector<double> get_ages() const { return ages; }
private:
	vector<string> names;
	vector<double> ages;
};

void operator<<(ostream&, const Name_pairs&);
bool operator==(const Name_pairs&, const Name_pairs&);
bool operator!=(const Name_pairs&, const Name_pairs&);
