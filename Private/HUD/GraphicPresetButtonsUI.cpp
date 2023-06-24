// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GraphicPresetButtonsUI.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicPresetButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	//
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
		int32 EnumToInt = static_cast<int32>(OverallScalabilityLevelState);
		GameUserSettings->SetOverallScalabilityLevel(EnumToInt);
		GameUserSettings->ApplySettings(true);
    		
	}
	
}

void UGraphicPresetButtonsUI::CloseGraphicPresetButtonsUI()
{
	UUserWidget::RemoveFromParent();
	
}

void UGraphicPresetButtonsUI::OnLowButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Low);
	CloseGraphicPresetButtonsUI();
	
}

void UGraphicPresetButtonsUI::OnMediumButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Medium);
	CloseGraphicPresetButtonsUI();
	
}

void UGraphicPresetButtonsUI::OnHighButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_High);
	CloseGraphicPresetButtonsUI();
	
}

void UGraphicPresetButtonsUI::OnUltraButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Ultra);
	CloseGraphicPresetButtonsUI();
	
}
