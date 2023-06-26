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
	ResumeButton->OnHovered.AddDynamic(this, &UInGamePauseUI::OnResumeButtonHovered);
	ResumeButton->OnUnhovered.AddDynamic(this, &UInGamePauseUI::OnResumeButtonUnhovered);
	
	RestartButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnRestartButtonClick);
	RestartButton->OnHovered.AddDynamic(this, &UInGamePauseUI::OnRestartButtonHovered);
	RestartButton->OnUnhovered.AddDynamic(this, &UInGamePauseUI::OnRestartButtonUnhovered);
	
	SettingButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnSettingsButtonClick);
	SettingButton->OnHovered.AddDynamic(this, &UInGamePauseUI::OnSettingButtonHovered);
	SettingButton->OnUnhovered.AddDynamic(this, &UInGamePauseUI::OnSettingButtonUnhovered);
	
	BackToMainMenuButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnBackToMainMenuButtonClick);
	BackToMainMenuButton->OnHovered.AddDynamic(this, &UInGamePauseUI::OnBackToMainMenuButtonHovered);
	BackToMainMenuButton->OnUnhovered.AddDynamic(this, &UInGamePauseUI::OnBackToMainMenuButtonUnhovered);
	
	QuitButton->OnClicked.AddDynamic(this, &UInGamePauseUI::OnQuitButtonClick);
	QuitButton->OnHovered.AddDynamic(this, &UInGamePauseUI::OnQuitButtonHovered);
	QuitButton->OnUnhovered.AddDynamic(this, &UInGamePauseUI::OnQuitButtonUnhovered);
	
}

void UInGamePauseUI::OnResumeButtonClick()
{
	DisableButtons();
	BackToGame();
	
}

void UInGamePauseUI::OnRestartButtonClick()
{
	DisableButtons();
	StartNewGame();
	
}

void UInGamePauseUI::OnQuitButtonClick()
{
	DisableButtons();
	QuitGame();
	
}

void UInGamePauseUI::OnResumeButtonHovered()
{
	PlayAnimation(ResumeButtonHover);
	
}

void UInGamePauseUI::OnResumeButtonUnhovered()
{
	PlayAnimation(ResumeButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UInGamePauseUI::OnRestartButtonHovered()
{
	PlayAnimation(RestartButtonHover);
	
}

void UInGamePauseUI::OnRestartButtonUnhovered()
{
	PlayAnimation(RestartButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UInGamePauseUI::OnSettingButtonHovered()
{
	PlayAnimation(SettingButtonHover);
	
}

void UInGamePauseUI::OnSettingButtonUnhovered()
{
	PlayAnimation(SettingButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UInGamePauseUI::OnBackToMainMenuButtonHovered()
{
	PlayAnimation(BackToMainMenuButtonHover);
	
}

void UInGamePauseUI::OnBackToMainMenuButtonUnhovered()
{
	PlayAnimation(BackToMainMenuButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UInGamePauseUI::OnQuitButtonHovered()
{
	PlayAnimation(QuitButtonHover);
	
}

void UInGamePauseUI::OnQuitButtonUnhovered()
{
	PlayAnimation(QuitButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UInGamePauseUI::BackToGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller)
		{
			// Input modeを"game"に戻す。
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
			Controller->bShowMouseCursor = false;
			UGameplayStatics::SetGamePaused(World, false);
			// UIをParentから削除する。同時にスクリーンから削除される。つまり、今は表示されているUIをスクリーンから削除する。
			UUserWidget::RemoveFromParent();
			
		}
		
	}
	
}

void UInGamePauseUI::OnBackToMainMenuButtonClick()
{
	// TODO: Back To Main Menu, && Main Menu
	
}

void UInGamePauseUI::DisableButtons()
{
	ResumeButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	RestartButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	SettingButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	BackToMainMenuButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	QuitButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	
}
