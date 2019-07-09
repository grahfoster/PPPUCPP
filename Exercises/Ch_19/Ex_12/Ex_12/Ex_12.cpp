#include <iostream>
#include <fstream>

class File_handle {
public:
	File_handle(const std::string&);
	~File_handle() { fs.close(); }
private:
	std::fstream fs;
};

File_handle::File_handle(const std::string& fn)
{
	fs.open(fn);
	if (!fs)
		throw std::exception("file could not be opened");
	fs.exceptions(fs.exceptions() | std::ios_base::badbit);
}

void f() { File_handle fh{ "Ex_12_input.txt" }; }

int main()
try {
	f();
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}