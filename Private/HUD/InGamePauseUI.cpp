// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InGamePauseUI.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UInGamePauseUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	/**
	 * ボタンのbind。
	 */
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
			// Input modeを"gameOnly"から"UIOnly"に変更する。
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
			// UIをParentから削除する。同時にスクリーンから削除される。つまり、今は表示されているUIをスクリーンから削除する。
			UUserWidget::RemoveFromParent();
			// Input modeを"game"に戻す。
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			UGameplayStatics::SetGamePaused(World, false);
			PlayerController->bShowMouseCursor = false;
			
		}
		
	}
	
}

void UInGamePauseUI::OnOptionButtonClick()
{
	// TODO: Option Menu
	
}

void UInGamePauseUI::OnBackToMainMenuButtonClick()
{
	// TODO: Back To Main Menu, && Main Menu
	
}

void UInGamePauseUI::OnQuitButtonClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
			
		}
		
	}
	
}
