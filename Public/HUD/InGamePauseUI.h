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
	/** <UMyUserWidget> */
	// オプションUIからゲームに戻る。
	UFUNCTION()
	virtual void OnResumeButtonClick();
	/** </UMyUserWidget> */
	
	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	// UIモードからゲームモードに戻る。
	void BackToGame();
	// 一度ボタンを押した後、全てのボタンを押さえない様に設定する。プレイヤーが複数のボタンを早押しする事を防止。
	void DisableButtons();


	/**
	 * クリックイベント。
	 */
	/** <UMyUserWidget> */
	virtual void OnRestartButtonClick() override;
	void BackToMainMenu();
	virtual void OnQuitButtonClick() override;
	/** </UMyUserWidget> */
	
	UFUNCTION()
	void OnBackToMainMenuButtonClick();

	
	/**
	 * UI FX.
	 */
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
	void FadeInFX();

	UFUNCTION()
	void FadeOutFX();

	
private:
	/** 
	 * Bind to blueprint: Clickable widgets.
	 */
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SettingButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackToMainMenuButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	
	/** 
	 * Bind to blueprint: Widget animations.
	 */
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


	// Timer設定に関する構造体、World->GetTimerManager().SetTimerメソッドのパラメータとして使われる。
	FTimerHandle FadeTimerHandle;
	
};
