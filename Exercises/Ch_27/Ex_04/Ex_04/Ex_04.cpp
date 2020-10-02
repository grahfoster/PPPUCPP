#include <iostream>

template <class T>
struct Link {
	Link(T t = T{}) : t{ t } {};
	Link* pre = 0;
	Link* suc = 0;
	T t;
};

template <class T>
class List {
public:
	List() {};
	~List();

	Link<T>* get_first() const { return first; }
	Link<T>* get_last() const { return last; }
	Link<T>* advance(Link<T>*, int) const;

	void push_back(Link<T>*);
	void push_front(Link<T>*);
	void insert(Link<T>*, Link<T>*);
	Link<T>* erase(Link<T>*);
private:
	Link<T>* first = 0;
	Link<T>* last = 0;
};

template <class T>
List<T>::~List()
{
	Link<T>* curr = first;
	while (curr) {
		Link<T>* next = curr->suc;
		delete curr;
		curr = next;
	}
}

template <class T>
Link<T>* List<T>::advance(Link<T>* p, int n) const
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

template <class T>
void List<T>::push_back(Link<T>* p)
{
	if (!p)
		throw std::exception{ "invalid Link pointer" };
	if (last) {
		last->suc = p;
		p->pre = last;
	}
	else {
		first = p;
	}
	last = p;
}

template <class T>
void List<T>::push_front(Link<T>* p)
{
	if (!p)
		throw std::exception{ "invalid Link pointer" };
	if (first) {
		first->pre = p;
		p->suc = first;
	}
	else {
		last = p;
	}
	first = p;
}

template <class T>
void List<T>::insert(Link<T>* p, Link<T>* q)
{
	if (!p || !q)
		throw std::exception{ "invalid Link pointer" };
	if (q->pre) {
		p->suc = q;
		p->pre = q->pre;
		q->pre = p;
		p->pre->suc = p;
	}
	else {
		p->suc = q;
		q->pre = p;
		first = p;
	}
}

template <class T>
Link<T>* List<T>::erase(Link<T>* p)
{
	if (!p)
		throw std::exception{ "invalid Link pointer" };
	if (p == first) {
		if (p->suc) {
			first = p->suc;
			p->suc->pre = 0;
			Link<T>* temp = p->suc;
			delete p;
			return temp;
		}
		else {
			first = last = 0;
			delete p;
			return 0;
		}
	}
	else if (p == last) {
		if (p->pre) {
			last = p->pre;
			p->pre->suc = 0;
			delete p;
			return 0;
		}
		else {
			first = last = 0;
			delete p;
			return 0;
		}
	}
	else {
		p->suc->pre = p->pre;
		p->pre->suc = p->suc;
		Link<T>* temp = p->suc;
		delete p;
		return temp;
	}
}

int main()
try {
	List<std::string> names;

	names.push_back(new Link<std::string>{ "Norah" });
	names.push_back(new Link<std::string>{ "Annemarie" });
	names.push_back(new Link<std::string>{ "Kris" });
	names.push_front(new Link<std::string>{ "Tiffany" });
	names.insert(new Link<std::string>{ "Claire" }, names.advance(names.get_first(), 2));
	names.erase(names.advance(names.get_first(), 1));

	int count = 0;
	for (Link<std::string>* curr = names.get_first(); curr; curr = curr->suc) {
		++count;
		std::cout << "Element " << count << ": " << curr->t << ".\n";
	}
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}