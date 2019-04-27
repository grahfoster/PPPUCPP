#include "../../../../std_lib_facilities.h"

void set_input_stream(ifstream&);
void set_output_stream(ofstream&);
void convert_file(ifstream&, ofstream&);

int main()
try {
	ifstream ifs;
	ofstream ofs;

	cout << "Enter input file name:\n";
	set_input_stream(ifs);

	cout << "Enter ouput file name:\n";
	set_output_stream(ofs);

	convert_file(ifs, ofs);
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}

string get_file_name()
{
	string file_name;
	cin >> file_name;
	if (cin.eof())
		throw exception("no input");
	if (!cin)
		throw exception("invalid input");
	return file_name;
}

void set_input_stream(ifstream& ifs)
{
	ifs.open(get_file_name());
	if (!ifs)
		throw exception("couldn't open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
}

void set_output_stream(ofstream & ofs)
{
	ofs.open(get_file_name(), ios_base::binary);
	if (!ofs)
		throw exception("couldn't open file");
}

void convert_file(ifstream & ifs, ofstream & ofs)
{
	vector<char> buffer;

	for (char c; ifs >> c;)
		buffer.push_back(c);
	if (!ifs.eof() && ifs.fail())
		throw exception("invalid input");

	for (char c : buffer)
		ofs.write(as_bytes(c), sizeof(char));
	if (!ofs.eof() && ofs.fail())
		throw exception("invalid output");
}