#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void* safe_malloc(size_t n)
{
	void* p = malloc(n);
	if (!p) {
		fprintf(stderr, "Error: failed to allocate %zu bytes.\n", n);
		exit(1);
	}
	return p;
}

int compare(const void* a, const void* b)
{
	return(strcmp(*((char**)a), *((char**)b)));
}

int main()
{
	const int num_words = 10;
	char** words = (char**)safe_malloc(sizeof(char*) * num_words);
	int i;
	int j;
	char c;

	printf("Please enter %d words:\n", num_words);
	for (i = 0; i < num_words; ++i) {
		const int buffer_size = 100;
		char* buffer = (char*)safe_malloc(sizeof(char) * buffer_size);

		while ((c = getchar()) != EOF && isspace(c));
		ungetc(c, stdin);

		for (j = 0; j < buffer_size - 1 && (c = getchar()) != EOF && !isspace(c); ++j)
			buffer[j] = c;
		buffer[j] = 0;
		words[i] = buffer;
	}

	qsort(words, num_words, sizeof(char*), compare);
	for (i = 0; i < num_words; ++i)
		printf("%s\n", words[i]);

	for (i = 0; i < num_words; ++i)
		free(words[i]);
}

