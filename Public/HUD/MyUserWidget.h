// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingsBackGroundUI.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

class UFadeUI;
class USettingsButtonsUI;
class UMainMenuButtonsUI;
class USettingsBackGroundUI;

/**
 * Parent class of all Widget of this game
 */

UCLASS()
class RPG_PROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	//
	UPROPERTY()
	USettingsBackGroundUI* SettingsBackGroundUI;
	
	
protected:
	//
	void GenerateSettingsUI();
	//
	UFUNCTION()
	void CloseSettingsBackGround() { SettingsBackGroundUI->CloseSettingsBackGroundUI(); }
	//
	void StartNewGame();
	//
	void QuitGame();
	
	// ゲームをリスタートする。
	UFUNCTION()
	virtual void OnRestartButtonClick();

	// 画面効果調整に関するUIを開く。
	UFUNCTION()
	virtual void OnSettingsButtonClick();

	// ゲームを終了する。
	UFUNCTION()
	virtual void OnQuitButtonClick();

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
	UPROPERTY(EditAnywhere, Category=MainMenuToOpenUI)
	TSubclassOf<UFadeUI> UFadeClass;

	//
	UPROPERTY()
	UFadeUI* FadeUI;

	// 
	UPROPERTY(EditAnywhere, Category=MainMenuToOpenUI)
	TSubclassOf<USettingsButtonsUI> USettingsButtonsClass;
	
	//
	UPROPERTY()
	USettingsButtonsUI* SettingsButtonsUI;

	//
	UPROPERTY(EditAnywhere, Category=MainMenuToOpenUI)
	TSubclassOf<USettingsBackGroundUI> USettingsBackGroundClass;

	//
	FTimerHandle FadeInTimerHandle;
	
};
