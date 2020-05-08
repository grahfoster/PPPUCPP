#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

std::string get_san_string(const std::string s)
{
	std::map<std::string, std::string> contractions{
		{ "aren't", "are not" }, { "can't", "cannot" }, { "couldn't", "could not" },
		{ "didn't", "did not" }, { "doesn't", "does not" }, { "don't", "do not" },
		{ "hadn't", "had not" }, { "hasn't", "has not" }, { "haven't", "have not" },
		{ "he'd", "he had" }, { "he'll", "he will" }, { "i'd", "i would" },
		{ "i'll", "i will" }, { "i'm", "i am" }, { "i've", "i have" },
		{ "isn't", "is not" }, { "it's", "it is" }, { "let's", "let us" },
		{ "she'd", "she had" }, { "she'll", "she will" }, { "she's", "she is" },
		{ "that's", "that is" }, { "there's", "there is" }, { "they'd", "they had" },
		{ "they'll", "they will" }, { "they're", "they are" }, { "they've", "they have" },
		{ "wasn't", "was not" }, { "we'd", "we had" }, { "we'll", "we will" },
		{ "we're", "we are" }, { "we've", "we have" }, { "weren't", "were not" },
		{ "what's", "what is" }, { "won't", "will not" }, { "wouldn't", "would not" },
		{ "you'd", "you had" }, { "you'll", "you will" }, { "you're", "you are" },
		{ "you've", "you have" }
	};

	std::string san_s;
	for (char c : s) {
		if (ispunct(c) && c != '\'' && c != '-')
			continue;
		san_s += tolower(c);
	}
	if (contractions.find(san_s) != contractions.end())
		san_s = contractions[san_s];
	if (san_s.size() > 1) {
		std::string ending = san_s.substr(san_s.size() - 2, 2);
		if (ending == "'s")
			san_s = san_s.substr(0, san_s.size() - 2);
	}
	return san_s;
}

int main()
try {
	std::ifstream ifs{ "Ex_13_input.txt" };
	if (!ifs)
		throw std::exception("input file not found");
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::ofstream ofs{ "Ex_13_output.txt" };
	if (!ofs)
		throw std::exception("outpout file not found");

	std::vector<std::string> buffer;
	std::set<std::string> dict;
	for (std::string s; ifs >> s;) {
		std::string san_s = get_san_string(s);
		buffer.push_back(san_s);
		dict.insert(san_s);
	}

	if (!ifs & !ifs.eof())
		throw std::exception("bad input");

	for (std::string s : buffer) {
		if (s.empty())
			continue;
		if (s.back() == 's') {
			std::string temp = s;
			temp.pop_back();
			if (dict.find(temp) != dict.end()) {
				ofs << temp << ' ';
				continue;
			}
		}
		ofs << s << ' ';
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}