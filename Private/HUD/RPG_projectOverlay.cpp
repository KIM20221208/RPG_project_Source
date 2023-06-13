// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RPG_projectOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void URPG_projectOverlay::SetHealthProgressBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
		
	}
	
}

void URPG_projectOverlay::SetStaminaProgressBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
		
	}
	
}

void URPG_projectOverlay::SetGold(int32 Gold)
{
	if (GoldCountText)
	{
		// P196.SetText function needs FText type as input,
		// FString::Printf makes param to FString and FText::FromString makes param to FText
		const FString GoldString = FString::Printf((TEXT("%d")), Gold);
		const FText GoldText = FText::FromString(GoldString);
		GoldCountText->SetText(GoldText);
		
	}
	
}

void URPG_projectOverlay::SetSouls(int32 Souls)
{
	if (SoulCountText)
	{
		// P196.SetText function needs FText type as input,
		// FString::Printf makes param to FString and FText::FromString makes param to FText
		const FString SoulsString = FString::Printf((TEXT("%d")), Souls);
		const FText SoulsText = FText::FromString(SoulsString);
		SoulCountText->SetText(SoulsText);
		
	}
	
}
