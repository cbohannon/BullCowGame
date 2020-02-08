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
    
    HiddenWord = TEXT("isogram");
    Lives = HiddenWord.Len(); // Let the player have the lives equal to the length(difficulty)
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word. You have %i lives."), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Type your guess and hit enter to continue."));
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

    /*
    if (!IsIsogram)
    {
        PrintLine(TEXT("No repeating letters, guess again."));
    }
    */

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again. \nYou have %i lives remaining."), Lives);

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