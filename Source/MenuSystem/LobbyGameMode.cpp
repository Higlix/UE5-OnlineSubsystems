// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int playerCount = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				3,
				5.f,
				FColor::Blue,
				FString::Printf(TEXT("PlayerCount: %d"), playerCount)
			);

			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				FString newPlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
					INDEX_NONE,
					5.f,
					FColor::Blue,
					FString::Printf(TEXT("NewPlayerName: %s"), *newPlayerName)
				);
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	


	if (GEngine)
	{
		int playerCount = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(
			3,
			5.f,
			FColor::Blue,
			FString::Printf(TEXT("PlayerCount: %d"), playerCount - 1)
		);

		APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
		if (PlayerState)
		{
			FString ExitingPlayerName = PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(
				INDEX_NONE,
				5.f,
				FColor::Blue,
				FString::Printf(TEXT("NewPlayerName: %s"), *ExitingPlayerName)
			);
		}
	}
}
