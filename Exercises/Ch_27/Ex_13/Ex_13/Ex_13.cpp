#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

struct Buffer {
	char* text;
	int size;
	int space;
};

void* safe_malloc(size_t n)
{
	void* p = malloc(n);
	if (!p) {
		fprintf(stderr, "Error: failed to allocate %zu bytes.\n", n);
		exit(1);
	}
	return p;
}

void destroy_buffer(struct Buffer* buffer)
{
	free(buffer->text);
	free(buffer);
}

void expand(struct Buffer* buffer)
{
	assert(buffer);
	buffer->space *= 2;
	{
		char* temp = (char*)safe_malloc(sizeof(char) * buffer->space);
		memcpy(temp, buffer->text, sizeof(char) * buffer->size);
		free(buffer->text);
		buffer->text = temp;
	}
}

void append(struct Buffer* buffer, char c)
{
	if (buffer->size == buffer->space)
		expand(buffer);
	buffer->text[buffer->size] = c;
	++buffer->size;
}

char* get_string()
{
	struct Buffer buffer;
	char c;

	buffer.text = (char*)safe_malloc(sizeof(char));
	buffer.size = 0;
	buffer.space = 1;

	while ((c = getchar()) != EOF && isspace(c));
	do {
		append(&buffer, c);
	} while ((c = getchar()) != EOF && !isspace(c));
	append(&buffer, 0);
	
	return buffer.text;
}

int main()
{
	char* string;
	string = get_string();
	printf("String: %s\n", string);
	free(string);
}