#include <iostream>

class Link {
public:
	std::string value;

	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr) : value{ v }, prev{ p }, succ{ s } {}

	Link* next() const { return succ; }
	Link* previous() const { return prev; }
	Link* advance(int) const;
	const Link* find(const std::string&) const;
	const Link* find_first() const;

	Link* insert(Link*);
	Link* add(Link*);
	Link* erase();
	Link* find(const std::string&);
	Link* find_first();
private:
	Link* prev;
	Link* succ;
};

Link* Link::advance(int n) const
{
	Link* lp = const_cast<Link*>(this);
	if (!lp) return lp;
	if (n > 0) {
		while (n--) {
			if (!succ)
				return succ;
			lp = succ;
		}
	}
	else if (n < 0) {
		while (n++) {
			if (!prev)
				return prev;
			lp = prev;
		}
	}
	return lp;
}

/* Find link in const linked list */
const Link* Link::find(const std::string& v) const
{
	if (!this)
		return this;
	const Link* lp = find_first();
	while (lp) {
		if (lp->value == v)
			return lp;
		lp = lp->succ;
	}
	return nullptr;
}

const Link* Link::find_first() const
{
	const Link* lp = this;
	while (lp->previous())
		lp = lp->previous();
	return lp;
}

Link* Link::insert(Link* lp)
{
	if (!lp)
		return this;
	if (!this)
		return lp;
	lp->succ = this;
	if (prev)
		prev->succ = lp;
	lp->prev = prev;
	prev = lp;
	return lp;
}

Link* Link::add(Link* lp)
{
	if (!lp)
		return this;
	if (!this)
		return lp;
	lp->prev = this;
	if (succ)
		succ->prev = lp;
	lp->succ = succ;
	succ = lp;
	return lp;
}

Link* Link::erase()
{
	if (!this)
		return this;
	if (succ) {
		value = succ->value;
		succ = succ->next();
	}
	return this;
}

Link* Link::find(const std::string& v)
{
	if (!this)
		return this;
	Link* lp = find_first();
	while (lp) {
		if (lp->value == v)
			return lp;
		lp = lp->succ;
	}
	return nullptr;
}

Link* Link::find_first()
{
	Link* lp = this;
	while (lp->previous())
		lp = lp->previous();
	return lp;
}

void print_all(Link* lp)
{
	if (!lp)
		return;
	lp = lp->find_first();
	std::cout << "{";
	while (lp) {
		std::cout << lp->value;
		if (lp = lp->next())
			std::cout << ", ";
	}
	std::cout << "}\n";
}

void delete_list(Link* lp)
{
	if (!lp)
		return;
	lp->find_first();
	while (lp->next()) {
		lp = lp->next();
		delete lp->previous();
	}
	delete lp;
}

int main()
try {
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	Link* greek_gods = new Link{ "Hera" };
	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	Link* lp1 = greek_gods->find("Mars");
	if (lp1)
		lp1->value = "Ares";

	Link* lp2 = norse_gods->find("Zeus");
	if (lp2) {
		greek_gods = greek_gods->insert(new Link{ *lp2 });
		lp2->erase();
	}

	print_all(norse_gods);
	print_all(greek_gods);

	delete_list(norse_gods);
	delete_list(greek_gods);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}