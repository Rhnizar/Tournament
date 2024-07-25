
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int rollDie() {
    return rand() % 6 + 1;
}

struct Player {
    int id;
    Player(int id) : id(id) {}
};

Player* playMatch(Player* player1, Player* player2) {
    int player1Roll, player2Roll;
    do {
        player1Roll = rollDie();
        player2Roll = rollDie();

        cout << "Player " << player1->id << " rolls: " << player1Roll << endl;
        cout << "Player " << player2->id << " rolls: " << player2Roll << endl;

        if (player1Roll > player2Roll) {
            cout << "Player " << player1->id << " wins this match!" << endl;
            return player1;
        } else if (player2Roll > player1Roll) {
            cout << "Player " << player2->id << " wins this match!" << endl;
            return player2;
        } else {
            cout << "It's a tie! Rerolling..." << endl;
        }
    } while (player1Roll == player2Roll);
    
    // This line will never be reached because the loop will continue until there is a winner.
    return nullptr;
}

void playRound(vector<Player*>& players, const string& stageName) {
    cout << "\n--- " << stageName << " ---" << endl;
    vector<Player*> winners;
    for (size_t i = 0; i < players.size(); i += 2) {
        Player* winner = playMatch(players[i], players[i + 1]);
        winners.push_back(winner);
    }
    players = winners;
}


void tournament(vector<Player*>& players) {
    int numPlayers = players.size();
    if (numPlayers == 4) {
        playRound(players, "Semifinals");
        playRound(players, "Final");
    } else if (numPlayers == 8) {
        playRound(players, "Quarterfinals");
        playRound(players, "Semifinals");
        playRound(players, "Final");
    } else if (numPlayers == 16) {
        playRound(players, "Round of 16");
        playRound(players, "Quarterfinals");
        playRound(players, "Semifinals");
        playRound(players, "Final");
    } else {
        cout << "Invalid number of players. Please enter 4, 8, or 16." << endl;
    }

    if (!players.empty()) {
        cout << "\nPlayer " << players[0]->id << " wins the tournament!" << endl;
    }
}


int main() {
    srand(time(0));

    int numPlayers;
    cout << "Enter the number of players (4, 8, or 16): ";
    cin >> numPlayers;

    if (numPlayers != 4 && numPlayers != 8 && numPlayers != 16) {
        cout << "Invalid number of players. Please enter 4, 8, or 16." << endl;
        return 1;
    }

    vector<Player*> players;
    for (int i = 1; i <= numPlayers; i++) {
        players.push_back(new Player(i));
    }

    tournament(players);

    for (Player* player : players) {
        delete player;
    }

    return 0;
}