#include "Turn.h"
#include "My_window.h"

using namespace Graph_lib;

// create cave system and window in which game takes place
Cave_system* csp;
My_window* mwp;

/*
Introduce the game to the player.
*/
void print_welcome() {
	My_window& mw = *mwp;

	mw.print("Welcome to Hunt the Wumpus, a text-based spelunking game. You have fallen into a vast cave system\n"
		"full of treacherous pits, swooping man-sized bats, and a viscious, bloodthirsty behemoth known as\n"
		"the Wumpus. With your trusty bow in hand, you must make your way from cave to cave and eliminate the\n"
		"beast before it makes you its prey. Type 'r' for an explanation of the game's rules.\n\n");
}

/*
Explain the game's rules to the player.
*/
void print_rules() {
	My_window& mw = *mwp;

	mw.print("Each cave in the system is connected to three adjoining caves. These are displayed to you at the\n"
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
		"own! Finally, if you run out of arrows, the game is over.\n\n");
}

/*
Inform the player of their current position and nearby dangers and prompt for turn input.
*/
void print_turn()
{
	Cave_system& cs = *csp;
	My_window& mw = *mwp;

	vector<Cave*> map_caves;
	map_caves.push_back(cs.get_player_cave());

	mw.print("You are currently in cave " + to_string(cs.get_player_cave()->get_num()) +
		". It connects to caves ");
	for (Cave* adj : cs.get_player_cave()->get_adjs()) {
		map_caves.push_back(adj);
		if (adj == cs.get_player_cave()->get_adjs().back())
			mw.print("and ");
		mw.print(to_string(adj->get_num()));
		if (adj == cs.get_player_cave()->get_adjs().back())
			mw.print(".\n");
		else
			mw.print(", ");
	}

	mw.set_cave_labels(map_caves);

	bool felt_pit = false;
	bool heard_bat = false;
	for (Cave* adj : cs.get_player_cave()->get_adjs()) {
		if (adj == cs.get_wumpus_cave())
			mw.print("A musky odor tingles your nose.\n");
		if (adj->get_has_pit() && !felt_pit) {
			mw.print("An ominous breeze blows over you.\n");
			felt_pit = true;
		}
		if (adj->get_has_bat() && !heard_bat) {
			mw.print("A wooshing noise fills your ears.\n");
			heard_bat = true;
		}
	}

	mw.print("Would you like to move or shoot? (" + to_string(cs.get_num_arrows()) + " arrow");
	mw.print((cs.get_num_arrows() == 1 ? "" : "s"));
	mw.print(" remaining)\n");
}

/*
Move the player to the specified cave, if valid.
*/
void move(Turn& turn)
{
	const char* const no_move_msg{ "You can't move to that cave.\n" };

	Cave_system& cs = *csp;

	if (0 >= turn.dests.front() || turn.dests.front() > Cave_system::num_caves)	// check for valid number
		throw Turn_exception(no_move_msg);

	for (Cave* adj : cs.get_player_cave()->get_adjs()) {
		if (adj->get_num() == turn.dests.front()) {	// check if number matches any adjoining cave
			cs.move_player(adj, false);
			return;
		}
	}

	// number didn't match any adjoining cave
	throw Turn_exception(no_move_msg);
}

/*
Shoot an arrow through the specified caves, if valid. Return true if the player hits the Wumpus and wins the
game; otherwise, return false.
*/
bool shoot(Turn& turn)
{
	const char* const no_shoot_msg{ "You can't shoot into that cave.\n" };

	Cave_system& cs = *csp;
	My_window& mw = *mwp;

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
		if (0 >= turn.dests.front() || turn.dests.front() > Cave_system::num_caves) // check for valid numbers
			throw Turn_exception(no_shoot_msg);
		for (Cave* adj : cave->get_adjs()) {
			if (adj->get_num() == dest) {	// check if number matches any adjoining cave
				cave = adj;
				break;
			}
			// number didn't match any adjoining cave
			if (adj == cave->get_adjs().back())
				throw Turn_exception(no_shoot_msg);
		}
	}

	mw.clear();

	for (int dest : turn.dests)
		if (dest == cs.get_wumpus_cave()->get_num())	// check if arrow hit Wumpus
			return true;

	mw.print("You didn't hit the Wumpus. Startled, it moved to an adjoining room.\n\n");
	cs.decr_arrows();
	cs.move_wumpus();
	return false;
}

void play_turn();

/*
Read input of instructions for the player's turn. Return true if the player has hit the Wumpus and won;
otherwise, return false.
*/
void do_action()
{
	My_window& mw = *mwp;

	Turn turn;
	try {
		istringstream iss{ mw.read() };
		iss >> turn;
		switch (turn.action) {
		case Turn::Action::rules:
			mw.clear();
			print_rules();
			break;
		case Turn::Action::move:
			move(turn);
			mw.clear();
			break;
		case Turn::Action::shoot:
			if (shoot(turn)) {
				mw.print("You slew the wumpus! You win!\n");
				mw.hide_enter_button();
				return;
			}
		}
	}
	catch (Turn_exception& te) {
		mw.print(te.what());
		return;
	}

	play_turn();
}

/*
Notify the player if they have won or lost the game. Return true if the player has won or lost; otherwise,
return false.
*/
void play_turn()
{
	Cave_system& cs = *csp;
	My_window& mw = *mwp;

	if (cs.get_num_arrows() == 0) {
		mw.print("You're out of arrows! You lose.\n");
		mw.hide_enter_button();
		return;
	}
	if (cs.get_player_cave() == cs.get_wumpus_cave()) {
		mw.print("The Wumpus is in this cave! You lose.\n");
		mw.hide_enter_button();
		return;
	}
	if (cs.get_player_cave()->get_has_pit()) {
		mw.print("There is a pit in this cave! You lose.\n");
		mw.hide_enter_button();
		return;
	}
	if (cs.get_player_cave()->get_has_bat()) {
		mw.print("There is a giant bat in this cave! It moves you to another cave.\n\n");
		cs.move_player(cs.get_player_cave(), true);
	}

	print_turn();
	return;
}

/*
Create and introduce the game, then generate turns until the player has won or lost.
*/
void play_game()
{
	print_welcome();
	play_turn();
	gui_main();
}

int main()
try {
	srand(time(NULL));
	csp = new Cave_system;
	mwp = new My_window{ { x_max() / 8, y_max() / 8 }, x_max() * 3 / 4, y_max() * 3 / 4, "My window" };
	play_game();
	delete mwp;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}