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
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking the player guess
    {
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You win!"));
            EndGame();
        }
        else
        {
            PrintLine(TEXT("You lost a life!"));
            PrintLine(TEXT("%i"), --Lives);

            if (Lives > 0)
            {
                if (Input.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("Sorry, try guessing again. \nYou have %i lives remaining."), Lives);
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left."));
                EndGame();
            }
        }
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
    // PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type your guess and hit enter to continue."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("Please press Enter to play again."));
}