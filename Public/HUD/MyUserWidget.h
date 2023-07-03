// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * Parent class of all Widget of this game
 */

class UFadeUI;
class USettingsButtonsUI;
class UMainMenuButtonsUI;

UCLASS()
class RPG_PROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	void OpenMapByName(FName MapName);
	// ゲームを最初から開始する。
	void StartNewGame();
	// Setting UIを生成する。
	void GenerateSettingsUI();
	// ゲームを終了する。
	void QuitGame();
	// Close all UI related to settings UI.
	void CloseSettingsButtongsUI();

	// 設定したTimer後、StartNewGameメソッドをcallする。
	UFUNCTION()
	virtual void OnRestartButtonClick();

	// 設定したTimer後、GenerateSettingsUIメソッドをcallする。
	UFUNCTION()
	virtual void OnSettingsButtonClick();

	// 設定したTimer後、QuitGameメソッドをcallする。
	UFUNCTION()
	virtual void OnQuitButtonClick();

	// UIが切り替える時のFX。
	UFUNCTION()
	void CloseUIFX();

	// 現存のUIが別のUIに切り替える時、切替FXのプレイ為の遅延、エディタで修正可能。
	UPROPERTY(EditAnywhere, Category=Delay)
	float SwitchUIDelay = 0.2;

	// UIが閉じる時、UIが閉じるFXのプレイ為の遅延、エディタで修正可能。
	UPROPERTY(EditAnywhere, Category=Delay)
	float CloseUIDelay = 0.5;

	UPROPERTY(EditAnywhere, Category=OpenMapName)
	FName NewGameMap = FName("MyDefaultMap");

	UPROPERTY(EditAnywhere, Category=OpenMapName)
	FName MainMenuMap = FName("TestMap");

	
private:
	// UIが閉じる時のFX UI、エディタから代入される。
	UPROPERTY(EditAnywhere, Category=MainMenuToOpenUI)
	TSubclassOf<UFadeUI> UFadeClass;
	
	UPROPERTY()
	UFadeUI* FadeUI;

	// Setting UIのボタンUI、エディタから代入される。
	UPROPERTY(EditAnywhere, Category=MainMenuToOpenUI)
	TSubclassOf<USettingsButtonsUI> USettingsButtonsClass;
	
	UPROPERTY()
	USettingsButtonsUI* SettingsButtonsUI;
	
	// Timer設定に関する構造体、World->GetTimerManager().SetTimerメソッドのパラメータとして使われる。
	FTimerHandle FadeTimerHandle;
	
};
