// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SettingsBackGroundUI.h"


void USettingsBackGroundUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	FadeInFX();
	
}

void USettingsBackGroundUI::CloseMe()
{
	UUserWidget::RemoveFromParent();
	
}

void USettingsBackGroundUI::FadeInFX()
{
	PlayAnimation(FadeIn);
	
}

void USettingsBackGroundUI::FadeOutFX()
{
	PlayAnimation(FadeIn,0, 1, EUMGSequencePlayMode::Reverse);
	
}
