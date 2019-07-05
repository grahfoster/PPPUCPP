#include <iostream>

struct God {
	std::string name;
	std::string mythology;
	std::string vehicle;
	std::string weapon;

	God(std::string n, std::string m = "", std::string v = "", std::string w = "") :
		name{ n }, mythology{ m }, vehicle{ v }, weapon{ w } {}
};

bool operator==(const God& god1, const God& god2) { return god1.name == god2.name; }
bool operator<(const God& god1, const God& god2) { return god1.name < god2.name; }

std::ostream& operator<<(std::ostream& os, const God& god)
{
	os << "Name: " << god.name <<
		", Mythology: " << god.mythology <<
		", Vehicle: " << god.vehicle <<
		", Weapon: " << god.weapon << '\n';
	return os;
}

template<class T>
class Link {
public:
	T val;

	Link(const T& v, Link* p = nullptr, Link* s = nullptr) : val{ v }, prev{ p }, succ{ s } {}

	Link* next() const { return succ; }
	Link* previous() const { return prev; }
	Link* advance(int) const;
	const Link* find(const T&) const;
	const Link* find_first() const;

	Link* insert(Link*);
	Link* add(Link*);
	Link* add_ordered(Link*);
	Link* erase();
	Link* find(const T&);
	Link* find_first();
private:
	Link* prev;
	Link* succ;
};

template<class T>
Link<T>* Link<T>::advance(int n) const
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

template<class T>
const Link<T>* Link<T>::find(const T& t) const
{
	if (!this)
		return this;
	const Link* lp = find_first();
	while (lp) {
		if (lp->val == t)
			return lp;
		lp = lp->succ;
	}
	return nullptr;
}

template<class T>
const Link<T>* Link<T>::find_first() const
{
	const Link* lp = this;
	while (lp->previous())
		lp = lp->previous();
	return lp;
}

template<class T>
Link<T>* Link<T>::insert(Link<T>* lp)
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

template<class T>
Link<T>* Link<T>::add(Link<T>* lp)
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

template<class T>
Link<T>* Link<T>::add_ordered(Link<T>* lp)
{
	Link* temp = this;
	if (!lp)
		return this;
	if (!temp)
		return temp;
	while (temp->prev)
		temp = temp->prev;
	while (temp->val < lp->val) {
		if (!temp->succ)
			return temp->add(lp);
		temp = temp->succ;
	}
	return temp->insert(lp);
}

template<class T>
Link<T>* Link<T>::erase()
{
	if (!this)
		return this;
	if (succ) {
		val = succ->val;
		succ = succ->next();
	}
	return this;
}

template<class T>
Link<T>* Link<T>::find(const T& t)
{
	if (!this)
		return this;
	Link* lp = find_first();
	while (lp) {
		if (lp->val == t)
			return lp;
		lp = lp->succ;
	}
	return nullptr;
}

template<class T>
Link<T>* Link<T>::find_first()
{
	Link* lp = this;
	while (lp->previous())
		lp = lp->previous();
	return lp;
}

template<class T>
void print_all(Link<T>* lp)
{
	if (!lp)
		return;
	lp = lp->find_first();
	while (lp) {
		std::cout << lp->val;
		lp = lp->next();
	}
}

template<class T>
void delete_list(Link<T>* lp)
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
	Link<God>* all_gods = new Link<God>{ { "Thor", "Norse", "Thor's Horse", "Mjolnir" } };
	all_gods = all_gods->insert(new Link<God>{ { "Odin", "Norse", "Sleipnir", "Gungnir" } });
	all_gods = all_gods->insert(new Link<God>{ { "Freia", "Norse", "Freia's Chariot", "N/A" } });
	all_gods = all_gods->insert(new Link<God>{ { "Heimdallr", "Norse", "Gulltoppr", "N/A" } });
	all_gods = all_gods->insert(new Link<God>{ { "Hera", "Greek", "Hera's Chariot", "N/A" } });
	all_gods = all_gods->insert(new Link<God>{ { "Athena", "Greek", "Athena's Chariot", "Various" } });
	all_gods = all_gods->insert(new Link<God>{ { "Poseidon", "Greek", "Poseidon's Chariot", "Trident" } });
	all_gods = all_gods->insert(new Link<God>{ { "Zeus", "Greek", "Zeus's Chariot", "Thunderbolt" } });
	all_gods = all_gods->insert(new Link<God>{ { "Ra", "Egyptian", "N/A", "N/A" } });
	all_gods = all_gods->insert(new Link<God>{ { "Isis", "Egyptian", "N/A", "N/A" } });
	all_gods = all_gods->insert(new Link<God>{ { "Set", "Egyptian", "N/A", "N/A" } });
	all_gods = all_gods->insert(new Link<God>{ { "Horus", "Egyptian", "N/A", "N/A" } });

	Link<God>* norse_gods = new Link<God>{ { (*all_gods->find({ "Thor" })).val } };
	norse_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Odin" })).val } });
	norse_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Freia" })).val } });
	norse_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Heimdallr" })).val } });

	Link<God>* greek_gods = new Link<God>{ { (*all_gods->find({ "Hera" })).val } };
	greek_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Athena" })).val } });
	greek_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Poseidon" })).val } });
	greek_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Zeus" })).val } });

	Link<God>* egyptian_gods = new Link<God>{ { (*all_gods->find({ "Ra" })).val } };
	egyptian_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Isis" })).val } });
	egyptian_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Set" })).val } });
	egyptian_gods->add_ordered(new Link<God>{ { (*all_gods->find({ "Horus" })).val } });

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