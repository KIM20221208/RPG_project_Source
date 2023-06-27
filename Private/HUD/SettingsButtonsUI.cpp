// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SettingsButtonsUI.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "HUD/SettingsBackGroundUI.h"

void USettingsButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	GenerateSettingsBackGroundUI();

	//本UIが生成される時のFX。
	FadeInFX();

	// イベントのバインド:
	ScreenResolutionComboBoxString->OnSelectionChanged.AddDynamic(this, &USettingsButtonsUI::OnScreenResolutionComboBoxStringSelectionChanged);

	GraphicPresetComboBoxString->OnSelectionChanged.AddDynamic(this, &USettingsButtonsUI::OnGraphicPresetComboBoxStringSelectionChanged);
	
	FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsButtonsUI::OnFullScreenCheckBoxStateChanged);
	
	BackButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnBackButtonClicked);
	BackButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnBackButtonHovered);
	BackButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnBackButtonUnhovered);
	
}

void USettingsButtonsUI::GenerateSettingsBackGroundUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && USettingsBackGroundClass)
		{
			SettingsBackGroundUI = CreateWidget<USettingsBackGroundUI>(Controller, USettingsBackGroundClass);
			SettingsBackGroundUI->AddToViewport();
			
		}
		
	}
	
}

void USettingsButtonsUI::CloseMe()
{
	UUserWidget::RemoveFromParent();

	// Close all related UI.
	if (SettingsBackGroundUI)
	{
		SettingsBackGroundUI->CloseMe();
		
	}
	
}

void USettingsButtonsUI::SwitchScreenResolution(const int X, const int Y)
{
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	if (GameUserSettings)
	{
		FIntPoint Resolution = FIntPoint(X, Y);
		GameUserSettings->SetScreenResolution(Resolution);
		GameUserSettings->ApplyResolutionSettings(false);
		GameUserSettings->ApplySettings(true);
		
	}
	
}

void USettingsButtonsUI::SwitchOverallScalabilityLevel(int32 ScalabilityLevel)
{
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	if (GameUserSettings)
	{
		// 画質を調整する。
		GameUserSettings->SetOverallScalabilityLevel(ScalabilityLevel);
		GameUserSettings->ApplySettings(true);
    		
	}
	
}

void USettingsButtonsUI::OnFullScreenCheckBoxStateChanged(bool bChange)
{
	
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	if (GameUserSettings)
	{
		// If Check Box is checked.
		if(bChange)
		{
			GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
			
		}
		else
		{
			GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
			
		}
		GameUserSettings->ApplySettings(true);
		
	}
	
}

void USettingsButtonsUI::OnScreenResolutionComboBoxStringSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	
	FString LeftString;
	FString RightString;
	// ComboBoxStringSelectionのStringから画像解析度をgetする。
	SelectedItem.Split("*", &LeftString, &RightString);

	// FStringをint型に変換する。
	XCoordinate = FCString::Atoi(*LeftString);
	YCoordinate = FCString::Atoi(*RightString);
	// 画像解析度をsetする。
	SwitchScreenResolution(XCoordinate, YCoordinate);
	
}

void USettingsButtonsUI::OnGraphicPresetComboBoxStringSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	int32 SelectedIndex = GraphicPresetComboBoxString->FindOptionIndex(SelectedItem);
	SwitchOverallScalabilityLevel(SelectedIndex);
	
}

void USettingsButtonsUI::OnBackButtonClicked()
{
	DisableButtons();
	FadeOutFX();
	SettingsBackGroundUI->FadeOutFX(); 
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeTimerHandle,
			this,
			&USettingsButtonsUI::CloseMe,
			CloseUIDelay,
			false
			);
		
	}
	
}

void USettingsButtonsUI::OnBackButtonHovered()
{
	PlayAnimation(BackButtonHover);
	
}

void USettingsButtonsUI::OnBackButtonUnhovered()
{
	PlayAnimation(BackButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::DisableButtons()
{
	
	FullScreenCheckBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	BackButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	
}

void USettingsButtonsUI::FadeInFX()
{
	PlayAnimation(FadeIn);
	
}

void USettingsButtonsUI::FadeOutFX()
{
	PlayAnimation(FadeIn, 0, 1, EUMGSequencePlayMode::Reverse);
	
}
