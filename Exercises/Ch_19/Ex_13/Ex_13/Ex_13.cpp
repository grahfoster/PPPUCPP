#include <algorithm>
#include <iostream>

class Tracer {
public:
	Tracer(const std::string&, const std::string&, const std::string&, const std::string&);
	Tracer(const Tracer&);
	~Tracer() { std::cout << destr_str << '\n'; }

	Tracer& operator=(const Tracer&);
private:
	std::string constr_str;
	std::string destr_str;
	std::string cpy_constr_str;
	std::string cpy_assgn_str;
};

Tracer::Tracer(const std::string& cs, const std::string& ds, const std::string& ccs, const std::string& cas) :
	constr_str{ cs }, destr_str{ ds }, cpy_constr_str{ ccs }, cpy_assgn_str{ cas }
{
	std::cout << constr_str << '\n';
}

Tracer::Tracer(const Tracer& trcr)
{
	constr_str = trcr.constr_str;
	destr_str = trcr.destr_str;
	cpy_constr_str = trcr.cpy_constr_str;
	cpy_assgn_str = trcr.cpy_assgn_str;
	std::cout << cpy_constr_str << '\n';
}

Tracer& Tracer::operator=(const Tracer& trcr)
{
	constr_str = trcr.constr_str;
	destr_str = trcr.destr_str;
	cpy_constr_str = trcr.cpy_constr_str;
	cpy_assgn_str = trcr.cpy_assgn_str;
	std::cout << cpy_assgn_str << '\n';
	return *this;
}

struct A { Tracer mmb_trcr{ "constructing", "destroying", "copy constructing", "copy assigning" }; };

Tracer glb_trcr{ "constructing", "destroying", "copy constructing", "copy assigning" };

int main()
try {
	Tracer lcl_trcr1{ "constructing", "destroying", "copy constructing", "copy assigning" };
	Tracer lcl_trcr2{ lcl_trcr1 };

	A a;

	Tracer* trcr_ptr{ new Tracer{ "constructing", "destroying", "copy constructing", "copy assigning" } };
	*trcr_ptr = lcl_trcr1;
	delete trcr_ptr;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}