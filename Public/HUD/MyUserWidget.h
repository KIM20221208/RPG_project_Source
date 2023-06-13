// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * Parent class of all Widget of this game
 */
UCLASS()
class RPG_PROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

	
protected:
	// ゲームをリスタートする。
	UFUNCTION()
	void OnRestartButtonClick();
	
};
