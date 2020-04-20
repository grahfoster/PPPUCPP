#include <iostream>

struct range_exception : std::exception { using std::exception::exception; };

template<class Elem>
class List {
public:
	struct Link;
	class Iterator;

	~List();

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
struct List<Elem>::Link {
	Link* prev = nullptr;
	Link* succ = nullptr;
	Elem v = Elem{};
};

template<class Elem>
class List<Elem>::Iterator {
public:
	Link* curr;

	Iterator(Link* p) : curr{ p } {};

	bool operator==(const Iterator& b) const { return curr == b.curr; }
	bool operator!=(const Iterator& b) const { return !(curr == b.curr); }

	Iterator& operator++() { curr = curr->succ; return *this; }
	Iterator& operator--() { curr = curr->prev; return *this; }
	Elem& operator*();
};

template<class Elem>
Elem& List<Elem>::Iterator::operator*()
{
	if (!curr)
		throw range_exception("out of range access");
	return curr->v;
}

template<class Elem>
List<Elem>::~List()
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
typename List<Elem>::Iterator List<Elem>::insert(Iterator p, const Elem& v)
{
	Link* nl = new Link;
	nl->v = v;
	if (!first) {
		first = nl;
		return Iterator{ nl };
	}
	nl->succ = p.curr;
	if (p.curr->prev) {
		nl->prev = p.curr->prev;
		p.curr->prev->succ = nl;
	}
	else
		first = nl;
	p.curr->prev = nl;
	return Iterator{ nl };
}

template<class Elem>
typename List<Elem>::Iterator List<Elem>::erase(Iterator p)
{
	if (!p.curr)
		throw std::exception("erase() called on empty List");
	Link* temp = p.curr->succ;
	if (p.curr->prev) {
		temp->prev = p.curr->prev;
		p.curr->prev->succ = temp;
	}
	else
		first = temp;
	delete p.curr;
	return List<Elem>::Iterator{ temp };
}

template<class Elem>
void List<Elem>::push_front(const Elem& v)
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
void List<Elem>::push_back(const Elem& v)
{
	Link* nl = new Link;
	nl->v = v;
	if (!first) {
		first = nl;
		return;
	}
	nl->prev = last();
	last()->succ = nl;
}

template<class Elem>
void List<Elem>::pop_front()
{
	if (first)
		erase(List<Elem>::Iterator{ first });
	else
		throw std::exception("pop_front() called on empty List");
}

template<class Elem>
void List<Elem>::pop_back()
{
	if (last())
		erase(List<Elem>::Iterator{ last() });
	else
		throw std::exception("pop_back() called on empty List");
}

template<class Elem>
Elem& List<Elem>::front()
{
	if (first)
		return first->v;
	else
		throw std::exception("front() called on empty List");
}

template<class Elem>
Elem& List<Elem>::back()
{
	if (last())
		return last()->v;
	else
		throw std::exception("back() called on empty List");
}

template<class Elem>
typename List<Elem>::Link* List<Elem>::last() const
{
	auto p = first;
	while (p->succ)
		p = p->succ;
	return p;
}

int main()
try {
	List<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);
	li.push_back(5);

	std::cout << *li.end() << '\n';
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}