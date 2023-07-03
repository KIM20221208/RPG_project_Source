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
			// TODO: Path is hard coded, need optimize.
			FString Directory = FString("/Game/Maps/") + MapName.ToString() + ".umap";
			FSoftObjectPath ToOpenLevelPath(Directory);
			TSoftObjectPtr<UWorld> ToOpenLevel(ToOpenLevelPath);
			// 特定のLevelを開く。
			UGameplayStatics::OpenLevelBySoftObjectPtr(World, ToOpenLevel);
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
