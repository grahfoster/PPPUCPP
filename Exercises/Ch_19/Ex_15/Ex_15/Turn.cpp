#include "Turn.h"

/*
Handles input of instructions for the player's turn. Proper format for printing rules: "r"; proper format for
move: "m#"; proper format for shooting: "s#-#-#".
*/
std::istream& operator>>(std::istream& is, Turn& turn)
{
	const char* const invalid_turn_msg{ "Invalid turn format. Type 'r' for rules.\n" };
	const char next = '-';

	char c;
	int i;

	// get first character for action
	is >> c;
	if (c == Turn::move_char)
		turn.action = Turn::Action::move;
	else if (c == Turn::shoot_char)
		turn.action = Turn::Action::shoot;
	else if (c == Turn::rules_char)
		turn.action = Turn::Action::rules;
	else {
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}

	// check next character
	is >> c;
	if (turn.action == Turn::Action::rules) {
		if (is.eof())
			return is;
		else {
			is.ignore(is.rdbuf()->in_avail());
			throw Turn_exception(invalid_turn_msg);
		}
	}
	else if (is.eof()) {
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}
	is.unget();

	// get number of first destination cave
	is >> i;
	if (is.fail()) {
		is.clear();
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}
	turn.dests.push_back(i);

	// check next character
	is >> c;
	if (is.eof())
		return is;
	if (turn.action == Turn::Action::move) {
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}
	if (c != next) {
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}

	// get number of second destination cave
	is >> i;
	if (is.fail()) {
		is.clear();
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}
	turn.dests.push_back(i);

	// check next character
	is >> c;
	if (is.eof())
		return is;
	if (c != next) {
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}

	// get number of third destination cave
	is >> i;
	if (is.fail()) {
		is.clear();
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(invalid_turn_msg);
	}
	turn.dests.push_back(i);

	// check next character
	is >> c;
	if (is.eof())
		return is;
	is.ignore(is.rdbuf()->in_avail());
	throw Turn_exception(invalid_turn_msg);
}