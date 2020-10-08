#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}

int main()
{
	char keys[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/? 	";
	int i;
	int max = strlen(keys);

	for (i = 0; i < max; ++i)
		printf("%c (%d)\n", keys[i], (int)keys[i]);
	printf("\n");

	qsort(keys, max, sizeof(char), compare);
	for (i = 0; i < max; ++i)
		printf("%c (%d)\n", keys[i], (int)keys[i]);
}