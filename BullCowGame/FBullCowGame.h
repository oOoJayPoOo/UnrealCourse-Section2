/*
@author Jay Peterson
BullCowGame class
*/

#pragma once
#include <string>

//these make the code Unreal-friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	InvalidStatus,
	Okay,
	NotIsogram,
	WrongLength,
	NotLowercase
};

class FBullCowGame
{
public:
	FBullCowGame();	//constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessStatus(FString) const;
	bool IsGameWon() const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);	//count number of bulls and cows, increases tries counter

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};