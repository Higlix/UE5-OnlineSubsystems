// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSessionSettings.h"

void UMenu::HostButtonClicked()
{
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			1,
			15.f,
			FColor::Yellow,
			FString(TEXT("Join Button Pressed"))
		);
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();

	if (World)
	{
		APlayerController* playerController = World->GetFirstPlayerController();
		if (playerController)
		{
			FInputModeGameOnly InputModeData;
			playerController->SetInputMode(InputModeData);
			playerController->SetShowMouseCursor(false);
		}
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return (false);
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}

	return (true);
}

void UMenu::NativeDestruct()
{
	MenuTearDown();

	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				INDEX_NONE,
				15.f,
				FColor::Green,
				FString(TEXT("Session Creation Successful"))
			);
		}
		UWorld* World = GetWorld();

		if (World)
		{
			World->ServerTravel(FString("/Game/ThirdPerson/Maps/LobbyMap?listen"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				INDEX_NONE,
				15.f,
				FColor::Red,
				FString(TEXT("Session Creation Failed"))
			);
		}
	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionsResults, bool bWasSuccessful)
{
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
}

void UMenu::OnDestroySession(bool bWasSuccesful)
{
}

void UMenu::OnStartSession(bool bWasSuccesful)
{
}

void UMenu::MenuSetup(int32 playerLimit, FString TypeOfMatch)
{
	NumPublicConnections = playerLimit;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* playerController = World->GetFirstPlayerController();
		if (playerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			playerController->SetInputMode(InputModeData);
			playerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
		MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	}
}