// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGamePauseUI.generated.h"

class UButton;

/**
 * Widget generated After "ESC" key pressed in game mode
 */
UCLASS()
class RPG_PROJECT_API UInGamePauseUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnResumeButtonClick();
	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	
	
	UFUNCTION()
	virtual void OnRestartButtonClick();
	
	UFUNCTION()
	virtual void OnOptionButtonClick();
	
	UFUNCTION()
	virtual void OnBackToMainMenuButtonClick();
	
	UFUNCTION()
	virtual void OnQuitButtonClick();

	
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
