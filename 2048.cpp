/*
 * 2048.cpp
 * COMP11 Project 1, Spring 2019, Tufts University
 * Modified by: Alexander Eldaief
 * Date: 03/05/2019
 */

#include <iostream>
#include <time.h>
#include <sstream>
using namespace std;

const char LEFT = 'a';
const char RIGHT = 'd';
const char UP = 'w';
const char DOWN = 's';
const char QUIT = 'q';

const int SIZE = 4;

void play();
void print_board(int gameboard[SIZE][SIZE], int score);
void game_start(int gameboard[SIZE][SIZE]);
int move_up(int gameboard[SIZE][SIZE], int c);
int move_down(int gameboard[SIZE][SIZE], int c);
int move_left(int gameboard[SIZE][SIZE], int r);
int move_right(int gameboard[SIZE][SIZE], int r);
void adding_tiles(int gameboard[SIZE][SIZE]);
void current_score(int gameboard[SIZE][SIZE]);
bool check_lost(int gameboard[SIZE][SIZE]);
int string2int(string s);
string int2string(int num);
void print_padded_string(string s);


int main() {
    play();
    return 0;
}

// play -- runs the program by calling all the functions written in the program.
// args: N/A 
// rets: nothing (void function)
void play() {

    int gameboard[SIZE][SIZE];
    cout << "Starting Game!" << endl;
    int score = 0;
    game_start(gameboard);
    print_board(gameboard, score);
    
    char input = ' ';

    while(input != QUIT) {
        
        cin >> input;

        if (input == QUIT) {
            cout << "Game Over. Your score is: " << score << endl;
        } 

        else if (input != UP and input != DOWN and input != RIGHT and 
            input != LEFT) {
            cout << "Command not recognized. Please try again." << endl;
        }

        else {
            
            if (input == LEFT) {
                for (int i = 0; i < SIZE; i++) {
                    score += move_left(gameboard, i);
                }
            } 

            else if (input == RIGHT) {
                for (int i = 0; i < SIZE; i++) {
                    score += move_right(gameboard, i);

                }
            }

            else if (input == UP) {
                for (int i = 0; i < SIZE; i++) {
                    score += move_up(gameboard, i);
                }
            }

            else if (input == DOWN) {
                for (int i = 0; i < SIZE; i++) {
                    score += move_down(gameboard, i);
                }
            }

            adding_tiles(gameboard);

            print_board(gameboard, score); 
        
            if (check_lost(gameboard)) {
                input = QUIT;
                cout << "Game Over." << endl;
                cout << "Final Score: " << score << endl;
            } 
        }
    }
}

// game_start -- initializes an array with "2's" in two random positions on the 
//               board.
// args: an integer (gameboard array)
// rets: nothing (void function)
void game_start(int gameboard[SIZE][SIZE]) {

    for (int c = 0; c < SIZE; c++) {
        for (int r = 0; r < SIZE; r++) {
            gameboard[c][r] = 0;
        }  
    }

    srand(time(NULL));
    int random_col = (rand() % SIZE);
    int random_row = (rand() % SIZE);
    gameboard[random_col][random_row] = 2;

    int random_col2 = (rand() % SIZE);
    int random_row2 = (rand() % SIZE);
    while ((random_col == random_col2) and (random_row == random_row2)){ 
        random_row2 = (rand() % SIZE);
        random_col2 = (rand() % SIZE);

    }

    gameboard[random_col2][random_row2] = 2;

}

// print_board -- sets all of the values of zero in array to a "-" and prints it
//                to the user.
// args: two integers; gameboard array and score
// rets: nothing (void function)
void print_board(int gameboard[SIZE][SIZE], int score) {

    string x;
    cout << "Current Score: " << score << endl;
    for (int c = 0; c < SIZE; c++){
        for (int r = 0; r < SIZE; r++) {
        
            if (gameboard[c][r] == 0) {
                x = "-";
            } 

            else {
                x = int2string(gameboard[c][r]);
            }

            print_padded_string(x);
        }

        cout << endl;

    }

}

// move_up -- sets the condition for when the user decides to move up and 
//              adds up numbers when they are the same.
// args: an integer (gameboard array) and an integer
// rets: score upwards
int move_up(int gameboard[SIZE][SIZE], int c) {
    int gameboard2[SIZE][SIZE];
    int gameboard2_current = 0;
    int position = 0;
    int score_up = 0;

    for (int r = 0; r < SIZE; r++) {

        if (gameboard[r][c] != 0) {
            gameboard2[gameboard2_current][c] = gameboard[r][c];
            gameboard2_current++;
        } 
    }

    for (int r = 0; r < SIZE; r++) {
            gameboard[r][c] = 0;
    }

    for (int r = 0; r < gameboard2_current; r++) {
        if (gameboard2[r][c] == gameboard2[r+1][c]) {
            gameboard[position][c] = 2 * gameboard2[r][c];
            r++;
            score_up += gameboard[position][c];
        } 

        else {
            gameboard[position][c] = gameboard2[r][c];
        }

        position++;
    }

    return score_up;
}

// move_down -- sets the condition for when the user decides to move down and 
//               adds up numbers when they are the same.
// args: an integer (gameboard array) and an integer
// rets: the score downwards
int move_down(int gameboard[SIZE][SIZE], int c) {
    int gameboard2[SIZE][SIZE];
    int gameboard2_current = SIZE - 1;
    int position = SIZE - 1;
    int score_down = 0;

    for (int r = SIZE-1; r > -1; r--) {
        if (gameboard[r][c] != 0) {
            gameboard2[gameboard2_current][c] = gameboard[r][c];
            gameboard2_current--;
        }
    }

    for (int r = SIZE - 1; r > -1; r--) {
        gameboard[r][c] = 0;
    }

    for (int r = SIZE - 1; r > gameboard2_current; r--) {
        if (gameboard2[r][c] == gameboard2[r-1][c]) {
            gameboard[r][c] = 2 * gameboard2[r][c] ;
            score_down += gameboard[r][c];
            r--;
        } 

        else {
            gameboard[position][c] = gameboard2[r][c];
        }
    
        position--;
    }

    return score_down;
}

// move_left -- sets the condition for when the user decides to move left and 
//              adds up numbers when they are the same.
// args: an integer (gameboard array) and an integer
// rets: the score to the left
int move_left(int gameboard[SIZE][SIZE], int r) {
    int gameboard2[SIZE][SIZE];
    int gameboard2_current = 0;
    int position = 0;
    int score_left = 0;

    for (int c = 0; c < SIZE; c++) {

        if (gameboard[r][c] != 0) {
            gameboard2[r][gameboard2_current] = gameboard[r][c];
            gameboard2_current++;
        } 
    }

    for (int c = 0; c < SIZE; c++) {
            gameboard[r][c] = 0;
    }

    for (int c = 0; c < gameboard2_current; c++) {
        if (gameboard2[r][c] == gameboard2[r][c+1]) {
            gameboard[r][position] = 2 * gameboard2[r][c];
            c++;
            score_left += gameboard[r][position];
        } 

        else {
            gameboard[r][position] = gameboard2[r][c];
        }

        position++;
    }

    return score_left;
}

// move_right -- sets the condition for when the user decides to move right and 
//               adds up numbers when they are the same.
// args: an integer (gameboard array) and an integer
// rets: the score to the right
int move_right(int gameboard[SIZE][SIZE], int r) {
    int gameboard2[SIZE][SIZE];
    int gameboard2_current = SIZE - 1;
    int position = SIZE - 1;
    int score_right = 0;

    for (int c = SIZE-1; c > -1; c--) {
        if (gameboard[r][c] != 0) {
            gameboard2[r][gameboard2_current] = gameboard[r][c];
            gameboard2_current--;
        }
    }

    for (int c = SIZE - 1; c > -1; c--) {
        gameboard[r][c] = 0;
    }

    for (int c = SIZE - 1; c > gameboard2_current; c--) {
        if (gameboard2[r][c] == gameboard2[r][c-1]) {
            gameboard[r][c] = 2 * gameboard2[r][c];
            score_right += gameboard[r][c];
            c--;

        } 

        else {
            gameboard[r][position] = gameboard2[r][c];

        }
    
        position--;
    }

    return score_right;
}

// adding_tiles -- adds new tiles of value either 4 or 2 in a random position on
//                 the board where the value of the array position is zero.
// args: an integer (gameboard array)
// rets: nothing (void function)
void adding_tiles(int gameboard[SIZE][SIZE]) {
   
    srand(time(NULL));
    int random_col = (rand() % SIZE);
    int random_row = (rand() % SIZE);

    int rn = (rand() % 10);

    while (gameboard[random_row][random_col] != 0) {
        random_col = (rand() % SIZE);
        random_row = (rand() % SIZE);

    }

    if (rn != 0) {
            gameboard[random_row][random_col] = 2;
    } 

    else {
            gameboard[random_row][random_col] = 4;
    } 
}

// check_lost -- checks the conditions for which the game is over, i.e. when the
//               gameboard is full.
// args: an integer (gameboard array)
// rets: a variable of type bool
bool check_lost(int gameboard[SIZE][SIZE]) {
    for (int c = 0; c < SIZE-1; c++) {
        for (int r = 0; r < SIZE - 1; r++) {
            if (gameboard[c][r] != SIZE-1) {
                if (gameboard[c][r] == gameboard[c][r+1]) {
                    return false;
                }

                if (gameboard[c][r] == gameboard[c+1][r]) {
                    return false;
                }
            }
        }
    }

    for (int c = 0; c < SIZE; c++) {
        for (int r = 0; r < SIZE - 1; r++) {
            if (gameboard[c][r] == 0) {
                return false;
            }
        }
    }

    return true;
}

/* string2int
 * Convert a string to an int. Returns the int form of the given string.
 * Throw logic error if the string is not numerical. 
 */
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* Converts an int to string.
 * Returns the string form of the given int
 */
string int2string(int num) {
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}

/* Print a string (persumably an int in the form of a string) with 
 * right paddings of up to 5 spaces
 */
void print_padded_string(string s) {
    printf("%-6s", s.c_str());
}