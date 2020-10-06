#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>

#define REINTERPRET_CAST(T, v) ((T)(v))

struct Link {
	int pre;
	int suc;
};

struct List {
	struct Link** links;
	int first;
	int last;
	int space;
};

struct Name {
	struct Link lnk;
	const char* p;
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

void init(struct List* lst)
{
	assert(lst);
	lst->links = NULL;
	lst->first = lst->last = 0;
	lst->space = 1;
}

struct List* create()
{
	struct List* lst = REINTERPRET_CAST(struct List*, safe_malloc(sizeof(struct List)));
	init(lst);
	return lst;
}

void clear(struct List* lst)
{
	assert(lst);
	{
		int i;
		for (i = 0; i < lst->last + 1; ++i)
			free(lst->links[i]);
		lst->links = NULL;
		lst->first = lst->last = 0;
	}
}

void destroy(struct List* lst)
{
	assert(lst);
	clear(lst);
	free(lst);
}

void expand(struct List* lst)
{
	assert(lst);
	lst->space *= 2;
	{
		struct Link** temp = REINTERPRET_CAST(struct Link**, safe_malloc(sizeof(struct Link*) * lst->space));
		memcpy(temp, lst->links, sizeof(struct Link*) * (lst->last + 1));
		free(lst->links);
		lst->links = temp;
	}
}

void push_back(struct List* lst, struct Link* p)
{
	assert(lst);
	assert(p);
	{
		if (lst->links && lst->last + 1 == lst->space)
			expand(lst);
		if (lst->links) {
			p->pre = lst->links[lst->last]->suc - 1;
			p->suc = lst->links[lst->last]->suc + 1;
			++lst->last;
			lst->links[lst->last] = p;
		}
		else {
			lst->links = REINTERPRET_CAST(struct Link**, safe_malloc(sizeof(struct Link*)));
			p->pre = -1;
			p->suc = 1;
			lst->links[lst->first] = p;
		}
	}
}

void insert(struct List* lst, struct Link* p, struct Link* q)
{
	assert(lst);
	assert(p);
	assert(q);

	if (lst->last + 1 == lst->space)
		expand(lst);
	p->pre = q->pre;
	p->suc = q->suc - 1;

	{
		int i;
		for (i = p->suc; i < lst->last + 1; ++i) {
			++lst->links[i]->pre;
			++lst->links[i]->suc;
		}
		for (i = lst->last + 1; i > q->pre; --i)
			lst->links[i] = lst->links[i - 1];
		++lst->last;
		lst->links[q->pre] = p;
	}
}

void push_front(struct List* lst, struct Link* p)
{
	if (lst->links)
		insert(lst, p, lst->links[lst->first]);
	else
		push_back(lst, p);
}

struct Link* erase(struct List* lst, struct Link* p)
{
	assert(lst);
	assert(p);
	{
		int temp = p->pre + 1;
		int i;
		for (i = p->suc; i < lst->last + 1; ++i) {
			--lst->links[i]->pre;
			--lst->links[i]->suc;
		}
		for (i = p->suc - 1; i < lst->last; ++i)
			lst->links[i] = lst->links[i + 1];
		--lst->last;
		free(p);
		return lst->links[temp];
	}
}

struct Name* make_name(const char* n)
{
	struct Name* p = REINTERPRET_CAST(struct Name*, safe_malloc(sizeof(struct Name)));
	p->p = n;
	return p;
}

int main() {
	struct List* names = create();
	int i;

	init(names);
	push_back(names, REINTERPRET_CAST(struct Link*, make_name("Norah")));
	push_back(names, REINTERPRET_CAST(struct Link*, make_name("Annemarie")));
	push_back(names, REINTERPRET_CAST(struct Link*, make_name("Kris")));
	push_front(names, REINTERPRET_CAST(struct Link*, make_name("Tiffany")));
	insert(names, REINTERPRET_CAST(struct Link*, make_name("Claire")), names->links[2]);
	erase(names, names->links[1]);

	for (i = 0; names->links && i < names->last + 1; ++i)
		printf("Element %d: %s\n", i + 1, (REINTERPRET_CAST(struct Name*, names->links[i]))->p);

	destroy(names);
}