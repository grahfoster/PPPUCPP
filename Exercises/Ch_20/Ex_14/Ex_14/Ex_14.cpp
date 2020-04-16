#include <iostream>

template<class Elem>
class Slist {
public:
	struct Link;
	class Iterator;

	~Slist();

	Iterator begin() { return Iterator{ first }; }
	Iterator end() { return Iterator{ nullptr }; }
	Iterator insert(Iterator, const Elem&);
	Iterator erase(Iterator);
	void push_front(const Elem&);
	void push_back(const Elem&);
	void pop_front();
	void pop_back();
	Elem& front();
	Elem& back();
private:
	Link* first = nullptr;

	Link* last() const;
};

template<class Elem>
struct Slist<Elem>::Link {
	Link* succ = nullptr;
	Elem v = Elem{};
};

template<class Elem>
class Slist<Elem>::Iterator {
public:
	Link* curr;

	Iterator(Link* p) : curr{ p } {};

	bool operator==(const Iterator& b) const { return curr == b.curr; }
	bool operator!=(const Iterator& b) const { return !(curr == b.curr); }

	Iterator& operator++() { curr = curr->succ; return *this; }
	Elem& operator*() { return curr->v; }
};

template<class Elem>
Slist<Elem>::~Slist()
{
	auto p = first;
	while (p->succ) {
		auto temp = p;
		p = temp->succ;
		delete temp;
	}
	delete p;
}

template<class Elem>
typename Slist<Elem>::Iterator Slist<Elem>::insert(Iterator p, const Elem& v)
{
	Link* nl = new Link;
	nl->v = v;
	if (!first) {
		first = nl;
		return Iterator{ nl };
	}
	nl->succ = p.curr;
	Link* prev = first;
	while (prev->succ) {
		if (prev->succ == p.curr) {
			prev->succ = nl;
			break;
		}
		prev = prev->succ;
	}
	if (p == first)
		first = nl;
	return Iterator{ nl };
}

template<class Elem>
typename Slist<Elem>::Iterator Slist<Elem>::erase(Iterator p)
{
	if (!p.curr)
		throw std::exception("erase() called on empty List");
	Link* temp = p.curr->succ;
	Link* prev = first;
	while (prev->succ) {
		if (prev->succ == p.curr) {
			prev->succ = temp;
			break;
		}
		prev = prev->succ;
	}
	if (p.curr == first)
		first = nullptr;
	delete p.curr;
	return Slist<Elem>::Iterator{ temp };
}

template<class Elem>
void Slist<Elem>::push_front(const Elem& v)
{
	Link* nl = new Link;
	nl->v = v;
	if (!first) {
		first = nl;
		return;
	}
	insert(Iterator{ first }, v);
}

template<class Elem>
void Slist<Elem>::push_back(const Elem& v)
{
	Link* nl = new Link;
	nl->v = v;
	if (!first) {
		first = nl;
		return;
	}
	last()->succ = nl;
}

template<class Elem>
void Slist<Elem>::pop_front()
{
	if (first)
		erase(Slist<Elem>::Iterator{ first });
	else
		throw std::exception("pop_front() called on empty List");
}

template<class Elem>
void Slist<Elem>::pop_back()
{
	if (last())
		erase(Slist<Elem>::Iterator{ last() });
	else
		throw std::exception("pop_back() called on empty List");
}

template<class Elem>
Elem& Slist<Elem>::front()
{
	if (first)
		return first->v;
	else
		throw std::exception("front() called on empty List");
}

template<class Elem>
Elem& Slist<Elem>::back()
{
	if (last())
		return last()->v;
	else
		throw std::exception("back() called on empty List");
}

template<class Elem>
typename Slist<Elem>::Link* Slist<Elem>::last() const
{
	auto p = first;
	while (p->succ)
		p = p->succ;
	return p;
}

template<class Iter>
Iter high(Iter b, Iter e)
{
	Iter high = b;
	while (b != e) {
		if (*high < *b)
			high = b;
		++b;
	}
	return high;
}

int main()
try {
	Slist<int> sli;
	for (int i = 0; std::cin >> i;)
		sli.push_back(i);
	if (!std::cin && !std::cin.eof())
		throw std::exception("bad input format");

	std::cout << "List contents: ";
	for (int i : sli)
		std::cout << i << ' ';
	std::cout << '\n';

	auto p = high(sli.begin(), sli.end());
	std::cout << "The highest value was: " << *p << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}