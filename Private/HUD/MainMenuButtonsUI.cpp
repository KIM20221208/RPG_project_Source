// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuButtonsUI.h"
#include "Components/Button.h"

void UMainMenuButtonsUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	// 本UIが生成される時のFX。
	FadeInFX();
	
	// イベントのバインド:
	PlayButton->OnClicked.AddDynamic(this, &UMainMenuButtonsUI::OnRestartButtonClick);
	PlayButton->OnHovered.AddDynamic(this, &UMainMenuButtonsUI::OnPlayButtonHovered);
	PlayButton->OnUnhovered.AddDynamic(this, &UMainMenuButtonsUI::OnPlayButtonUnhovered);
	
	SettingsButton->OnClicked.AddDynamic(this, &UMainMenuButtonsUI::OnSettingsButtonClick);
	SettingsButton->OnHovered.AddDynamic(this, &UMainMenuButtonsUI::OnSettingsButtonHovered);
	SettingsButton->OnUnhovered.AddDynamic(this, &UMainMenuButtonsUI::OnSettingsButtonUnhovered);
	
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuButtonsUI::OnQuitButtonClick);
	QuitButton->OnHovered.AddDynamic(this, &UMainMenuButtonsUI::OnQuitButtonHovered);
	QuitButton->OnUnhovered.AddDynamic(this, &UMainMenuButtonsUI::OnQuitButtonUnhovered);
	
}

void UMainMenuButtonsUI::OnRestartButtonClick()
{
	DisableButtons();
	Super::OnRestartButtonClick();
	
}

void UMainMenuButtonsUI::OnQuitButtonClick()
{
	DisableButtons();
	Super::OnQuitButtonClick();
	
}

void UMainMenuButtonsUI::OnPlayButtonHovered()
{
	PlayAnimation(PlayButtonHover);
	
}

void UMainMenuButtonsUI::OnPlayButtonUnhovered()
{
	PlayAnimation(PlayButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UMainMenuButtonsUI::OnSettingsButtonHovered()
{
	PlayAnimation(SettingsButtonHover);
	
}

void UMainMenuButtonsUI::OnSettingsButtonUnhovered()
{
	PlayAnimation(SettingsButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UMainMenuButtonsUI::OnQuitButtonHovered()
{
	PlayAnimation(QuitButtonHover);
	
}

void UMainMenuButtonsUI::OnQuitButtonUnhovered()
{
	PlayAnimation(QuitButtonHover, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UMainMenuButtonsUI::FadeInFX()
{
	PlayAnimation(FadeIn, 0, 1, EUMGSequencePlayMode::Reverse);
	
}

void UMainMenuButtonsUI::FadeOutFX()
{
	PlayAnimation(FadeIn);
	
}

void UMainMenuButtonsUI::DisableButtons()
{
	// ユーザーがボタンを押した後、全部のボタンの"OnClick"イベントを閉じる。
	PlayButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	SettingsButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	QuitButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	
}
