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
	
	UFUNCTION()
	void OnOptionButtonClick();
	
	UFUNCTION()
	void OnBackToMainMenuButtonClick();

	
private:
	// Button widget: ゲームリスタートボタン。
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackToMainMenuButton;

	// Button widget: ゲーム終了ボタン。
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
};
