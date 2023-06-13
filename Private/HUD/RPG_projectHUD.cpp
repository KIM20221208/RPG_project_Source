// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RPG_projectHUD.h"
#include "HUD/RPG_projectOverlay.h"
#include "HUD/GameOverUI.h"
#include "HUD/InGamePauseUI.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ARPG_projectHUD::ShowGameOverUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// ゲームオーバーUIを開く前、RPG_projectOverlayを先ずcloseする。
		UWidgetLayoutLibrary::RemoveAllWidgets(World);
		// ViewportにゲームオーバーUIを開く。
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && UGameOverClass)
		{
			GameOverUI = CreateWidget<UGameOverUI>(Controller, UGameOverClass);
			GameOverUI->AddToViewport();
			// マウスのコントロールを許可する。
			Controller->bShowMouseCursor = true;
			// HUD stateを"Game Over"に設定する。
			HUDState = EHUDState::EHS_GameOver;
			
		}
		
	}
	
}

void ARPG_projectHUD::ShowInGamePauseUI()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// ViewportにオプションUIを開く。
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && UInGamePauseClass)
		{
			InGamePauseUI = CreateWidget<UInGamePauseUI>(Controller, UInGamePauseClass);
			InGamePauseUI->AddToViewport();
			// マウスのコントロールを許可する。
			Controller->bShowMouseCursor = true;
			// オプションUIの時、ゲームを一時停止する。
			UGameplayStatics::SetGamePaused(World, true);
			// // HUD stateを"In Game Pause"に設定する。
			HUDState = EHUDState::EHS_InGamePause;
			
		}
		
	}
	
}

void ARPG_projectHUD::CloseInGamePauseUI()
{
	InGamePauseUI->OnResumeButtonClick();
	HUDState = EHUDState::EHS_InGaming;
	
}

void ARPG_projectHUD::ShowRPG_projectOverlay()
{
	// P197
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && URPG_projectClass)
		{
			// P197.template functionでURPG_projectOverlayを生成する。 
			RPG_projectOverlay = CreateWidget<URPG_projectOverlay>(Controller, URPG_projectClass);
			RPG_projectOverlay->AddToViewport();
			Controller->bShowMouseCursor = false;
			HUDState = EHUDState::EHS_InGaming;
			
		}
		
	}
	
}

void ARPG_projectHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ShowRPG_projectOverlay();
	
}
