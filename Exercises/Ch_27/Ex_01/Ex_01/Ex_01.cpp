#include <stdio.h>

int my_strlen(const char* s)
{
	int length = 0;
	while (*s++)
		length++;
	return length;
}

int my_strcmp(const char* s1, const char* s2)
{
	while (*s1 && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

char* my_strcpy(char* s1, const char* s2)
{
	while (*s1++ = *s2++);
	return s1;
}

int main() {
	char s1[] = "string";
	char s2[] = "strong";

	printf("%d\n", my_strlen(s1));

	printf("%d\n", my_strcmp(s1, s2));

	my_strcpy(s2, s1);
	printf("%s\n", s2);
}