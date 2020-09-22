#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f(char* p, int x)
{
	printf("p is \"%s\" and x is %d.\n", p, x);
}

int main() {
	printf("Hello, World!\n");

	char word1[] = "Hello,";
	char word2[] = "World!";

	char* sentence = (char*)malloc(strlen(word1) + strlen(word2) + 2);
	strcpy(sentence, word1);
	strcat(sentence, " ");
	strcat(sentence, word2);
	printf("%s\n", sentence);

	f(word1, strlen(word1));
	f(word2, strlen(word2));
	f(sentence, strlen(sentence));

	free(sentence);
}