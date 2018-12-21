/*@author Jay Peterson*/

#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

void PrintIntro(void);
void PlayGame(void);
string GetGuess(void);
void PrintGuess(string);
bool AskToPlayAgain(void);

int main(void)
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro(void)
{
	constexpr int WORD_LENGTH = 5;

	cout << "Welcome to Bulls and Cows, a fun word game!\n";
	cout << "Can you guess the " << WORD_LENGTH << " isogram that I'm thinking of?\n" << endl;
}

void PlayGame()
{
	constexpr int NUMBER_OF_GUESSES = 5;
	for (int i = 0; i < NUMBER_OF_GUESSES; i++)
	{
		string Guess = GetGuess();
		PrintGuess(Guess);
	}
}
string GetGuess(void)
{
	string Guess = "";				//variable to store player's guess
	cout << "What is you guess? ";	//Prompt user 
	getline(cin, Guess);			//Store input in Guess variable
	return Guess;					//return guess as string
}

void PrintGuess(string guess)
{
	cout << "Your guess: " << guess << "\n" << endl;	//print out the players guess (extra newline afterward)
}

bool AskToPlayAgain(void)
{
	cout << "Do you want to play again? (y/n) ";
	string Response = "";
	getline(cin, Response);
	cout << endl;
	if (tolower(Response[0]) == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}