// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "pch.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("DEBUG-The HiddenWord is: %s."), *HiddenWord); // This is a debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (!bGameOver)
    {
        ProcessGuess(Input); // Checking the player guess
    }
    else 
    {
        ClearScreen();
        SetupGame();
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcome the player
    PrintLine(TEXT("Welcome to the Bull - Cows game!"));
    
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len(); // Let the player have the lives equal to the length(difficulty)
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word. You have %i lives."), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Type your guess and hit enter to continue."));

    // const TCHAR HW[] = TEXT("plumes");
    // const TCHAR HW[] = { TEXT('c'), TEXT('a'), TEXT('k'), TEXT('e'), TEXT('s'), TEXT('\0')};
    // PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    // PrintLine(TEXT("The 4th character of HW is: %c"), HW[3]);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\nPlease press Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again. \nYou have %i lives remaining."), Lives);

        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    // Subtract one life
    PrintLine(TEXT("You lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();

        PrintLine(TEXT("You have no lives left."));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);

        EndGame();
        
        return;
    }

    // Show the player the bulls and the cows
    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word)
{
    // For each letter we are going to start at element 0 
    // Compare the next letter
    // until we reach the word length -1
    // if any letters are the same return false

    return true;
}