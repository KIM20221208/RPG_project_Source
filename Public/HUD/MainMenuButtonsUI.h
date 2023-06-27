// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "MainMenuButtonsUI.generated.h"

/**
 * メイン画面のブタンに関するUI
 */

class UButton;

UCLASS()
class RPG_PROJECT_API UMainMenuButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()

	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	
	/** <UMyUserWidget> */
	virtual void OnRestartButtonClick() override;
	virtual void OnQuitButtonClick() override;
	/** </UMyUserWidget> */

	
	/**
	 * UI FX.
	 */
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

	// 本UIが生成される時のFX。
	UFUNCTION()
	void FadeInFX();
	
	// 本UIがcloseされる時のFX。
	UFUNCTION()
	void FadeOutFX();

	
	// 一度ボタンを押した後、全てのボタンを押さえない様に設定する。プレイヤーが複数のボタンを早押しする事を防止。
	void DisableButtons();

	
private:
	/** 
	 * Bind to blueprint: Clickable widgets.
	 */
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	

	/** 
	 * Bind to blueprint: Widget animations.
	 */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* PlayButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SettingsButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* QuitButtonHover;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;
	
};
