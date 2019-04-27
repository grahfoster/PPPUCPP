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

		for (int i = 0; i < buffer.size(); ++i) {
			if (buffer[i] == '\"')
				while (++i && i < buffer.size() && buffer[i] != '\"');

			if (is_punct(buffer[i]))
				buffer[i] = ' ';
		}

		iss.str(buffer);
	}
	return *this;
}

Punct_stream::operator bool()
{
	return !(is.fail() || is.bad());
}

bool Punct_stream::is_punct(char c)
{
	static const std::vector<char> punct_chars{
		'.', ';', ',', '?', '-', '\''
	};

	for (char punct_char : punct_chars)
		if (c == punct_char)
			return true;
	return false;
}