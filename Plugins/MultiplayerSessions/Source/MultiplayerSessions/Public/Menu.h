// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"


#include "Menu.generated.h"

/**
 * 
 */

class UButton;
class UMultiplayerSessionsSubsystem;

UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget)) /* To automaticly find the corresponding button with the same name*/
		UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();


	void MenuTearDown();

	/* Online Subsystem */
	UMultiplayerSessionsSubsystem* MultiplayerSessionSubsystem;


	int32 NumPublicConnections{ 4 };
	FString MatchType{ TEXT("FreeForAll") };

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	/*
		Callbacks for the custom delegates on the MultiplayerSS
	*/
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionsResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void OnDestroySession(bool bWasSuccesful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccesful);

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 playerLimit = 4, FString MatchType = TEXT("FreeForAll"));
};
