#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int playerChoice, computerChoice;
    int playerWins = 0;
    int computerWins = 0;

    while (playerWins < 3 && computerWins < 3) {
        cout << "\n1. Rock\n2. Paper\n3. Scissors\n";
        cout << "Choose your weapon (1-3): ";
        cin >> playerChoice;

        if (playerChoice < 1 || playerChoice > 3) {
            cout << "Invalid option.\n";
            continue;
        }

        computerChoice = rand() % 3 + 1;

        if (playerChoice == computerChoice) {
            cout << "It's a tie.\n";
        } else if ((playerChoice == 1 && computerChoice == 3) ||
                   (playerChoice == 2 && computerChoice == 1) ||
                   (playerChoice == 3 && computerChoice == 2)) {
            cout << "You won this round.\n";
            playerWins++;
        } else {
            cout << "You lost this round.\n";
            computerWins++;
        }

        cout << "Score: Player " << playerWins << " - " << computerWins << " CPU\n";
    }

    return 0;
}
