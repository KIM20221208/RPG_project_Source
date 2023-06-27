// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/SettingsButtonsUI.h"
#include "HUD/FadeUI.h"


void UMyUserWidget::OpenMapByName(FName MapName)
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller)
		{
			// 特定のLevelを開く。
			UGameplayStatics::OpenLevel(World, MapName);
			// UIをParentから削除する。同時にスクリーンから削除される。つまり、今は表示されているUIをスクリーンから削除する。
			UUserWidget::RemoveFromParent();
			// Input modeを"game"に戻す。
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
			
		}
		
	}
}

void UMyUserWidget::StartNewGame()
{
	OpenMapByName(NewGameMap);
	
}

void UMyUserWidget::GenerateSettingsUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && USettingsButtonsClass)
		{
			SettingsButtonsUI = CreateWidget<USettingsButtonsUI>(Controller, USettingsButtonsClass);
			SettingsButtonsUI->AddToViewport();
			
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

void UMyUserWidget::CloseSettingsButtongsUI()
{
	if (SettingsButtonsUI)
	{
		// Close all UI related to Settings Buttons UI, Close Settings Buttons UI: Delay version.
		SettingsButtonsUI->OnBackButtonClicked();
		
	}
	
}

void UMyUserWidget::OnRestartButtonClick()
{
	CloseUIFX();
	
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeTimerHandle,
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
			FadeTimerHandle,
			this,
			&UMyUserWidget::GenerateSettingsUI,
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
			FadeTimerHandle,
			this,
			&UMyUserWidget::QuitGame,
			CloseUIDelay,
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
