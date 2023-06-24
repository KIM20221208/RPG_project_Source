// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SettingsBackGroundUI.h"

void USettingsBackGroundUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	FadeInFX();
	
}

void USettingsBackGroundUI::CloseSettingsBackGroundUI()
{
	UUserWidget::RemoveFromParent();
	FadeOutFx();
	UE_LOG(LogTemp, Warning, TEXT("Close Settings BackGround UI triggered"))
	
}

void USettingsBackGroundUI::FadeInFX()
{
	PlayAnimation(FadeIn);
	
}

void USettingsBackGroundUI::FadeOutFx()
{
	PlayAnimation(FadeIn,0, 1, EUMGSequencePlayMode::Reverse);
	
}
