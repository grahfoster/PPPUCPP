#include "Cave_system.h"
#include "Turn.h"
#include <chrono>

/*
Introduce the game to the player.
*/
void print_welcome(std::ostream& os) {
	os << "Welcome to Hunt the Wumpus, a text-based spelunking game. You have fallen into a vast cave system\n"
		"full of treacherous pits, swooping man-sized bats, and a viscious, bloodthirsty behemoth known as\n"
		"the Wumpus. With your trusty bow in hand, you must make your way from cave to cave and eliminate the\n"
		"beast before it makes you its prey. Type 'r' for an explanation of the game's rules.\n";
}

/*
Explain the game's rules to the player.
*/
void print_rules(std::ostream& os) {
	os << "\nEach cave in the system is connected to three adjoining caves. These are displayed to you at the\n"
		"beginning of each turn. If one or more pits are in the adjoining caves, you will be notified of an\n"
		"ominous breeze. Likewise, if one or more bats are in the adjoining caves, you will hear a nearby\n"
		"wooshing sound. When the Wumpus is in one of the adjoining rooms, your keen sense of smell will tell\n"
		"you so. Should you enter a room with a pit, you will fall in, ending the game. Entering a room with\n"
		"a bat will cause the winged creature to pick you up and drag you to a different, random cave.\n"
		"The only way to beat the game is to slay the Wumpus with your bow. In order to do this, you must\n"
		"move from room to room searching for the beast while avoiding the dangers scattered throughout the\n"
		"cave system. To move to an adjoining room, type 'm' followed by the cave you wish to move to (e.g.,\n"
		"\"m13\" will move you to cave 13, assuming it is adjacent to the cave you are currently in). Be sure\n"
		"to draw a map as you move through the cave system. This will help you avoid pits and bats, as well\n"
		"as increase your odds of striking the Wumpus with an arrow.\n"
		"Once you have a good idea of where the Wumpus is, take aim with your bow and loose a shaft through\n"
		"up to three adjoined caves. To do so, type 's' followed by the caves you wish to shoot into,\n"
		"separated by '-' (e.g., \"s12-2-8\" will shoot an arrow through caves 12, 2, and 8, assuming each\n"
		"adjoins the next). If you want to shoot through three caves but cannot figure out a flight path,\n"
		"type \"s0\" to loose a shaft into three random ajoined caves. Beware: if you fire an arrow but\n"
		"do not hit the Wumpus, the beast will stir and move to an adjoining cave, which may just be your\n"
		"own! Finally, if you run out of arrows, the game is over.\n";
}

/*
Inform the player of their current position and nearby dangers and prompt for turn input.
*/
void print_turn(std::ostream& os, Cave_system& cs)
{
	os << "You are currently in cave " << cs.get_player_cave()->get_num() << ". It connects to caves ";
	for (Cave* adj : cs.get_player_cave()->get_adjs()) {
		if (adj == cs.get_player_cave()->get_adjs().back())
			os << "and ";
		os << adj->get_num();
		if (adj == cs.get_player_cave()->get_adjs().back())
			os << ".\n";
		else
			os << ", ";
	}

	bool felt_pit = false;
	bool heard_bat = false;
	for (Cave* adj : cs.get_player_cave()->get_adjs()) {
		if (adj == cs.get_wumpus_cave())
			os << "A musky odor tingles your nose.\n";
		if (adj->get_has_pit() && !felt_pit) {
			os << "An ominous breeze blows over you.\n";
			felt_pit = true;
		}
		if (adj->get_has_bat() && !heard_bat) {
			os << "A wooshing noise fills your ears.\n";
			heard_bat = true;
		}
	}

	os << "Would you like to move or shoot? (" << cs.get_num_arrows() << " arrow" <<
		(cs.get_num_arrows() == 1 ? "" : "s") << " remaining)\n";
}

/*
Move the player to the specified cave, if valid.
*/
void move(std::istream& is, Cave_system& cs, Turn& turn)
{
	const char* const no_move_msg{ "You can't move to that cave.\n" };

	if (0 >= turn.dests.front() || turn.dests.front() > Cave_system::num_caves) {	// check for valid number
		is.ignore(is.rdbuf()->in_avail());
		throw Turn_exception(no_move_msg);
	}

	for (Cave* adj : cs.get_player_cave()->get_adjs()) {
		if (adj->get_num() == turn.dests.front()) {	// check if number matches any adjoining cave
			cs.move_player(adj, false);
			return;
		}
	}

	// number didn't match any adjoining cave
	is.ignore(is.rdbuf()->in_avail());
	throw Turn_exception(no_move_msg);
}

/*
Shoot an arrow through the specified caves, if valid. Return true if the player hits the Wumpus and wins the
game; otherwise, return false.
*/
bool shoot(std::istream& is, std::ostream& os, Cave_system& cs, Turn& turn)
{
	const char* const no_shoot_msg{ "You can't shoot into that cave.\n" };

	// if user entered "0" for first cave number, randomly select three valid caves
	if (turn.dests.front() == 0) {
		turn.dests.clear();
		Cave* cave = get_rand_cave(cs.get_player_cave()->get_adjs());
		turn.dests.push_back(cave->get_num());
		for (int i = 1; i < Turn::num_dests; ++i) {
			cave = get_rand_cave(cave->get_adjs());
			turn.dests.push_back(cave->get_num());
		}
	}

	// validate sequence of caves
	Cave* cave = cs.get_player_cave();
	for (int dest : turn.dests) {
		if (0 >= turn.dests.front() || turn.dests.front() > Cave_system::num_caves) { // check for valid numbers
			is.ignore(is.rdbuf()->in_avail());
			throw Turn_exception(no_shoot_msg);
		}
		for (Cave* adj : cave->get_adjs()) {
			if (adj->get_num() == dest) {	// check if number matches any adjoining cave
				cave = adj;
				break;
			}
			// number didn't match any adjoining cave
			if (adj == cave->get_adjs().back()) {
				is.ignore(is.rdbuf()->in_avail());
				throw Turn_exception(no_shoot_msg);
			}
		}
	}

	for (int dest : turn.dests)
		if (dest == cs.get_wumpus_cave()->get_num())	// check if arrow hit Wumpus
			return true;

	os << "You didn't hit the Wumpus. Startled, it moved to an adjoining room.\n";
	cs.decr_arrows();
	cs.move_wumpus();
	return false;
}

/*
Read input of instructions for the player's turn. Return true if the player has hit the Wumpus and won;
otherwise, return false.
*/
bool do_action(std::istream& is, std::ostream& os, Cave_system& cs)
{
	Turn turn;
	while (true) {
		try {
			is >> turn;
			switch (turn.action) {
			case Turn::Action::rules:
				print_rules(os);
				return false;
			case Turn::Action::move:
				move(is, cs, turn);
				return false;
			case Turn::Action::shoot:
				return shoot(is, os, cs, turn);
			}
		}
		catch (Turn_exception& te) {
			os << te.what();
			turn = Turn();
		}
	}
}

/*
Notify the player if they have won or lost the game. Return true if the player has won or lost; otherwise,
return false.
*/
bool play_turn(std::istream& is, std::ostream& os, Cave_system& cs)
{
	os << '\n';
	if (cs.get_num_arrows() == 0) {
		os << "You're out of arrows! You lose.\n";
		return false;
	}
	if (cs.get_player_cave() == cs.get_wumpus_cave()) {
		os << "The Wumpus is in this cave! You lose.\n";
		return false;
	}
	if (cs.get_player_cave()->get_has_pit()) {
		os << "There is a pit in this cave! You lose.\n";
		return false;
	}
	if (cs.get_player_cave()->get_has_bat()) {
		os << "There is a giant bat in this cave! It moves you to another cave.\n";
		cs.move_player(cs.get_player_cave(), true);
		return true;
	}

	print_turn(os, cs);

	if (do_action(is, os, cs)) {
		os << "You slew the wumpus! You win!\n";
		return false;
	}

	return true;
}

/*
Create and introduce the game, then generate turns until the player has won or lost. 
*/
void play_game(std::istream& is, std::ostream& os)
{
	srand(time(NULL));
	Cave_system cs;
	print_welcome(os);
	while (play_turn(is, os, cs));
}

int main()
try {
	play_game(std::cin, std::cout);
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	std::cerr << "Unexpected error.\n";
}