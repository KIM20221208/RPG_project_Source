// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/SettingsButtonsUI.h"
#include "HUD/FadeUI.h"
#include "HUD/SettingsBackGroundUI.h"

void UMyUserWidget::GenerateSettingsUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && USettingsButtonsClass && USettingsBackGroundClass)
		{
			SettingsBackGroundUI = CreateWidget<USettingsBackGroundUI>(Controller, USettingsBackGroundClass);
			SettingsBackGroundUI->AddToViewport();
			SettingsButtonsUI = CreateWidget<USettingsButtonsUI>(Controller, USettingsButtonsClass);
			SettingsButtonsUI->AddToViewport();
			
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
			FadeInTimerHandle,
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
