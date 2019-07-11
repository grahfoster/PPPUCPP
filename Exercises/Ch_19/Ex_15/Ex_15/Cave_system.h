#include <vector>

/*
Represents a single cave in a system of caves traversed by the player. Each cave has a number and keeps track of
whether it contains a pit or bat.
*/
class Cave {
public:
	static const int num_adjs = 3;
	static const enum class Cave_state {
		unknown, clear, pit_warning, pit_danger, bat_warning, bat_danger
	};

	Cave(int n) : num{ n }, adjs{ std::vector<Cave*>(num_adjs, nullptr) } {}

	int get_num() const { return num + 1; }
	bool get_has_pit() const { return has_pit; }
	bool get_has_bat() const { return has_bat; }
	bool is_full() const;
	bool is_connected(Cave*) const;
	bool is_mobile() const;
	Cave_state get_cave_state() const { return cave_state; }

	void set_has_pit(bool hp) { has_pit = hp; }
	void set_has_bat(bool hb) { has_bat = hb; }
	std::vector<Cave*>& get_adjs() { return adjs; }
	void set_cave_state(Cave_state cs) { cave_state = cs; }
private:
	int num;
	bool has_wumpus = false;
	bool has_pit = false;
	bool has_bat = false;
	std::vector<Cave*> adjs;
	Cave_state cave_state = Cave_state::unknown;
};

/*
Exception thrown when a cave system fails to construct due to randomness.
*/
struct Cave_exception {};

/*
System of caves that the player traverses during the game. Handles where the player and Wumpus are located, as
well as the number of arrows remaining to the player.
*/
class Cave_system {
public:
	static const int num_caves = 20;

	Cave_system();
	~Cave_system() { clear_caves(); }

	Cave* get_wumpus_cave() const { return wumpus_cave; }
	Cave* get_player_cave() const { return player_cave; }
	int get_num_arrows() const { return num_arrows; }

	void move_wumpus();
	void move_player(Cave*, bool);
	void decr_arrows() { --num_arrows; }
	Cave* get_cave(int i) { return caves[i]; }
private:
	const int num_pits = 3;
	const int num_bats = 3;

	std::vector<Cave*> caves;
	Cave* wumpus_cave;
	Cave* player_cave;
	int num_arrows = 5;

	void clear_caves();
	void remove_cave(std::vector<Cave*>&, int);
	void connect_cave(std::vector<Cave*>&, Cave*);
};

/*
Returns a cave selected at random from a vector of caves.
*/
inline Cave* get_rand_cave(std::vector<Cave*>& rand_caves) { return rand_caves[rand() % rand_caves.size()]; }