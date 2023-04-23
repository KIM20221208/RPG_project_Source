// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "GameOverUI.generated.h"

class UButton;

/**
 * Widget generated After RPG_projectCharacter dead
 */
UCLASS()
class RPG_PROJECT_API UGameOverUI : public UMyUserWidget
{
	GENERATED_BODY()

protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	
	
private:
	// Button widget: Restart game after user click
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
};
