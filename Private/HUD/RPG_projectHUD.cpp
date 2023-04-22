// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RPG_projectHUD.h"
#include "HUD/RPG_projectOverlay.h"
#include "HUD/GameOverUI.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/UserWidget.h"

void ARPG_projectHUD::GameOver()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// Before add game over UI, remove RPG_projectOverlay
		UWidgetLayoutLibrary::RemoveAllWidgets(World);
		// Add game over UI into the viewport
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && UGameOverClass)
		{
			GameOverUI = CreateWidget<UGameOverUI>(Controller, UGameOverClass);
			GameOverUI->AddToViewport();
			// Show Mouse cursor after player dead
			Controller->bShowMouseCursor = true;
			// Change HUD state to "Game Over"
			HUDState = EHUDState::EHS_GameOver;
			
		}
	}
}

void ARPG_projectHUD::BeginPlay()
{
	Super::BeginPlay();
	// P197.
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && URPG_projectClass)
		{
			// P197.Create URPG_projectOverlay via template function
			RPG_projectOverlay = CreateWidget<URPG_projectOverlay>(Controller, URPG_projectClass);
			RPG_projectOverlay->AddToViewport();
			
		}
	}
	
}
