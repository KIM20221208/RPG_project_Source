// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "GraphicPresetButtonsUI.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UGraphicPresetButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()


protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;

private:
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* LowButton;
	
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* MediumButton;
	
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* HighButton;

	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* UltraButton;
	
};
