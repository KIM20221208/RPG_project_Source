// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/OverallScalabilityLevelTypes.h"
#include "MyUserWidget.generated.h"

class UFadeUI;
class USettingsButtonsUI;
class UMainMenuButtonsUI;


/**
 * Parent class of all Widget of this game
 */

UCLASS()
class RPG_PROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

	
protected:
	//
	void GenerateMainMenuButtonsUI();
	void GenerateSettingsButtonsUI();
	
	//
	void StartNewGame();
	//
	void QuitGame();
	//
	void SwitchOverallScalabilityLevel(EOverallScalabilityLevelState ToSet);
	
	// ゲームをリスタートする。
	UFUNCTION()
	virtual void OnRestartButtonClick();

	// 画面効果調整に関するUIを開く。
	UFUNCTION()
	virtual void OnSettingsButtonClick();

	// ゲームを終了する。
	UFUNCTION()
	virtual void OnQuitButtonClick();
	
	//
	UFUNCTION()
	void OnLowButtonClicked();

	//
	UFUNCTION()
	void OnMediumButtonClicked();

	//
	UFUNCTION()
	void OnHighButtonClicked();

	//
	UFUNCTION()
	void OnUltraButtonClicked();
	
	//
	UFUNCTION()
	virtual void OnBackButtonClicked();

	//　UIが切り替える時の動画。
	UFUNCTION()
	void CloseUIFX();

	//
	UPROPERTY(EditAnywhere, Category=ToOpenUI)
	float SwitchUIDelay = 0.2;

	//
	UPROPERTY(EditAnywhere, Category=ToOpenUI)
	float CloseUIDelay = 0.5;

	
private:
	// 
	UPROPERTY(EditAnywhere, Category=ToOpenUI)
	TSubclassOf<UFadeUI> UFadeClass;

	//
	UPROPERTY()
	UFadeUI* FadeUI;

	// 
	UPROPERTY(EditAnywhere, Category=ToOpenUI)
	TSubclassOf<USettingsButtonsUI> USettingsButtonsClass;
	
	//
	UPROPERTY()
	USettingsButtonsUI* SettingsButtonsUI;

	// 
	UPROPERTY(EditAnywhere, Category=ToOpenUI)
	TSubclassOf<UMainMenuButtonsUI> UMainMenuButtonsClass;

	//
	UPROPERTY()
	UMainMenuButtonsUI* MainMenuButtonsUI;

	//
	FTimerHandle FadeInTimerHandle;

	// ゲームの画質に関するSettingsの列挙型変数、default: High。
	EOverallScalabilityLevelState OverallScalabilityLevelState = EOverallScalabilityLevelState::EOSLS_High;
	
};
