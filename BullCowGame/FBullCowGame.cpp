/*
@author Jay Peterson
BullCowGame class implementation
*/

#pragma once
#include "FBullCowGame.h"
#include <map>

//these make the code Unreal-friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

/*
Gets number of max tries based on the length of the hidden word
@return the max number of tries as an integer
*/
int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries = { {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

/*
Checks for certain errors in the players guess
@param the players guess as a string
@return the status of the guess as an enumerated type
*/
EGuessStatus FBullCowGame::CheckGuessStatus(FString Guess) const
{
	if (!IsIsogram(Guess))//not isogram
	{
		return EGuessStatus::NotIsogram;
	}
	else if (!IsLowercase(Guess))//not lowercase
	{
		return EGuessStatus::NotLowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	else
	{
		return EGuessStatus::Okay;
	}
}

/*
Resets the current try and win state boolean
*/
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";	//This word must be an isogram
	
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameWon = false;
	return;
}

//takes in valid guess, increments try counter, and returns count as struct
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();	//both guess and hidden word are same length when guess is valid

	//go through letters in the try, compare to secret word, counting bulls and cows
	for (int i = 0; i < WordLength; i++)
	{
		for (int j = 0; j < WordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j])	//characters match
			{
				if (i == j)	//characters are at the same index
				{
					BullCowCount.Bulls++;
				}
				else	//characters are not at the same index
				{	
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)	//Bulls indicate correctly guessed letter
	{	//if # of bulls equals the length of the hidden word, each letter was guessed correctly, game has been won
		bGameWon = true;
	}
	else
	{	//ints were not equal, game has not been won
		bGameWon = false;
	}

	return BullCowCount;
}

/*
Checks to see if each character in the string is unique
@param a string to iterate through, checking the letters
@return false if a repeated letter was found, true otherwise
*/
bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)	//there cant be repeated letters if there aren't atleast 2 chars
	{
		return true;
	}

	TMap<char, bool> LettersSeen;	//create map for letters seen

	for (auto Letter : Guess)//go through letters in guess
	{
		Letter = tolower(Letter);
		if (LettersSeen[Letter])
		{
			return false;	//if letter already seen, return false
		}
		else
		{
			LettersSeen[Letter] = true;	//add letter to map
		}
	}

	return true;	//if we go through the guess without finding repeated letters, return true
}

/*
Check to see if each letter in a string is lowercase
@param a string to iterate through, checking each char
@return false if an uppcase letter was found, true otherwise
*/
bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;	//made it through the whole guess without finding an uppercase letter
}