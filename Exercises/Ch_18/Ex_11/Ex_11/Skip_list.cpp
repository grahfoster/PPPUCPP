#include "Skip_list.h"

Skip_list::Skip_list(int mnl, int i) :
	max_num_levels{ mnl }, rate{ i }
{
	if (max_num_levels < 1)
		throw std::exception("max number of levels must be greater than 0");
	if (rate < 1)
		throw std::exception("interval must be greater than 0");

	// initialize head and tail with maximum number of levels and target head's successor pointers to tail
	head = new Skip_node{ "HEAD", max_num_levels };
	tail = new Skip_node{ "TAIL", max_num_levels };
	for (int i = 0; i < max_num_levels; ++i)
		head->get_succs()[i] = tail;
}

Skip_list::~Skip_list()
{
	// walk through list and delete each node
	Skip_node* temp = head;
	while (temp) {
		head = head->get_succs().front();
		delete temp;
		temp = head;
	}
}

/*
Insert a new node into the list.
*/
bool Skip_list::insert(const std::string& value)
{
	// create a vector to keep track of "pending" successor node pointers that have not yet connected to their
	// targets
	std::vector<Skip_node**> open_succs(max_num_levels, nullptr);
	
	// update pending successors while searching for insertion point
	Skip_node* temp = head;
	do {
		for (int i = 0; i < temp->get_succs().size(); ++i)
			open_succs[i] = &temp->get_succs()[i];
		temp = temp->get_succs().front();
	} while (temp != tail && temp->get_value() < value);

	if (temp != tail && temp->get_value() == value)
		return false;

	++num_nodes;	// new node is valid; increment total nodes in list

	// determine number of levels for new node
	int num_levels = 0;
	for (int i = 0; i < max_num_levels; ++i)
		if (!(num_nodes % int(pow(rate, i))))	// does num_nodes divide evenly into square of rate?
			++num_levels;

	// create new node and retarget applicable pending successor pointers
	Skip_node* insertable = new Skip_node{ value, num_levels };
	for (int i = 0; i < num_levels; ++i)
		* open_succs[i] = insertable;

	// target new node's pending successor pointers to correct nodes
	while (temp) {
		for (int i = 0; i < num_levels && i < temp->get_succs().size(); ++i)
			if (!insertable->get_succs()[i])
				insertable->get_succs()[i] = temp;
		temp = temp->get_succs().front();
	}

	return true;
}

/*
Remove a node from the list by value.
*/
bool Skip_list::remove(const std::string& value)
{
	// create vector to keep track of "pending" successor node pointers that have not yet connected to targets
	std::vector<Skip_node**> open_succs(max_num_levels, nullptr);

	// update pending successors while searching for removeable node
	Skip_node* temp = head;
	do {
		for (int i = 0; i < temp->get_succs().size(); ++i)
			open_succs[i] = &temp->get_succs()[i];
		temp = temp->get_succs().front();
	} while (temp != tail && temp->get_value() != value);

	if (temp == tail)
		return false;

	// found node to be removed; mark next node for removal
	Skip_node* removeable = temp->get_succs().front();

	// update tail node
	if (removeable == tail)
		tail = temp;

	// retarget applicable pending successor pointers to correct node
	for (Skip_node** open_succ : open_succs) {
		if (*open_succ == removeable)
			* open_succ = temp;
		if (*open_succ == temp)
			* open_succ = nullptr;
	}

	// copy next node into current node and delete next node
	temp->set_value(removeable->get_value());
	temp->get_succs() = removeable->get_succs();
	delete removeable;

	// retarget remaining pending successor pointers to correct nodes
	while (temp) {
		for (int i = 0; i < temp->get_succs().size(); ++i)
			if (!*open_succs[i])
				* open_succs[i] = temp;
		temp = temp->get_succs().front();
	}

	return true;
}

/*
Find a node within the list by value.
*/
Skip_node* Skip_list::find(const std::string& value)
{
	Skip_node* temp = head;
	while (temp != tail)
		// take fastest "route" through highest-level successor node pointers
		for (int i = temp->get_succs().size() - 1; i >= 0; --i) {
			if (temp->get_succs()[i] == tail) {
				if (i == 0)	// queried node doesn't exist
					return nullptr;
				continue;
			}
			if (temp->get_succs()[i]->get_value() == value)	// found queried node
				return temp->get_succs()[i];
			if (temp->get_succs()[i]->get_value() < value) {	// queried node must be farther along
				temp = temp->get_succs()[i];
				break;
			}
			if (i == 0)	// queried node doesn't exist
				return nullptr;
		}
}

/*
Print out the value of each node in the list.
*/
void Skip_list::print(std::ostream& os)
{
	Skip_node* temp = head;
	while (temp) {
		os << temp->get_value() << " ";
		temp = temp->get_succs().front();
	}
	os << '\n';
}