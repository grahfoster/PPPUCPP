#include <iostream>
#include <iomanip>
#include <vector>

struct Info {
	std::string last_name;
	std::string first_name;
	std::string telephone;
	std::string email;
};

int main()
try {
	int birth_year = 1991;
	int age = 27;

	std::cout << std::showbase << "Decimal: " << birth_year << '\t' <<
		"Hexadecimal: " << std::hex << birth_year << '\t' <<
		"Octal: " << std::oct << birth_year << "\n\n";

	std::cout << std::dec << "Age: " << age << "\n\n";

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	std::cin >> a >> std::oct >> b >> std::hex >> c >> d;
	std::cout << a << '\t' << b << '\t' << c << '\t' << d << "\n\n";

	double num = 1234567.89;

	std::cout << num << '\t' <<
		std::fixed << num << '\t' <<
		std::scientific << num << "\n\n";

	const int num_dividers = 5;
	const int name_width = 15;
	const int telephone_width = 20;
	const int email_width = 30;

	std::vector<Info> infos{
		Info{"Foster", "Gregory", "(585) 208-8756", "grahfoster@gmail.com"},
		Info{"Williams", "Ian", "(585) 482-7176", "iwilliams@risd.edu"},
		Info{"Homerin", "Elias", "(585) 782-1026", "elihomerin@gmail.com"},
		Info{"Dwyer-Reynolds", "Conor", "(585) 209-4456", "cdreynolds@yale.edu"},
		Info{"Dwyer-Reynolds", "Emma", "(585) 209-4557", "edreynolds@rochester.edu"},
		Info{"Pietrobono", "Jessica", "(718) 492-1080", "jnpietrobono@gmail.com"}
	};

	for (int i = 0; i < num_dividers + name_width + name_width + telephone_width + email_width; ++i)
		std::cout << '-';
	std::cout << '\n';

	std::cout << '|' << std::setw(name_width) << "Last Name" <<
		'|' << std::setw(name_width) << "First Name" <<
		'|' << std::setw(telephone_width) << "Telephone" <<
		'|' << std::setw(email_width) << "Email" << "|\n";

	for (int i = 0; i < num_dividers + name_width + name_width + telephone_width + email_width; ++i)
		std::cout << '-';
	std::cout << '\n';

	for (Info info : infos) {
		std::cout << '|' << std::setw(name_width) << info.last_name <<
			'|' << std::setw(name_width) << info.first_name <<
			'|' << std::setw(telephone_width) << info.telephone <<
			'|' << std::setw(email_width) << info.email << "|\n";
	}

	for (int i = 0; i < num_dividers + name_width + name_width + telephone_width + email_width; ++i)
		std::cout << '-';
	std::cout << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}