#include <iostream>
#include <sstream>

class Punct_stream {
public:
	Punct_stream(std::istream& is) : is{ is } {}

	Punct_stream& operator>>(std::string&);
	operator bool();
private:
	std::istream& is;
	std::stringstream iss;

	bool is_punct(char);
};