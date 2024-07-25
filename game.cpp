#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()
#include <vector>

using namespace std;

class Player
{
    public:
        int id;
        string name;

        Player(int id, string name);
};

Player::Player(int id, string name) : id(id), name(name)
{
    // id = id;
    // name = name;
}
// Function to simulate rolling a die
int rollDie() {
    return rand() % 6 + 1; // Generate a random number between 1 and 6
}

// // Function to play the game
// void playGame(int targetWins) {
//     int player1Wins = 0;
//     int player2Wins = 0;

//     while (player1Wins < targetWins && player2Wins < targetWins) {
//         int player1Roll = rollDie();
//         int player2Roll = rollDie();

//         cout << "Player 1 rolls: " << player1Roll << endl;
//         cout << "Player 2 rolls: " << player2Roll << endl;

//         if (player1Roll > player2Roll) {
//             cout << "Player 1 wins this round!" << endl;
//             player1Wins++;
//         } else if (player2Roll > player1Roll) {
//             cout << "Player 2 wins this round!" << endl;
//             player2Wins++;
//         } else {
//             cout << "It's a tie!" << endl;
//         }

//         cout << "Score: Player 1 = " << player1Wins << ", Player 2 = " << player2Wins << endl << endl;
//     }

//     if (player1Wins == targetWins) {
//         cout << "Player 1 wins the game!" << endl;
//     } else {
//         cout << "Player 2 wins the game!" << endl;
//     }
// }

// Function to play the game
Player playGame(int targetWins, Player p1, Player p2) {
    int player1Wins = 0;
    int player2Wins = 0;

    while (player1Wins < targetWins && player2Wins < targetWins) {
        int player1Roll = rollDie();
        int player2Roll = rollDie();

        cout << p1.name << "  rolls: " << player1Roll << endl;
        cout << p2.name << "  rolls: " << player2Roll << endl;

        if (player1Roll > player2Roll) {
            cout << p1.name <<" wins this round!" << endl;
            player1Wins++;
        } else if (player2Roll > player1Roll) {
            cout << p2.name << " wins this round!" << endl;
            player2Wins++;
        } else {
            cout << "It's a tie!" << endl;
        }

        cout << "Score: " << p1.name << " = " << player1Wins << ", " << p2.name << " = " << player2Wins << endl << endl;
    }

    if (player1Wins == targetWins) {
        cout << p1.name << " wins the game!" << endl;
        return p1;
    } else {
        cout << p2.name << " wins the game!" << endl;
        return p2;
    }
    return Player(100, "Test");
}

vector<Player> Organize_Tournament(int numberPlayers)
{
    vector<Player> Players;
    if(numberPlayers != 4 && numberPlayers != 8 && numberPlayers != 16)
    {
        cout << "Tournament accepts only 4, 8 or 16 players\n";
        exit(1);
    }
    for(size_t i=0; i<(size_t)numberPlayers; i++)
    {
        string name;
        cout << "Enter name of player " << i+1 << " : ";
        cin >> name;
        Player p(i+1, name);
        Players.push_back(p);
    }
    return Players;
}

int main() {
    srand(time(0)); // Seed the random number generator
    Player p1(1, "P1");
    Player p2(2, "P2");
    int targetWins = 3;
    // cout << "Enter the number of wins required to win the game: ";
    // cin >> targetWins;

    int numberPlayers;
    cout << "Enter the number of players in this tournament :  ";
    cin >> numberPlayers;
    vector<Player> Players = Organize_Tournament(numberPlayers);
    cout << "List of  Players in this tournament: \n";
    for(size_t i=0; i<Players.size(); i++)
    {
        cout << "id: " << Players[i].id << "  name:   " << Players[i].name << endl;
    }
    vector<Player> SemiFinal;
    cout << "\n==================\n";
    for(size_t i=0; i<Players.size(); i+=2)
    {
        Player Pl = playGame(targetWins, Players[i], Players[i+1]);
        SemiFinal.push_back(Pl);
        cout << "Player with id : " << Pl.id << " and name :  "<< Pl.name << "  is win." << endl;
    }
    cout << "\n==================\n";
    vector<Player> Final;
    for(size_t i=0; i<SemiFinal.size(); i+=2)
    {
        Player Pl = playGame(targetWins, SemiFinal[i], SemiFinal[i+1]);
        Final.push_back(Pl);
    }
    if(Final.size() == 1)
    {
        cout << "Player with id : " << Final[0].id << " and name :  "<< Final[0].name << "  is win the tournament." << endl;
    }
    return 0;
}
