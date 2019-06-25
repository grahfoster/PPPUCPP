#include <iostream>

struct God {
	std::string name;
	std::string mythology;
	std::string vehicle;
	std::string weapon;
};

std::ostream& operator<<(std::ostream& os, const God& god)
{
	os << "Name: " << god.name <<
		", Mythology: " << god.mythology <<
		", Vehicle: " << god.vehicle <<
		", Weapon: " << god.weapon << '\n';
	return os;
}

class Link {
public:
	God god;

	Link(const God& g, Link* p = nullptr, Link* s = nullptr) : god{ g }, prev{ p }, succ{ s } {}

	Link* next() const { return succ; }
	Link* previous() const { return prev; }
	Link* advance(int) const;
	const Link* find(const std::string&) const;
	const Link* find_first() const;

	Link* insert(Link*);
	Link* add(Link*);
	Link* add_ordered(Link*);
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

const Link* Link::find(const std::string& n) const
{
	if (!this)
		return this;
	const Link* lp = find_first();
	while (lp) {
		if (lp->god.name == n)
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

Link* Link::add_ordered(Link* lp)
{
	Link* temp = this;
	if (!lp)
		return this;
	if (!temp)
		return temp;
	while (temp->prev)
		temp = temp->prev;
	while (temp->god.name < lp->god.name) {
		if (!temp->succ)
			return temp->add(lp);
		temp = temp->succ;
	}
	return temp->insert(lp);
}

Link* Link::erase()
{
	if (!this)
		return this;
	if (succ) {
		god = succ->god;
		succ = succ->next();
	}
	return this;
}

Link* Link::find(const std::string& n)
{
	if (!this)
		return this;
	Link* lp = find_first();
	while (lp) {
		if (lp->god.name == n)
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
	while (lp) {
		std::cout << lp->god;
		lp = lp->next();
	}
}

void delete_list(Link* lp)
{
	if (!lp)
		return;
	lp = lp->find_first();
	while (lp->next()) {
		lp = lp->next();
		delete lp->previous();
	}
	delete lp;
}

int main()
try {
	Link* all_gods = new Link{ God{ "Thor", "Norse", "Thor's Horse", "Mjolnir" } };
	all_gods = all_gods->insert(new Link{ God{ "Odin", "Norse", "Sleipnir", "Gungnir" } });
	all_gods = all_gods->insert(new Link{ God{ "Freia", "Norse", "Freia's Chariot", "N/A" } });
	all_gods = all_gods->insert(new Link{ God{ "Heimdallr", "Norse", "Gulltoppr", "N/A" } });
	all_gods = all_gods->insert(new Link{ God{ "Hera", "Greek", "Hera's Chariot", "N/A" } });
	all_gods = all_gods->insert(new Link{ God{ "Athena", "Greek", "Athena's Chariot", "Various" } });
	all_gods = all_gods->insert(new Link{ God{ "Poseidon", "Greek", "Poseidon's Chariot", "Trident" } });
	all_gods = all_gods->insert(new Link{ God{ "Zeus", "Greek", "Zeus's Chariot", "Thunderbolt" } });
	all_gods = all_gods->insert(new Link{ God{ "Ra", "Egyptian", "N/A", "N/A" } });
	all_gods = all_gods->insert(new Link{ God{ "Isis", "Egyptian", "N/A", "N/A" } });
	all_gods = all_gods->insert(new Link{ God{ "Set", "Egyptian", "N/A", "N/A" } });
	all_gods = all_gods->insert(new Link{ God{ "Horus", "Egyptian", "N/A", "N/A" } });

	Link* norse_gods = new Link{ God{ (*all_gods->find("Thor")).god } };
	norse_gods->add_ordered(new Link{ God{ (*all_gods->find("Odin")).god } });
	norse_gods->add_ordered(new Link{ God{ (*all_gods->find("Freia")).god } });
	norse_gods->add_ordered(new Link{ God{ (*all_gods->find("Heimdallr")).god } });

	Link* greek_gods = new Link{ God{ (*all_gods->find("Hera")).god } };
	greek_gods->add_ordered(new Link{ God{ (*all_gods->find("Athena")).god } });
	greek_gods->add_ordered(new Link{ God{ (*all_gods->find("Poseidon")).god } });
	greek_gods->add_ordered(new Link{ God{ (*all_gods->find("Zeus")).god } });

	Link* egyptian_gods = new Link{ God{ (*all_gods->find("Ra")).god } };
	egyptian_gods->add_ordered(new Link{ God{ (*all_gods->find("Isis")).god } });
	egyptian_gods->add_ordered(new Link{ God{ (*all_gods->find("Set")).god } });
	egyptian_gods->add_ordered(new Link{ God{ (*all_gods->find("Horus")).god } });

	std::cout << "Norse Gods:\n\n";
	print_all(norse_gods);
	std::cout << "\nGreek Gods:\n\n";
	print_all(greek_gods);
	std::cout << "\nEgyptian Gods:\n\n";
	print_all(egyptian_gods);

	delete_list(all_gods);
	delete_list(norse_gods);
	delete_list(greek_gods);
	delete_list(egyptian_gods);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}