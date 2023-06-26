// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "InGamePauseUI.generated.h"

class UButton;

/**
 * ゲーム中"F10"を押した後に表示されるオプションUI。
 */

UCLASS()
class RPG_PROJECT_API UInGamePauseUI : public UMyUserWidget
{
	GENERATED_BODY()

	
public:
	// オプションUIからゲームに戻る。
	UFUNCTION()
	virtual void OnResumeButtonClick();

	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	virtual void OnRestartButtonClick() override;
	virtual void OnQuitButtonClick() override;

	UFUNCTION()
	void OnResumeButtonHovered();

	UFUNCTION()
	void OnResumeButtonUnhovered();

	UFUNCTION()
	void OnRestartButtonHovered();

	UFUNCTION()
	void OnRestartButtonUnhovered();

	UFUNCTION()
	void OnSettingButtonHovered();

	UFUNCTION()
	void OnSettingButtonUnhovered();

	UFUNCTION()
	void OnBackToMainMenuButtonHovered();

	UFUNCTION()
	void OnBackToMainMenuButtonUnhovered();

	UFUNCTION()
	void OnQuitButtonHovered();

	UFUNCTION()
	void OnQuitButtonUnhovered();
	
	UFUNCTION()
	void OnBackToMainMenuButtonClick();
	
	void BackToGame();
	void DisableButtons();

	
private:
	// Button widget: ゲームリスタートボタン。
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SettingButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackToMainMenuButton;

	// Button widget: ゲーム終了ボタン。
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ResumeButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* RestartButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SettingButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* BackToMainMenuButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* QuitButtonHover;
	
};
