// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GraphicPresetButtonsUI.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicPresetButtonsUI::CloseMe()
{
	UUserWidget::RemoveFromParent();
	
}

void UGraphicPresetButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	// イベントのバインド:
	LowButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnLowButtonClicked);
	MediumButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnMediumButtonClicked);
	HighButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnHighButtonClicked);
	UltraButton->OnClicked.AddDynamic(this, &UGraphicPresetButtonsUI::OnUltraButtonClicked);
	
}

void UGraphicPresetButtonsUI::SwitchOverallScalabilityLevel(EOverallScalabilityLevelState ToSet)
{
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	if (GameUserSettings)
	{
		OverallScalabilityLevelState = ToSet;
		// 列挙型変巣をInt型にcastする。
		int32 EnumToInt = static_cast<int32>(OverallScalabilityLevelState);
		// 画質を調整する。
		GameUserSettings->SetOverallScalabilityLevel(EnumToInt);
		GameUserSettings->ApplySettings(true);
    		
	}
	
}

void UGraphicPresetButtonsUI::OnLowButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Low);
	CloseMe();
	
}

void UGraphicPresetButtonsUI::OnMediumButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Medium);
	CloseMe();
	
}

void UGraphicPresetButtonsUI::OnHighButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_High);
	CloseMe();
	
}

void UGraphicPresetButtonsUI::OnUltraButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Ultra);
	CloseMe();
	
}
