#include <iostream>

//class B1 {
//public:
//	virtual void vf() { std::cout << "B1::vf()"; }
//	void f() { std::cout << "B1::f()"; }
//	virtual void pvf() = 0;
//};
//
//class D1 : public B1 {
//public:
//	void vf() override { std::cout << "D1::vf()"; }
//	void f() { std::cout << "D1::f()"; }
//};
//
//class D2 : public D1 {
//public:
//	void pvf() override { std::cout << "D2::pvf()"; }
//};

class B2 {
public:
	virtual void pvf() = 0;
};

class D21 : public B2 {
public:
	void pvf() override { std::cout << s; }
private:
	std::string s{ "D21::pvf()" };
};

class D22 : public B2 {
public:
	void pvf() override { std::cout << i; }
	void f(B2& b2) { b2.pvf(); }
private:
	int i = 0;
};

int main()
try {
	/*D1 d1;
	d1.vf();
	d1.f();

	B1& b1 = d1;
	b1.vf();
	b1.f();*/

	/*D2 d2;
	d2.vf();
	d2.f();
	d2.pvf();*/

	D21 d21;
	D22 d22;
	d22.f(d21);
	d22.f(d22);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}