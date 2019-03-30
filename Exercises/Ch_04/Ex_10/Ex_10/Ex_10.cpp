#include "../../../../std_lib_facilities.h"

int main() {
	int player_move = 0, computer_move = 0;
	vector<string> moves = { "rock", "paper", "scissors" };

	// ask the user for their move
	cout << "Enter 0 for 'rock,' 1 for 'paper,' or 2 for 'scissors': ";
	while (cin >> player_move) {
		// randomize the computer's move
		computer_move = randint(0, 2);

		// reject invalid input
		if (player_move < 0 || player_move > 2)
			cout << "Enter a number from 0 to 2.\n";
		// output the result of the game
		else {
			cout << "You chose " << moves[player_move] <<
				" and the computer chose " << moves[computer_move] << ". ";
			switch (player_move) {
			case 0:
				cout << (computer_move == 0 ? "You tied." : (computer_move == 1 ? "You lost." : "You won."));
				break;
			case 1:
				cout << (computer_move == 1 ? "You tied." : (computer_move == 2 ? "You lost." : "You won."));
				break;
			case 2:
				cout << (computer_move == 2 ? "You tied." : (computer_move == 0 ? "You lost." : "You won."));
				break;
			}

			cout << endl;
		}
	}
}