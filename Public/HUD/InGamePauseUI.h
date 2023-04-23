// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "InGamePauseUI.generated.h"

class UButton;

/**
 * Widget generated After "F10" key pressed in game mode
 */
UCLASS()
class RPG_PROJECT_API UInGamePauseUI : public UMyUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnResumeButtonClick();
	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	
	
	UFUNCTION()
	void OnOptionButtonClick();
	
	UFUNCTION()
	void OnBackToMainMenuButtonClick();
	
	UFUNCTION()
	void OnQuitButtonClick();

	
private:
	// Button widget: Restart game after user click
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackToMainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
};
