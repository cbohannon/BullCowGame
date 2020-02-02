// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "pch.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Welcome the player
    PrintLine(TEXT("Welcome to the Bull - Cows game!"));
    PrintLine(TEXT("Guess the four letter word.")); // Remove the magic number
    PrintLine(TEXT("Press enter to continue...")); // Does this really make any sense here?

    SetupGame();// Setup the game

    // Set some lives
    // Prompt player for a guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Check the player guess 

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
    }
    else
    {
        PrintLine(TEXT("You lose!"));
    }

    // Check if Isogram
    // Prompt to guess again
    // Check the correct number of characters
    // Remove life
    // Are lives > zero
    // If TRUE , GuessAgin
    // If FALSE, lose life
    // Show remaining lives
    // Show HiddenWord?
    // Prompt to play again or quit
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4;
}