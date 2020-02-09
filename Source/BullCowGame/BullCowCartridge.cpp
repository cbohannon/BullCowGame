// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "FileHelper.h"
#include "pch.h"
#include <Runtime\Core\Public\Misc\Paths.h>


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    TArray<FString> WordListFile;
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordListFile, *WordListPath);

    SetupGame();

    PrintLine(TEXT("The number of possible words is %i."), WordListFile.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(WordListFile).Num());
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
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\nPlease press Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    // TODO: The three early return functions can be placed in a const function 
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

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 index = 0; index < Word.Len(); index++)
    {
        for (int32 Comparison = index + 1 ; Comparison < Word.Len(); Comparison++)
        {
            if (Word[index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    for (FString CurrentWord : WordList)
    {
        if (CurrentWord.Len() >= 4 && CurrentWord.Len() <= 8)
        {
            if (IsIsogram(CurrentWord))
            {
                ValidWords.Emplace(CurrentWord);
            }
        }
    }

    return ValidWords;
}