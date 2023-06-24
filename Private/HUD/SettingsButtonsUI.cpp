// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SettingsButtonsUI.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "GameFramework/GameUserSettings.h"
#include "HUD/ScreenResolutionButtonsUI.h"
#include "HUD/GraphicPresetButtonsUI.h"
#include "HUD/SettingsBackGroundUI.h"

void USettingsButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	GenerateSettingsBackGroundUI();

	//
	FadeInFX();

	//
	ScreenResolutionButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnScreenResolutionButtonClicked);
	ScreenResolutionButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnScreenResolutionButtonHovered);
	ScreenResolutionButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnScreenResolutionButtonUnhovered);

	GraphicPresetButton->OnClicked.AddDynamic(this, &USettingsButtonsUI::OnGraphicPresetButtonClicked);
	GraphicPresetButton->OnHovered.AddDynamic(this, &USettingsButtonsUI::OnGraphicPresetButtonHovered);
	GraphicPresetButton->OnUnhovered.AddDynamic(this, &USettingsButtonsUI::OnGraphicPresetButtonUnhovered);

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

void USettingsButtonsUI::CloseSettingsButtonsUI()
{
	UUserWidget::RemoveFromParent();

	// Close Settings BackGround.
	if (SettingsBackGroundUI)
	{
		SettingsBackGroundUI->CloseSettingsBackGroundUI();
		
	}
	
}

void USettingsButtonsUI::GenerateScreenResolutionButtonsUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && UScreenResolutionButtonsClass)
		{
			ScreenResolutionButtonsUI = CreateWidget<UScreenResolutionButtonsUI>(Controller, UScreenResolutionButtonsClass);
			ScreenResolutionButtonsUI->AddToViewport();
			
		}
		
	}
	
}

void USettingsButtonsUI::GenerateGraphicPresetButtonsUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && UGraphicButtonsClass)
		{
			GraphicPresetButtonsUI = CreateWidget<UGraphicPresetButtonsUI>(Controller, UGraphicButtonsClass);
			GraphicPresetButtonsUI->AddToViewport();
			
		}
		
	}
	
}

void USettingsButtonsUI::OnScreenResolutionButtonClicked()
{
	GenerateScreenResolutionButtonsUI();
	
}

void USettingsButtonsUI::OnScreenResolutionButtonHovered()
{
	PlayAnimation(ScreenResolutionButtonHover);
	
}

void USettingsButtonsUI::OnScreenResolutionButtonUnhovered()
{
	PlayAnimation(ScreenResolutionButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void USettingsButtonsUI::OnGraphicPresetButtonClicked()
{
	GenerateGraphicPresetButtonsUI();
	
}

void USettingsButtonsUI::OnGraphicPresetButtonHovered()
{
	PlayAnimation(GraphicPresetButtonHover);
	
}

void USettingsButtonsUI::OnGraphicPresetButtonUnhovered()
{
	PlayAnimation(GraphicPresetButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
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
			&USettingsButtonsUI::CloseSettingsButtonsUI,
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
	//
	ScreenResolutionButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	GraphicPresetButton->SetVisibility(ESlateVisibility::HitTestInvisible);
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
