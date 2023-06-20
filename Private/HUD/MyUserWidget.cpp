// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/SettingsButtonsUI.h"
#include "HUD/FadeUI.h"
#include "HUD/MainMenuButtonsUI.h"
#include "GameFramework/GameUserSettings.h"

void UMyUserWidget::GenerateMainMenuButtonsUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && UMainMenuButtonsClass)
		{
			MainMenuButtonsUI = CreateWidget<UMainMenuButtonsUI>(Controller, UMainMenuButtonsClass);
			MainMenuButtonsUI->AddToViewport();
			UUserWidget::RemoveFromParent();
			
		}
		
	}
	
}

void UMyUserWidget::GenerateSettingsButtonsUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && USettingsButtonsClass)
		{
			SettingsButtonsUI = CreateWidget<USettingsButtonsUI>(Controller, USettingsButtonsClass);
			SettingsButtonsUI->AddToViewport();
			UUserWidget::RemoveFromParent();
			
		}
		
	}
	
}

void UMyUserWidget::StartNewGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller)
		{
			// Input modeを"gameOnly"から"UIOnly"に変更する。
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(Controller);
			// 特定のLevelを開く。
			UGameplayStatics::OpenLevel(World, FName("MyDefaultMap"));
			// UIをParentから削除する。同時にスクリーンから削除される。つまり、今は表示されているUIをスクリーンから削除する。
			UUserWidget::RemoveFromParent();
			// Input modeを"game"に戻す。
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
			
		}
		
	}
	
}

void UMyUserWidget::QuitGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller)
		{
			UKismetSystemLibrary::QuitGame(World, Controller, EQuitPreference::Quit, false);
			UUserWidget::RemoveFromParent();
			
		}
		
	}
	
}

void UMyUserWidget::SwitchOverallScalabilityLevel(EOverallScalabilityLevelState ToSet)
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

void UMyUserWidget::SwitchScreenResolution(const int XCoordinate, const int YCoordinate)
{
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	if (GameUserSettings)
	{
		FIntPoint Resolution = FIntPoint(XCoordinate, YCoordinate);
		GameUserSettings->SetScreenResolution(Resolution);
		GameUserSettings->ApplyResolutionSettings(false);
		GameUserSettings->ApplySettings(true);
		
	}
	
}

void UMyUserWidget::OnRestartButtonClick()
{
	CloseUIFX();
	
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeInTimerHandle,
			this,
			&UMyUserWidget::StartNewGame,
			CloseUIDelay,
			false
			);
		
	}
	
}

void UMyUserWidget::OnSettingsButtonClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeInTimerHandle,
			this,
			&UMyUserWidget::GenerateSettingsButtonsUI,
			SwitchUIDelay,
			false
			);
		
	}
	
}

void UMyUserWidget::OnQuitButtonClick()
{
	CloseUIFX();
	
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeInTimerHandle,
			this,
			&UMyUserWidget::QuitGame,
			CloseUIDelay,
			false
			);
		
	}
	
}

void UMyUserWidget::OnLowButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Low);
	
}

void UMyUserWidget::OnMediumButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Medium);
	
}

void UMyUserWidget::OnHighButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_High);
	
}

void UMyUserWidget::OnUltraButtonClicked()
{
	SwitchOverallScalabilityLevel(EOverallScalabilityLevelState::EOSLS_Ultra);
	
}

void UMyUserWidget::OnButton1280_720Clicked()
{
	SwitchScreenResolution(1280, 720);
	
}

void UMyUserWidget::OnButton1920_1080Clicked()
{
	SwitchScreenResolution(1920, 1080);
	
}

void UMyUserWidget::OnButton2560_1440Clicked()
{
	SwitchScreenResolution(2560, 1440);
	
}

void UMyUserWidget::OnBackButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeInTimerHandle,
			this,
			&UMyUserWidget::GenerateMainMenuButtonsUI,
			SwitchUIDelay,
			false
			);
		
	}
	
}

void UMyUserWidget::CloseUIFX()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && UFadeClass)
		{
			FadeUI = CreateWidget<UFadeUI>(Controller, UFadeClass);
			FadeUI->AddToViewport();
			FadeUI->PlayFadeInAnimation();
			
		}
		
	}
	
}
