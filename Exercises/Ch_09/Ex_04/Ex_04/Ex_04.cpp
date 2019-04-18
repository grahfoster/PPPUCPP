#include "../../../../std_lib_facilities.h"

struct X {	// define a structure "X"
	void f(int x) {	// define a member function "f()" of structure "X"
		struct Y {	// define a structure "Y" within the scope of the member function "f()" of structure "X"
			int f() {	// define a member function "f()" of structure "Y"
				return 1;
			}
			int m;	// define an integer variable "m"
		};
		int m;	// define an integer variable "m"
		m = x;	// assign the value of argument "x" to "m"
		Y m2;	// define a "Y" variable "m2"
		return f(m2.f());	// return 1
	}
	int m;	// define an integer variable "m"
	void g(int m) {	// define a member function "g()" of structure "X"
		if (m)	// use the integer value "m" provided as the function argument
			f(m + 2);	// return 1
		else {
			g(m + 2);	// infinite loop
		}
	}
	X() {}	// declare an empty constructor for structure "X"
	void m3() {}	// declare a member function "m3()" of structure "X"
	void main() {	// define a member function "main()" of structure "X"
		X a;	// define an "X" variable "a"
		a.f(2);	// return 1
	}
};