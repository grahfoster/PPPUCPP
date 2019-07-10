#include <iostream>
#include <vector>

/*
Represents the instructions given through input during the player's turn.
*/
struct Turn {
	static const char rules_char = 'r';
	static const char move_char = 'm';
	static const char shoot_char = 's';
	static const int num_dests = 3;

	enum class Action { rules, move, shoot };

	Action action;
	std::vector<int> dests;	// numbers of caves to move or shoot through
};

/*
Exception thrown when player input is incorrectly formatted or against the rules.
*/
struct Turn_exception : std::exception { using std::exception::exception; };

std::istream& operator>>(std::istream&, Turn&);