/*
@author Jay Peterson
Console executable that uses the BullCowGame class. It handles all interaction with the player
*/

#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include "FBullCowGame.h"

//these make the code Unreal-friendly
using FText = std::string;
using int32 = int;

//function prototypes
void PrintIntro(FBullCowGame);
void PlayGame(void);
FText GetValidGuess(void);
void PrintGuess(FBullCowCount);
bool AskToPlayAgain(void);
void PrintGameSummary(FBullCowGame);

FBullCowGame BCGame;	//instantiate a new game, reset for each play

int main(void)
{
	do
	{
		//We will introduce the game and play at least once, then ask to play again each time afterwards
		PrintIntro(BCGame);
		PlayGame();
		PrintGameSummary(BCGame);
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro(FBullCowGame BCGame)
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^    \"\"^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " isogram that I'm thinking of?\n" << std::endl;
}

/*
Gets valid guesses from the player and prints number of bulls and cows for each guess
The game ends when player is out of guesses or guesses the hidden word exactly
*/
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop while the games hasnt been won and the player has tries remaining
	while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= MaxTries))
	{
		FText Guess = GetValidGuess();

		EGuessStatus GuessStatus = BCGame.CheckGuessStatus(Guess);

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		PrintGuess(BullCowCount);
	}

	return;
}

//Loop until a valid guess is entered
FText GetValidGuess(void)
{
	FText Guess = "";	//variable to store player's guess
	EGuessStatus GuessStatus = EGuessStatus::InvalidStatus;

	//Get a guess at least once, loop if an error is found
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ": ";
		std::cout << "What is you guess? ";	//Prompt user 
		std::getline(std::cin, Guess);	//Store input in Guess variable

		GuessStatus = BCGame.CheckGuessStatus(Guess);
		switch (GuessStatus)
		{
		case (EGuessStatus::NotIsogram):
			std::cout << "Please enter a word with no repeated letters.\n\n";
			break;
		case (EGuessStatus::NotLowercase):
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		case (EGuessStatus::WrongLength):
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		default:
			break;
		}
	} while (GuessStatus != EGuessStatus::Okay);	//loop until we detect no errors
	return Guess;
}

//print out the number of bulls and cows from players guess (extra newline afterward)
void PrintGuess(FBullCowCount BullCowCount)
{
	std::cout << "Bulls = " << BullCowCount.Bulls;
	std::cout << "\tCows = " << BullCowCount.Cows << "\n\n";
}

//Prmpts the user to input a y\n if they want to play again, returns a boolean
bool AskToPlayAgain(void)
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";	//Ask to play again
	FText Response = "";
	std::getline(std::cin, Response);	//get response
	std::cout << std::endl << std::endl;	//print two extra newlines
	if (tolower(Response[0]) == 'y')
	{
		return true;	//return true if the first letter read is y or Y
	}
	else
	{
		return false;	//return false if the first letter read is not y or Y
	}
}

/*
Displays different text depending on the outcome of the game
*/
void PrintGameSummary(FBullCowGame BCGame)
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You guessed the correct word!\n";
	}
	else
	{
		std::cout << "You ran out of tries!\n";
	}
}
