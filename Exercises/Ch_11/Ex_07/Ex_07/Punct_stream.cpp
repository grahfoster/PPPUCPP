#include "Punct_stream.h"
#include <vector>

Punct_stream& Punct_stream::operator>>(std::string& s)
{
	while (!(iss >> s)) {
		if (!is || iss.bad())
			return *this;
		iss.clear();

		std::string buffer;
		std::getline(is, buffer);
		format_line(buffer);
		iss.str(buffer);
	}
	return *this;
}

Punct_stream::operator bool()
{
	return !(is.fail() || is.bad());
}

void Punct_stream::format_line(std::string & buffer)
{
	for (int i = 0; i < buffer.size(); ++i) {
		if (buffer[i] == '\"')
			while (++i && i < buffer.size() && buffer[i] != '\"')
				buffer[i] = tolower(buffer[i]);

		if (buffer[i] == '\'' && is_contraction(buffer, i + 1)) {
			buffer[i] = 'o';
			buffer.insert(i - 1, " ");
		}

		if (buffer.size() > i + 1 && buffer[i] == '-'
			&& isalpha(buffer[i - 1]) && isalpha(buffer[i + 1]))
			continue;

		if (is_punctuation(buffer[i]))
			buffer[i] = ' ';

		buffer[i] = tolower(buffer[i]);
	}
}

bool Punct_stream::is_contraction(std::string & buffer, int length)
{
	static const std::vector<std::string> contractions{
		"aren't", "couldn't", "don't", "haven't"
	};

	std::string word = buffer.substr(0, length);
	for (std::string contraction : contractions)
		if (buffer.size() > length &&
			word + buffer[length] == contraction)
			return true;
	return false;
}

bool Punct_stream::is_punctuation(char c)
{
	static const std::vector<char> punctuations{
		'.', ';', ',', '?', '-', '\''
	};

	for (char punctuation : punctuations)
		if (c == punctuation)
			return true;
	return false;
}