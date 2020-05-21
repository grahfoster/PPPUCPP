#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
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
		if (*p == "||||") {
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
	std::regex pattern{ R"(From: (.*))" };

	for (const auto& vs : *msg) {
		std::smatch matches;
		if (std::regex_search(vs, matches, pattern)) {
			s = matches[1];
			return true;
		}
	}
	return false;
}

std::string find_subject(const Message* msg)
{
	std::regex pattern{ R"(Subject: (.*))" };

	for (const auto& vs : *msg) {
		std::smatch matches;
		if (std::regex_search(vs, matches, pattern))
			return matches[1];
	}
	return "";
}

int main()
try {
	Mail_file mf{ "Ex_04_input.txt" };

	std::multimap<std::string, const Message*> senders;

	for (const auto& msg : mf) {
		std::string s;
		if (find_from_addr(&msg, s))
			senders.insert(std::make_pair(s, &msg));
	}

	std::string sender;
	std::cout << "Enter sender name you would like to see subjects from:\n";
	std::getline(std::cin, sender);

	std::cout << "\nSubjects:\n";
	auto p = senders.equal_range(sender);
	for (auto q = p.first; q != p.second; ++q)
		std::cout << '\t' << find_subject(q->second) << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}