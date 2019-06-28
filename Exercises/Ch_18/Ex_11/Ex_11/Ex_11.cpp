#include "Skip_list.h"
#include <iostream>

int main()
try {
	const std::vector<std::string> months{ 
		"January", "February", "March", "April", "May", "June", 
		"July", "August", "September", "October", "November", "December" 
	};
	Skip_list sl(4, 2);
	
	for (std::string month : months)
		sl.insert(month);
	std::cout << "English Months: \n";
	sl.print(std::cout);

	const std::vector<std::string> sp_months{
		"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
		"Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
	};

	for (std::string sp_month : sp_months)
		sl.insert(sp_month);
	std::cout << "\nEnglish and Spanish Months: \n";
	sl.print(std::cout);

	for (std::string month : months)
		sl.remove(month);
	std::cout << "\nSpanish Months: \n";
	sl.print(std::cout);

	std::cout << '\n';
	const std::string month{ "December" };
	if (sl.find(month))
		std::cout << "Found ";
	else
		std::cout << "Did not find ";
	std::cout << month << ".\n\n";

	const std::string s_month{ "Diciembre" };
	if (sl.find(s_month))
		std::cout << "Found ";
	else
		std::cout << "Did not find ";
	std::cout << s_month << ".\n";
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}