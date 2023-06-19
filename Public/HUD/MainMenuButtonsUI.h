// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "MainMenuButtonsUI.generated.h"

class UButton;

/**
 * メイン画面のブタンに関するUI
 */

UCLASS()
class RPG_PROJECT_API UMainMenuButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()

	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	virtual void OnRestartButtonClick() override;
	virtual void OnSettingsButtonClick() override;
	virtual void OnQuitButtonClick() override;

	//
	UFUNCTION()
	void OnPlayButtonHovered();
	UFUNCTION()
	void OnPlayButtonUnhovered();
	UFUNCTION()
	void OnSettingsButtonHovered();
	UFUNCTION()
	void OnSettingsButtonUnhovered();
	UFUNCTION()
	void OnQuitButtonHovered();
	UFUNCTION()
	void OnQuitButtonUnhovered();
	UFUNCTION()
	void FadeInFX();
	UFUNCTION()
	void FadeOutFX();

	//
	void DisableButtons();
	
private:
	// Button widget: プレイヤーがクリックした後、ゲームをリスタートする。
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
	
	// Button widget: プレイヤーがクリックした後、ゲームをリスタートする。
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	
	// Button widget: プレイヤーがクリックした後、ゲームをリスタートする。
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* PlayButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SettingsButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* QuitButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;
	
};
