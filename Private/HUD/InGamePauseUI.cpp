// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InGamePauseUI.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/RPG_projectCharacter.h"
#include "HUD/SettingsButtonsUI.h"
#include "Kismet/GameplayStatics.h"

void UInGamePauseUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	//本UIが生成される時のFX。
	FadeInFX();
	
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

void UInGamePauseUI::BackToGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller)
		{
			ARPG_projectCharacter* RPG_ProjectCharacter = Cast<ARPG_projectCharacter>(Controller->GetCharacter());
			if (RPG_ProjectCharacter)
			{
				// ゲームモードに戻る時、プレイヤーが操作しているキャラのActionStateを"Unoccupied"に調整する。
				RPG_ProjectCharacter->SetActionState(EActionState::EAS_Unoccupied);
				
			}
			// Input modeを"game"に戻す。
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
			Controller->bShowMouseCursor = false;
			UGameplayStatics::SetGamePaused(World, false);
			// UIをParentから削除する。同時にスクリーンから削除される。つまり、今は表示されているUIをスクリーンから削除する。
			UUserWidget::RemoveFromParent();
			// Close all UI related to settings UI.
			CloseSettingsButtongsUI();
			
		}
		
	}
	
}

void UInGamePauseUI::DisableButtons()
{
	ResumeButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	RestartButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	SettingButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	BackToMainMenuButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	QuitButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	
}

void UInGamePauseUI::OnResumeButtonClick()
{
	DisableButtons();
	FadeOutFX();
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeTimerHandle,
			this,
			&UInGamePauseUI::BackToGame,
			SwitchUIDelay,
			false
			);
		
	}
	
}

void UInGamePauseUI::OnRestartButtonClick()
{
	DisableButtons();
	Super::OnRestartButtonClick();
	
}

void UInGamePauseUI::BackToMainMenu()
{
	OpenMapByName(MainMenuMap);
	
}

void UInGamePauseUI::OnBackToMainMenuButtonClick()
{
	DisableButtons();
	CloseUIFX();
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			FadeTimerHandle,
			this,
			&UInGamePauseUI::BackToMainMenu,
			CloseUIDelay,
			false
			);
		
	}
	
}

void UInGamePauseUI::OnQuitButtonClick()
{
	DisableButtons();
	Super::OnQuitButtonClick();
	
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

void UInGamePauseUI::FadeInFX()
{
	PlayAnimation(FadeIn);
	
}

void UInGamePauseUI::FadeOutFX()
{
	PlayAnimation(FadeIn, 0, 1, EUMGSequencePlayMode::Reverse);
	
}
