#include <iostream>
#include <vector>
#include <fstream>

double* get_from_jack(const int* count)
{
	double* jack_data = new double[*count];
	std::ifstream ifs{ "Ex_02_input1.txt" };
	if (!ifs)
		throw std::exception("input file not found");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	for (int i = 0; i < *count; ++i)
		ifs >> jack_data[i];
	if (!ifs && !ifs.eof())
		throw std::exception("bad input format");

	return jack_data;
}

std::vector<double>* get_from_jill()
{
	std::vector<double>* jill_data = new std::vector<double>;
	std::ifstream ifs{ "Ex_02_input2.txt" };
	if (!ifs)
		throw std::exception("input file not found");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	for (double d; ifs >> d; jill_data->push_back(d));
	if (!ifs && !ifs.eof())
		throw std::exception("bad input format");

	return jill_data;
}

double* high(double* first, double* last)
{
	double* high = first;
	for (; first != last; ++first)
		if (*high < *first)
			high = first;
	return high;
}

int main()
try {
	constexpr int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	std::vector<double>* jill_data = get_from_jill();
	std::vector<double>& v = *jill_data;

	auto jack_high = high(jack_data, jack_data + jack_count);
	auto jill_high = high(&v[0], &v[0] + v.size());

	if (jack_high == &jack_data[jack_count])
		std::cout << "Jack's data was empty.\n";
	else
		std::cout << "Jack's max: " << *jack_high << '\n';
	if (jill_high == &v[0] + v.size())
		std::cout << "Jill's data was empty.\n";
	else
		std::cout << "Jill's max: " << *jill_high << '\n';

	delete[] jack_data;
	delete jill_data;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}