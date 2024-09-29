// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	/* Online Subsystem */
	UMultiplayerSessionsSubsystem* MultiplayerSessionSubsystem;

protected:
	virtual bool Initialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();
};
