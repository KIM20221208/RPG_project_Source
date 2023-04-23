// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InGamePauseUI.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UInGamePauseUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnResumeButtonClick);
	RestartButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnRestartButtonClick);
	OptionButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnOptionButtonClick);
	BackToMainMenuButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnBackToMainMenuButtonClick);
	QuitButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnQuitButtonClick);
	
}

void UInGamePauseUI::OnResumeButtonClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			// set input mode from "gameOnly" to "UIOnly"
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
			// Remove widget from it's parent, also be removed if bounded with screen 
			UUserWidget::RemoveFromParent();
			// set back input mode to "game"
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			PlayerController->bShowMouseCursor = false;
			UGameplayStatics::SetGamePaused(World, false);
		}
	}
}

void UInGamePauseUI::OnRestartButtonClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			// set input mode from "gameOnly" to "UIOnly"
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
			// Open a certain level 
			UGameplayStatics::OpenLevel(World, FName("Minimal_Default"));
			// Remove widget from it's parent, also be removed if bounded with screen 
			UUserWidget::RemoveFromParent();
			// set back input mode to "game"
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			
		}
	}
	
}

void UInGamePauseUI::OnOptionButtonClick()
{
	
}

void UInGamePauseUI::OnBackToMainMenuButtonClick()
{
	
}

void UInGamePauseUI::OnQuitButtonClick()
{
	
}