#include <iostream>
#include <ctime> // To take the time
using namespace std;

void boarddrawing(char *space); // Function to draw the game board
void playerturn(char *space, char player); // Function to handle the player's turn
void computerturn(char *space, char computer); // Function to handle the computer's turn
bool winner(char *space, char player, char computer); // Function to check if there is a winner
bool tie(char *space); // Function to check if there is a tie

int main (){

    char space[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // creating spaces for the game board
    char player = 'X'; // Player's symbol
    char computer = 'O'; // Computer's symbol
    bool running = true;

    boarddrawing (space); 

    while (running) {
        playerturn(space, player); // Player's turn
        boarddrawing(space); // Draw the board after player's turn

        if (winner (space, player, computer)){
            running = false;
            break;
        }
        if (tie (space)){
            running = false;
            break;
        }
        
        computerturn(space, computer); // Computer's turn
        boarddrawing(space); // Draw the board after computer's turn
        
         if (winner (space, player, computer)){
            running = false;
            break;
        }
        if (tie (space)){
            running = false;
            break;
        }
    }
    cout << "THANKS FOR PLAY\n ";
    return 0;
}
// Define the functions
void boarddrawing(char *space){
 cout << "\n" ;
 cout << "     |     |     "<< "\n";
 cout << "   "<< space[0]<<" |  "<< space[1]<<"  |    "<< space[2]<<" ""\n";
 cout << "_____|_____|_____"<< "\n";
 cout << "     |     |     "<< "\n" ;
 cout << "   "<< space[3]<<" |  "<< space[4]<<"  |    "<< space[5]<<" ""\n";
 cout << "_____|_____|_____"<< "\n";
 cout << "     |     |     "<< "\n" ;
 cout << "   "<< space[6]<<" |  "<< space[7]<<"  |    "<< space[8]<<" ""\n";
 cout << "     |     |     "<< "\n" ;
 cout << "\n" ;
 }
 
void playerturn(char *space, char player){
    int num; // Variable to store the player's choice
    do
    {
        cout << "Enter a number (1-9) to place your " << player << ": ";
        cin >> num; // Get the player's choice
        num--; // Adjust for zero-based indexing

        if (space[num] == ' ') { // Check if the space is empty
            space[num] = player; // Place the player's symbol on the board
            break; // Exit the loop if the move is valid
    } 
} while (!num > 0 && !num < 8); // Validate the input to ensure it's between 1 and 9
}

void computerturn(char *space, char computer){
 int num;
 srand (time (0));// Seed the random number generator with the current time

 while (true) { // Loop until a valid move is found
    num = rand() % 9; // Generate a random number between 0 and 8

    if (space[num] == ' ') { // Check if the space is empty
        space[num] = computer; // Place the computer's symbol on the board
        break; // Exit the loop if the move is valid
    }
} }

bool winner(char *space, char player, char computer){ //Verifyn who is the winner
//First case when player play in line 1, 2, 3 (horizontal 0,1,2)
    if( (space[0] != ' ') && (space [0] == space[1]) && (space [1] == space[2])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";
} //Second case when player play in line 4, 5, 6 (horizontal 3,4,5)
else if( (space[3] != ' ') && (space [3] == space[4]) && (space [4] == space[5])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";
} //Third case when player play in line 7, 8, 9 (horizontal 6,7,8)
else if( (space[6] != ' ') && (space [6] == space[7]) && (space [7] == space[8])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";

} //First case when player play in line 1, 4, 7 (vertical 0,3,6)
else if( (space[0] != ' ') && (space [0] == space[3]) && (space [3] == space[6])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";
} //Second case when player play in line 2, 5, 8 (vertical 1,4,7)
else if( (space[1] != ' ') && (space [1] == space[4]) && (space [4] == space[7])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";
} //Third case when player play in line 3, 6, 9 (vertical 2,5,8)
else if( (space[2] != ' ') && (space [2] == space[5]) && (space [5] == space[8])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";

} //First case when player play in line 1, 5, 9 (diagonal 0,4,8)
else if( (space[0] != ' ') && (space [0] == space[4]) && (space [4] == space[8])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";
} //Second case when player play in line 3, 5, 7 (diagonal 2,4,6)
else if( (space[2] != ' ') && (space [2] == space[4]) && (space [4] == space[6])){
    space [0] == player;
    cout << "YOU WON \n " << "YOU LOST \n ";
}
else {
    return false; // No winner found
}
}

bool tie(char *space){

    for (int i = 0; i < 9; i++) {
        if (space[i] == ' ') {
            return false; // If any space is empty, it's not a tie
        }
    }
    cout << "It's a tie!" << endl; // If all spaces are filled and no winner, it's a tie
    return true; // All spaces are filled
}