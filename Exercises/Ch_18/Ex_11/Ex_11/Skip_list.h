/*
A skip list is a sorted singly-linked list composed of nodes with varying "levels." Nodes with a greater number
of levels can see past nodes with fewer levels to nodes with equal or greater levels. This makes for faster
searches but longer and more expensive manipulations (e.g., insertions, removals).
*/

#include <iostream>
#include <string>
#include <vector>

/*
Contains a string value as well as a vector of pointers to succeeding nodes whose length corresponds to this
nodes number of levels.
*/
class Skip_node {
public:
	Skip_node(const std::string& v, int num_levels) :
		value{ v }, succs{ std::vector<Skip_node*>(num_levels, nullptr) } {}

	std::string get_value() const { return value; }

	void set_value(const std::string& v) { value = v; }
	std::vector<Skip_node*>& get_succs() { return succs; }
private:
	std::string value;
	std::vector<Skip_node*> succs;
};

/*
Contains a singly-linked list of Skip_nodes with heights ranging from 1 to max_num_levels, assigned at a rate
of pow(interval, x), where x is an integer less than max_num_levels.
*/
class Skip_list {
public:
	Skip_list(int, int);
	~Skip_list();

	bool insert(const std::string&);
	bool remove(const std::string&);
	Skip_node* find(const std::string&);
	void print(std::ostream&);
private:
	const int max_num_levels;
	const int rate;

	int num_nodes = 0;
	Skip_node* head;
	Skip_node* tail;
};
