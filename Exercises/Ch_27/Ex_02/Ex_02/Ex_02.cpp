#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Link {
	struct Link* pre;
	struct Link* suc;
};

struct List {
	struct Link* first;
	struct Link* last;
};

struct Name {
	struct Link lnk;
	const char* p;
};

void init(struct List* lst)
{
	assert(lst);
	lst->first = lst->last = 0;
}

struct List* create()
{
	struct List* lst = (struct List*)malloc(sizeof(struct List));
	init(lst);
	return lst;
}

void clear(struct List* lst)
{
	assert(lst);
	{
		struct Link* curr = lst->first;
		while (curr) {
			struct Link* next = curr->suc;
			free(curr);
			curr = next;
		}
		lst->first = lst->last = 0;
	}
}

void destroy(struct List* lst)
{
	assert(lst);
	clear(lst);
	free(lst);
}

void push_back(struct List* lst, struct Link* p)
{
	assert(lst);
	{
		struct Link* last = lst->last;
		if (last) {
			last->suc = p;
			p->pre = last;
		}
		else {
			lst->first = p;
			p->pre = 0;
		}
		lst->last = p;
		p->suc = 0;
	}
}

void push_front(struct List* lst, struct Link* p)
{
	assert(lst);
	{
		struct Link* first = lst->first;
		if (first) {
			first->pre = p;
			p->suc = first;
		}
		else {
			lst->last = p;
			p->suc = 0;
		}
		lst->first = p;
		p->pre = 0;
	}
}

void insert(struct List* lst, struct Link* p, struct Link* q)
{
	assert(lst);
	{
		if (q->pre) {
			p->suc = q;
			p->pre = q->pre;
			q->pre = p;
			p->pre->suc = p;
		}
		else {
			p->suc = q;
			p->pre = 0;
			q->pre = p;
			lst->first = p;
		}
	}
}

struct Link* erase(struct List* lst, struct Link* p)
{
	assert(lst);
	if (p == lst->first) {
		if (p->suc) {
			lst->first = p->suc;
			p->suc->pre = 0;
			return p->suc;
		}
		else {
			lst->first = lst->last = 0;
			return 0;
		}
	}
	else if (p == lst->last) {
		if (p->pre) {
			lst->last = p->pre;
			p->pre->suc = 0;
		}
		else {
			lst->first = lst->last = 0;
			return 0;
		}
	}
	else {
		p->suc->pre = p->pre;
		p->pre->suc = p->suc;
		return p->suc;
	}
}

struct Link* advance(struct Link* p, int n)
{
	if (n > 0) {
		while (n > 0) {
			if (p->suc)
				p = p->suc;
			else
				return 0;
			--n;
		}
	}
	else {
		while (n < 0) {
			if (p->pre)
				p = p->pre;
			else
				return 0;
			++n;
		}
	}
	return p;
}

struct Name* make_name(const char* n)
{
	struct Name* p = (struct Name*)malloc(sizeof(struct Name));
	p->p = n;
	return p;
}

int main() {
	struct List* names = create();
	struct Link* curr;
	int count = 0;

	init(names);
	push_back(names, (struct Link*)make_name("Norah"));
	push_back(names, (struct Link*)make_name("Annemarie"));
	push_back(names, (struct Link*)make_name("Kris"));
	push_front(names, (struct Link*)make_name("Tiffany"));
	insert(names, (struct Link*)make_name("Claire"), advance(names->first, 2));
	erase(names, advance(names->first, 1));

	for (curr = names->first; curr; curr = curr->suc) {
		++count;
		printf("Element %d: %s\n", count, ((struct Name*)curr)->p);
	}

	destroy(names);
}