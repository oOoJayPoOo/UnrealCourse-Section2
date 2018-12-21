/*@author Jay Peterson*/

#include <iostream>
#include <string>
#include <ctype.h>
#include "FBullCowGame.h"

void PrintIntro(void);
void PlayGame(void);
std::string GetGuess(void);
void PrintGuess(std::string);
bool AskToPlayAgain(void);

FBullCowGame BCGame;	//instantiate a new game

int main(void)
{
	do
	{
		//We will introduce the game and play at least once, then ask to play again each time afterwards
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro(void)
{
	constexpr int WORD_LENGTH = 5;

	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " isogram that I'm thinking of?\n" << std::endl;
}

//Gets players guess and prints it out for each guess, game ends when player is out of guesses
void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();
	for (int i = 0; i < MaxTries; i++)
	{
		std::string Guess = GetGuess();
		PrintGuess(Guess);
	}
}

//Prompts players for guess and returns the guess as a string
std::string GetGuess(void)
{
	int CurrentTry = BCGame.GetCurrentTry();
	std::string Guess = "";	//variable to store player's guess
	std::cout << "Try " << CurrentTry << ": What is you guess? ";	//Prompt user 
	std::getline(std::cin, Guess);	//Store input in Guess variable
	return Guess;	//return guess as string
}

void PrintGuess(std::string Guess)
{
	std::cout << "Your guess: " << Guess << "\n" << std::endl;	//print out the players guess (extra newline afterward)
}

//Prmpts the user to input a y\n if they want to play again, returns a boolean
bool AskToPlayAgain(void)
{
	std::cout << "Do you want to play again? (y/n) ";	//Ask to play again
	std::string Response = "";
	std::getline(std::cin, Response);	//get response
	std::cout << std::endl;	//print extra newline
	if (tolower(Response[0]) == 'y')
	{
		return true;	//return true if the first letter read is y or Y
	}
	else
	{
		return false;	//return false if the first letter read is not y or Y
	}
}