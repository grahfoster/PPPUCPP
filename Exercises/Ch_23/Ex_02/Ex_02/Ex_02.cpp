#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using Line_iter = std::vector<std::string>::const_iterator;

class Message {
public:
	Message(Line_iter li1, Line_iter li2) : first{ li1 }, second{ li2 } {};
	Line_iter begin() const { return first; }
	Line_iter end() const { return second; }
private:
	Line_iter first;
	Line_iter second;
};

using Mess_iter = std::vector<Message>::const_iterator;

class Mail_file {
public:
	std::string name;
	std::vector<std::string> lines;
	std::vector<Message> msgs;

	Mail_file(const std::string&);

	Mess_iter begin() const { return msgs.begin(); }
	Mess_iter end() const { return msgs.end(); }
};

Mail_file::Mail_file(const std::string& file_name)
{
	std::ifstream ifs{ file_name };
	if (!ifs)
		throw std::exception("couldn't open input file");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	for (std::string s; std::getline(ifs, s);)
		lines.push_back(s);
	if (!ifs && !ifs.eof())
		throw std::exception("bad input");

	auto first = lines.begin();
	for (auto p = first; p != lines.end(); ++p)
		if (*p == "----") {
			msgs.push_back(Message{ first, p });
			first = p + 1;
		}
}

int is_prefix(const std::string& s, const std::string& p)
{
	int n = p.size();
	if (std::string(s, 0, n) == p)
		return n;
	return 0;
}

bool find_from_addr(const Message* msg, std::string& s)
{
	for (const auto& vs : *msg)
		if (int n = is_prefix(vs, "From: ")) {
			s = std::string(vs, n);
			return true;
		}
	return false;
}

std::string find_subject(const Message* msg)
{
	for (const auto& vs : *msg)
		if (int n = is_prefix(vs, "Subject: "))
			return std::string(vs, n);
	return "";
}

int main()
try {
	Mail_file mf{ "Ex_02_input.txt" };

	std::multimap<std::string, const Message*> subjects;

	for (const auto& msg : mf)
		if (!find_subject(&msg).empty())
			subjects.insert(std::make_pair(find_subject(&msg), &msg));

	std::string query;
	std::cout << "Please enter a string to search for in the subject lines:\n";
	std::cin >> query;

	for (const auto& psm : subjects) {
		if (psm.first.find(query) != std::string::npos) {
			for (const auto& vs : *psm.second) {
				for (const auto& li : vs)
					std::cout << li;
				std::cout << '\n';
			}
			std::cout << '\n';
		}
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}