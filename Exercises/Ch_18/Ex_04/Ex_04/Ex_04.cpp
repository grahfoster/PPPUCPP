#include <iostream>

//int strlength(const char* s)
//{
//	int length = 0;
//	while (*s) {
//		++length;
//		++s;
//	}
//
//	return length;
//}
//
//char* strdupe(const char* s)
//{
//	const int length = strlength(s);
//	char* cp = new char[length + 1];
//
//	while (*s)
//		* cp++ = *s++;
//	*cp = *s;
//
//	return cp - length;
//}
//
//char* findx(const char* s, const char* x)
//{
//	while (*s++)
//		if (*s == *x) {
//			char* cp = const_cast<char*>(s);
//			while (*s++ == *x++)
//				if (!*x)
//					return cp;
//		}
//	return nullptr;
//}
//
//int strcomp(const char* s1, const char* s2)
//{
//	const int length1 = strlength(s1);
//	const int length2 = strlength(s2);
//	const int length = length1 < length2 ? length1 : length2;
//	for (int i = 0; i < length; ++i) {
//		if (*s1 < *s2)
//			return 1;
//		if (*s1 > * s2)
//			return -1;
//		++s1;
//		++s2;
//	}
//	if (length1 == length2)
//		return 0;
//}

char* strdupe(const char* s, int n)
{
	char* cp = new char[n];

	for (int i = 0; i < n; ++i)
		cp[i] = s[i];

	return cp;
}

char* findx(const char* s, int n1, const char* x, int n2)
{
	for (int i = 0; i < n1; ++i)
		if (s[i] == x[0]) {
			for (int j = 0; j < n2; ++j)
				if (s[i + j] != x[j])
					break;
			return const_cast<char*>(&s[i]);
		}
	return nullptr;
}

int strcomp(const char* s1, int n1, const char* s2, int n2)
{
	const int length = n1 < n2 ? n1 : n2;
	for (int i = 0; i < length; ++i) {
		if (s1[i] < s2[i])
			return 1;
		if (s1[i] > s2[i])
			return -1;
	}
	if (n1 == n2)
		return 0;
}

int main()
try {
	/*char s1[] = { 's', 't', 'r', 'i', 'n', 'g' };
	char* cp1 = strdupe(s1);

	const int length1 = strlength(cp1);
	for (int i = 0; i < length1; ++i)
		std::cout << *cp1++;
	std::cout << '\n';

	delete[](cp1 - length1);

	char* s2 = new char[6]{ 's', 't', 'r', 'i', 'n', 'g' };
	char* cp2 = strdupe(s2);

	const int length2 = strlength(cp2);
	for (int i = 0; i < length2; ++i)
		std::cout << *cp2++;
	std::cout << '\n';

	delete[] s2;
	delete[](cp2 - length2);

	char s3[] = { 's', 't', 'r', 'i', 'n', 'g' };
	char x1[] = { 't', 'r', 'i', 'n' };

	char* cp3 = findx(s3, x1);
	if (cp3)
		std::cout << "String x begins at address " << static_cast<void*>(cp3) << ".\n";
	else
		std::cout << "String x is not contained within string s.\n";

	char* s4 = new char[6]{ 's', 't', 'r', 'i', 'n', 'g' };
	char x2[] = { 't', 'r', 'i', 'n' };

	char* cp4 = findx(s4, x2);
	if (cp4)
		std::cout << "String x begins at address " << static_cast<void*>(cp4) << ".\n";
	else
		std::cout << "String x is not contained within string s.\n";

	delete[] s4;
	delete[] x2;

	char s5[] = { 's', 't', 'r', 'i', 'n', 'g', '1' };
	char s6[] = { 's', 't', 'r', 'i', 'n', 'g', '2' };

	const int i1 = strcomp(s5, s6);
	std::cout << "String 1 ";
	switch (i1) {
	case 1:
		std::cout << "comes before";
		break;
	case -1:
		std::cout << "comes after";
		break;
	default:
		std::cout << "is lexicographically equal to";
	}
	std::cout << " string 2.\n";

	char* s7 = new char[7]{ 's', 't', 'r', 'i', 'n', 'g', '1' };
	char* s8 = new char[7]{ 's', 't', 'r', 'i', 'n', 'g', '2' };

	const int i2 = strcomp(s7, s8);
	std::cout << "String 1 ";
	switch (i2) {
	case 1:
		std::cout << "comes before";
		break;
	case -1:
		std::cout << "comes after";
		break;
	default:
		std::cout << "is lexicographically equal to";
	}
	std::cout << " string 2.\n";

	delete[] s7;
	delete[] s8;*/

	char s1[] = "string";
	char* cp1 = strdupe(s1, 6);

	for (int i = 0; i < 6; ++i)
		std::cout << cp1[i];
	std::cout << '\n';

	delete[] cp1;

	char s2[] = { 's', 't', 'r', 'i', 'n', 'g' };
	char* cp2 = strdupe(s1, 6);

	for (int i = 0; i < 6; ++i)
		std::cout << cp2[i];
	std::cout << '\n';

	delete[] cp2;

	char* s3 = new char[6]{ 's', 't', 'r', 'i', 'n', 'g' };
	char* cp3 = strdupe(s3, 6);

	for (int i = 0; i < 6; ++i)
		std::cout << cp3[i];
	std::cout << '\n';

	delete[] s3;
	delete[] cp3;

	char s4[] = "string";
	char x1[] = "trin";

	char* cp4 = findx(s4, 6, x1, 4);
	if (cp4)
		std::cout << "String x begins at address " << static_cast<void*>(cp4) << ".\n";
	else
		std::cout << "String x is not contained within string s.\n";

	char s5[] = { 's', 't', 'r', 'i', 'n', 'g' };
	char x2[] = { 't', 'r', 'i', 'n' };

	char* cp5 = findx(s5, 6, x2, 4);
	if (cp5)
		std::cout << "String x begins at address " << static_cast<void*>(cp5) << ".\n";
	else
		std::cout << "String x is not contained within string s.\n";

	char* s6 = new char[6]{ 's', 't', 'r', 'i', 'n', 'g' };
	char* x3 = new char[4]{ 't', 'r', 'i', 'n' };

	char* cp6 = findx(s6, 6, x3, 4);
	if (cp6)
		std::cout << "String x begins at address " << static_cast<void*>(cp6) << ".\n";
	else
		std::cout << "String x is not contained within string s.\n";

	delete[] s6;
	delete[] x3;

	char s7[] = "string1";
	char s8[] = "string2";

	const int i1 = strcomp(s7, 7, s8, 7);
	std::cout << "String 1 ";
	switch (i1) {
	case 1:
		std::cout << "comes before";
		break;
	case -1:
		std::cout << "comes after";
		break;
	default:
		std::cout << "is lexicographically equal to";
	}
	std::cout << " string 2.\n";

	char s9[] = { 's', 't', 'r', 'i', 'n', 'g', '1' };
	char s10[] = { 's', 't', 'r', 'i', 'n', 'g', '2' };

	const int i2 = strcomp(s9, 7, s10, 7);
	std::cout << "String 1 ";
	switch (i2) {
	case 1:
		std::cout << "comes before";
		break;
	case -1:
		std::cout << "comes after";
		break;
	default:
		std::cout << "is lexicographically equal to";
	}
	std::cout << " string 2.\n";

	char* s11 = new char[7]{ 's', 't', 'r', 'i', 'n', 'g', '1' };
	char* s12 = new char[7]{ 's', 't', 'r', 'i', 'n', 'g', '2' };

	const int i3 = strcomp(s11, 7, s12, 7);
	std::cout << "String 1 ";
	switch (i3) {
	case 1:
		std::cout << "comes before";
		break;
	case -1:
		std::cout << "comes after";
		break;
	default:
		std::cout << "is lexicographically equal to";
	}
	std::cout << " string 2.\n";

	delete[] s11;
	delete[] s12;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}