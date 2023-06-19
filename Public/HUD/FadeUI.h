// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeUI.generated.h"

/**
 * 
 */

UCLASS()
class RPG_PROJECT_API UFadeUI : public UUserWidget
{
	GENERATED_BODY()

	
public:
	void PlayFadeInAnimation();

	
private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* fadeIn;
	
};
