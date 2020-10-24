//============================================================================
// Name        : GuessingGame.cpp
// Author      : Higor Maia Concessa
// Version     : 1.0.0
// License     : GNU General Public License v3.0
// Description : A simple guessing game in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/** Constants **/
const short MAX_SCORE = 1000;
const short ATTEMPT_EASY = 15;
const short ATTEMPT_MEDIUM = 10;
const short ATTEMPT_HARD = 5;
const short ATTEMPT_VERY_HARD = 3;
/**				**/

/** Non Constants **/
bool exitGame;
bool winner = false;
short level;
short attempts;
float score = 100;
short winnerNumber;
/** 			**/

/** Procedures **/
void printWelcome();
void printWinner();
void printLoser();
void printTip(short number);
void printScore(float score);
void selectLevel();
void playAgain();
/**				**/

/** Functions **/
bool isValidLevel(short level);
short randomNumber();
short receiveNumber();
short receiveNewNumber();
float calcScore(float oldScore, short number);
/**				**/

int main() {
	printWelcome();
	while(!exitGame){
		winner = false;
		winnerNumber = randomNumber();
		selectLevel();
		if(!exitGame){
			cout << "Attempt " << 1 << " of " << attempts << endl;
			int playerNumber = receiveNumber();

			if(playerNumber != winnerNumber){
				printTip(playerNumber);
				for(int i = 1; i < attempts; i++){
					cout << "Attempt " << i+1 << " of " << attempts << endl;
					playerNumber = receiveNewNumber();
					score = calcScore(score, playerNumber);
					if(playerNumber == winnerNumber){
						winner = true;
						printWinner();
						printScore(score);
						playAgain();
						break;
					}else{
						printTip(playerNumber);
					}
				}
				if(!winner){
					cout << "The secret number is " << winnerNumber << endl;
					printLoser();
					printScore(score);
					playAgain();
				}
			}else{
				winner = true;
				printWinner();
				playAgain();
			}
		}
	}
	cout << "Thank you, good bye!" << endl;
	return 0;
}

void printWelcome(){
	cout << endl;
	cout << "*******************************************************" << endl;
	cout << "********** Welcome to number guessing game! ***********" << endl;
	cout << "*******************************************************" << endl << endl;
}

void printWinner(){
	cout << endl;
	cout << "**       *************************************       **" << endl;
	cout << "************** CONGRATULATIONS! YOU WIN! **************" << endl;
	cout << "**       *************************************       **" << endl << endl;
}

void printLoser(){
	cout << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "X X X X X X X X X  MY BAD! YOU LOSE!  X X X X X X X X X" << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl << endl;
}

void printScore(float score){
	cout.precision(2);
	cout << fixed;
	cout << "Score: " << score << endl << endl;
}

void selectLevel(){
	cout << "Choose the game level:" << endl;
	cout << "1 - Easy" << endl;
	cout << "2 - Medium" << endl;
	cout << "3 - Hard" << endl;
	cout << "4 - Very Hard" << endl;
	cout << "0 - Exit" << endl << endl;
	cin >> level;

	if(isValidLevel(level)){
		cout << "Level " << level << " selected! God game!" << endl << endl;
	}else if(exitGame){
		return;
	}else{
		cout << "Invalid level! Please, select a valid level or digit 0 to exit." << endl;
		selectLevel();
	}
}

bool isValidLevel(short level){
	switch(level){
		case 1:
			attempts = ATTEMPT_EASY;
			return true;
		case 2:
			attempts = ATTEMPT_MEDIUM;
			return true;
		case 3:
			attempts = ATTEMPT_HARD;
			return true;
		case 4:
			attempts = ATTEMPT_VERY_HARD;
			return true;
		case 0:
			exitGame = true;
			return false;
		default:
			return false;
	}
}

short randomNumber(){
	srand(time(NULL));	// Use base time to calc a random number
	/**
	 * % 100 return a number between 0~99
	 * % 1000 return a number between 0~999
	 * etc
	 */
	cout << "A new number between 0 and 99 has generate!" << endl << endl;
	return rand() % 100;
}

short receiveNumber(){
	cout << "Enter the first number to try to guess: " << endl;
	int i;
	cin >> i;
	return i;
}

short receiveNewNumber(){
	cout << "Enter with other number to try to guess: " << endl;
	int i;
	cin >> i;
	return i;
}

float calcScore(float oldScore, short number){
	float newScore = oldScore - abs(number - winnerNumber)/2;
	return newScore;
}

void playAgain(){
	cout << "Play again?" << endl;
	cout << "Yes (Y)" << endl;
	cout << "No (N)" << endl << endl;
	char in;
	cin >> in;

	if(in == 'y' || in == 'Y'){
		exitGame = false;
	} else if(in == 'n' || in == 'N' || in == '0'){
		exitGame = true;
	}else{
		cout << "Invalid answer! Please, try again or digit 0 to exit." << endl;
		playAgain();
	}
}

void printTip(short number){
	cout << endl;
	if(number < winnerNumber){
		cout << "The number " << number << " is lower than the secret number!" << endl << endl;
	}else{
		cout <<"The number " << number << " is bigger than the secret number!" << endl << endl;
	}
}
