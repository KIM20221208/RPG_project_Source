// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

class UButton;

/**
 * Widget generated After RPG_projectCharacter dead
 */
UCLASS()
class RPG_PROJECT_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void OnRestartButtonClick();

	
private:
	// Button widget: Restart game after user click
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
};
