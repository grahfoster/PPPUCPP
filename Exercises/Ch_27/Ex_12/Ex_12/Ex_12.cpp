#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <cstring>

// Member is a pair of data points contained in a Table
struct Member {
	const char* name;
	int num;
};

// Table is simply an array of unique Member pointers that keeps track of its size and space
struct Table {
	struct Member** members;
	int size;
	int space;
};

// safe safe_malloc wrapper that catches allocation errors
void* safe_malloc(size_t n)
{
	void* p = malloc(n);
	if (!p) {
		fprintf(stderr, "Error: failed to allocate %zu bytes.\n", n);
		exit(1);
	}
	return p;
}

// allocate and initialize a new Table
struct Table* construct_table() {
	struct Table* table = (struct Table*)safe_malloc(sizeof(struct Table));
	table->size = 0;
	table->space = 1;

	return table;
}

// deallocate a Table and its contents
void destroy_table(struct Table* table)
{
	assert(table);
	{
		int i;
		for (i = 0; i < table->size; ++i)
			free(table->members[i]);
		free(table);
	}
}

// expand the space of the array of Members in a Table
void expand(struct Table* table) {
	assert(table);
	table->space *= 2;
	{
		struct Member** temp = (struct Member**)safe_malloc(sizeof(struct Member*) * table->space);
		memcpy(temp, table->members, sizeof(struct Member*) * table->size);
		free(table->members);
		table->members = temp;
	}
}

// find a Member in a table and return a pointer to that Member if it exists; otherwise,
// return the null pointer
struct Member* find(struct Table* table, const char* name) {
	assert(table);
	{
		int i;
		for (i = 0; i < table->size; ++i)
			if (name == table->members[i]->name)
				return table->members[i];
		return NULL;
	}
}

// allocate, initialize, and place a Member at the front of a Table and return a pointer to
// that Member. If the Member arguments are non-unique, return the null pointer
struct Member* insert(struct Table* table, const char* name, int num) {
	assert(table);
	{
		if (find(table, name))
			return NULL;
		if (table->size == table->space)
			expand(table);

		struct Member* member = (struct Member*)safe_malloc(sizeof(struct Member));
		member->name = name;
		member->num = num;

		if (table->size) {
			struct Member** temp = (struct Member**)safe_malloc(sizeof(struct Member*) * table->space);
			temp[0] = member;
			memcpy(&temp[1], table->members, sizeof(struct Member*) * table->size);
			free(table->members);
			table->members = temp;
		}
		else {
			table->members = (struct Member**)safe_malloc(sizeof(struct Member*));
			table->members[0] = member;
		}
		++table->size;
	}
	return 0;
}

// find and erase a Member from a Table and return a pointer to the next Member. If there are
// no other Members or the sought for Member is invalid, return the null pointer
struct Member* remove(struct Table* table, const char* name) {
	assert(table);
	{
		struct Member* member = find(table, name);
		if (member) {
			struct Member** temp = (struct Member**)safe_malloc(sizeof(struct Member*) * table->space);
			int i;
			int j = 0;
			for (i = 0; i < table->size; ++i) {
				if (table->members[i] != member) {
					temp[j] = table->members[i];
					++j;
				}
			}
			free(member);
			free(table->members);
			table->members = temp;
			--table->size;
		}
		else
			return NULL;
	}
}

int main()
{
	struct Table* table = construct_table();
	int i;

	insert(table, "element_a", 1);
	insert(table, "element_b", 2);
	insert(table, "element_a", 3);
	insert(table, "element_c", 4);
	remove(table, "element_b");

	for (i = 0; i < table->size; ++i)
		printf("Member %d: %s, %d\n", i + 1, table->members[i]->name, table->members[i]->num);

	destroy_table(table);
}