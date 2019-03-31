#include "../../../../std_lib_facilities.h"

void drill();

int main() {
	try {
		drill();
		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
}

//void drill() {
//	cout << "Success!\n";
//}

//void drill() {
//	cout << "Success!\n";
//}

//void drill() {
//	cout << "Success" << "!\n";
//}

//void drill() {
//	cout << "Success!" << endl;
//}

//void drill() {
//	int res = 7;
//	vector<int> v(10);
//	v[5] = res;
//	cout << "Success!\n";
//}

//void drill() {
//	vector<int> v(10);
//	v[5] = 7;
//	if (v[5] == 7)
//		cout << "Success!\n";
//}

//void drill() {
//	if (true)
//		cout << "Success!\n";
//	else
//		cout << "Fail!\n";
//}

//void drill() {
//	bool c = false;
//	if (!c)
//		cout << "Success!\n";
//	else
//		cout << "Fail!\n";
//}

//void drill() {
//	string s = "ape";
//	bool c = "fool" < s;
//	if (!c)
//		cout << "Success!\n";
//}

//void drill() {
//	string s = "ape";
//	if (s != "fool")
//		cout << "Success!\n";
//}

//void drill() {
//	string s = "ape";
//	if (s != "fool")
//		cout << "Success!\n";
//}

//void drill() {
//	string s = "ape";
//	if (s < "fool")
//		cout << "Success!\n";
//}

//void drill() {
//	vector<char> v(5);
//	for (int i = 0; i < v.size(); ++i);
//	cout << "Success!\n";
//}

//void drill() {
//	vector<char> v(5);
//	for (int i = 0; i < v.size(); ++i);
//	cout << "Success!\n";
//}

//void drill() {
//	string s = "Success!\n";
//	for (int i = 0; i < s.length(); ++i)
//		cout << s[i];
//}

//void drill() {
//	if (true)
//		cout << "Success!\n";
//	else
//		cout << "Fail!\n";
//}

//void drill() {
//	int x = 2000;
//	int c = x;
//	if (c == 2000)
//		cout << "Success!\n";
//}

//void drill() {
//	string s = "Success!\n";
//	for (int i = 0; i < s.length(); ++i)
//		cout << s[i];
//}

//void drill() {
//	vector<int> v(5);
//	for (int i = 0; i < v.size(); ++i);
//	cout << "Success!\n";
//}

//void drill() {
//	int i = 0;
//	int j = 9;
//	while (i < 10)
//		++i;
//	if (j < i)
//		cout << "Success!\n";
//}

//void drill() {
//	int x = 2;
//	double d = 5.0 / (x - 1);
//	if (d > 2 * x + 0.5)
//		cout << "Success!\n";
//}

//void drill() {
//	string s = "Success!\n";
//	for (int i = 0; i < s.length(); ++i)
//		cout << s[i];
//}

//void drill() {
//	int i = 0;
//	while (i < 10)
//		++i;
//	if (i == i)
//		cout << "Success!\n";
//}

//void drill() {
//	int x = 4;
//	double d = 5.0 / (x - 2);
//	if (d < 2 * x + 0.5)
//		cout << "Success!\n";
//}

void drill() {
	cout << "Success!\n";
}