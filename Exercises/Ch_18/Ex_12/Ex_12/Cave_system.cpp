#include "Cave_system.h"

/*
Check if the cave has been connected to the maximum number of adjoining caves.
*/
bool Cave::is_full() const
{
	for (Cave* adj : adjs)
		if (!adj)
			return false;
	return true;
}

/*
Check if the cave has been connected to another given cave.
*/
bool Cave::is_connected(Cave* cave) const
{
	for (Cave* adj : adjs)
		if (adj == cave)
			return true;
	return false;
}

/*
Check if the given cave is surrounded by pits or bats, rendering the placed player or Wumpus immobile.
*/
bool Cave::is_mobile() const {
	for (Cave* adj : adjs)
		if (!adj->get_has_pit() && !adj->get_has_bat())
			return true;
	return false;
}

Cave_system::Cave_system()
{
	// create and connect caves (connecting caves is not guaranteed to work: in case of failure, clear and
	// reconstruct caves and try to connect again)
	while (true) {
		for (int i = 0; i < num_caves; ++i)
			caves.push_back(new Cave{ i });
		std::vector<Cave*> unplaced_caves{ caves };
		try {
			for (Cave* cave : caves)
				if (!cave->is_full())
					connect_cave(unplaced_caves, cave);
			break;
		}
		catch (Cave_exception) {
			clear_caves();
		}
	}

	// place pits in random caves
	for (int i = 0; i < num_pits; ++i) {
		Cave* pit_cave = get_rand_cave(caves);
		while (pit_cave->get_has_pit())
			pit_cave = get_rand_cave(caves);
		pit_cave->set_has_pit(true);
	}

	// place bats in random caves
	for (int i = 0; i < num_bats; ++i) {
		Cave* bat_cave = get_rand_cave(caves);
		while (bat_cave->get_has_pit() || bat_cave->get_has_bat())
			bat_cave = get_rand_cave(caves);
		bat_cave->set_has_bat(true);
	}

	// place Wumpus in random cave
	do {
		wumpus_cave = get_rand_cave(caves);
	} while (wumpus_cave->get_has_pit() || wumpus_cave->get_has_bat() || !wumpus_cave->is_mobile());

	// place player in random cave
	do {
		player_cave = get_rand_cave(caves);
	} while (player_cave == wumpus_cave || player_cave->get_has_pit() || player_cave->get_has_bat() ||
		!player_cave->is_mobile());
}

/*
Move the Wumpus to a random adjoining cave. Called when the player shoots an arrow and fails to hit the Wumpus.
*/
void Cave_system::move_wumpus()
{
	do {
		wumpus_cave = get_rand_cave(wumpus_cave->get_adjs());
	} while (wumpus_cave->get_has_pit() || wumpus_cave->get_has_bat());
}

/*
Move the player to a random cave (if rand is true) or to a chosen adjoining cave (if rand is false). Called
when the player encounters a bat or chooses to move on their turn, with respective values.
*/
void Cave_system::move_player(Cave* cave, bool rand)
{
	if (rand)
		do {
			player_cave = get_rand_cave(caves);
		} while (player_cave == cave || player_cave == wumpus_cave || player_cave->get_has_pit() ||
			player_cave->get_has_bat() || !player_cave->is_mobile());
	else
		player_cave = cave;
}

/*
Delete caves and clear the vector containing them in preparation for reconstruction.
*/
void Cave_system::clear_caves()
{
	for (Cave* cave : caves)
		delete cave;
	caves.clear();
}

/*
Remove a cave from the vector of unplaced caves, narrowing the selection pool for random caves.
*/
void Cave_system::remove_cave(std::vector<Cave*>& unplaced_caves, int num)
{
	for (int i = 0; i < unplaced_caves.size(); ++i)
		if (num == unplaced_caves[i]->get_num())
			unplaced_caves.erase(unplaced_caves.begin() + i);
}

/*
Connect a given cave to up to three applicable caves. Due to randomness, a cave may be impossible to connect.
In this case, an exception is thrown to begin connecting each cave again.
*/
void Cave_system::connect_cave(std::vector<Cave*>& unplaced_caves, Cave* cave)
{
	remove_cave(unplaced_caves, cave->get_num());	// remove cave from pool; it can't connect to itself
	for (int i = 0; i < Cave::num_adjs; ++i) {
		while (!cave->get_adjs()[i]) {	// check if adjoining cave is unassigned
			// connection fails if only one cave remains that can't connect to itself or if two caves remain
			// that are already connected and can't be connected again
			if (unplaced_caves.empty() || (unplaced_caves.size() <= 2 &&
				unplaced_caves.front()->is_connected(cave) && unplaced_caves.back()->is_connected(cave)))
				throw Cave_exception();

			Cave* rand_cave = get_rand_cave(unplaced_caves);
			// if random cave is full, remove it from selection pool
			if (rand_cave->is_full()) {
				remove_cave(unplaced_caves, rand_cave->get_num());
				continue;
			}

			for (int j = 0; j < Cave::num_adjs; ++j) {	// iterate over random cave's adjoining cave pointers
				// if random cave has open slot and isn't connected to cave in another slot, connect both caves
				if (!rand_cave->get_adjs()[j] && !rand_cave->is_connected(cave)) {
					rand_cave->get_adjs()[j] = cave;
					cave->get_adjs()[i] = rand_cave;
					break;
				}
			}
		}
	}
}