// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPG_projectOverlay.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * P196. Show HUD of RPG_projectcharacter class, parent class of WBP(Widget Blue Print) in UE5 Editor
 */
UCLASS()
class RPG_PROJECT_API URPG_projectOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
/**
 * Getter & Setter
 */
	// P196.Set value for progress bar by percent
	void SetHealthProgressBarPercent(float Percent);
	void SetStaminaProgressBarPercent(float Percent);
	void SetGold(int32 Gold);
	void SetSouls(int32 Souls);
	
private:
	// P196.declaration of Progress Bar in WBP, gotta be the same name as WBP components
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaProgressBar;

	// P196.declaration of Text Block in WBP, gotta be the same name as WBP components
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SoulCountText;
	
};
