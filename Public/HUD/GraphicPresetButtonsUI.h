// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "HUD/OverallScalabilityLevelTypes.h"
#include "GraphicPresetButtonsUI.generated.h"

/**
 * ゲームの画質に関するSetting Buttons。
 * Warning: Abandoned Now!
 */

class UButton;

UCLASS()
class RPG_PROJECT_API UGraphicPresetButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()

	
public:
	// 本UIをcloseする。画質調整ブタンを押した後callされれる。
	void CloseMe();
	

protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;

	// パラメータToSetより、ゲームの画質を調整する。
	void SwitchOverallScalabilityLevel(EOverallScalabilityLevelState ToSet);


	/**
	 * クリックイベント。
	 */
	UFUNCTION()
	void OnLowButtonClicked();
	
	UFUNCTION()
	void OnMediumButtonClicked();
	
	UFUNCTION()
	void OnHighButtonClicked();
	
	UFUNCTION()
	void OnUltraButtonClicked();
	

private:
	/** 
	 * Bind to blueprint: Clickable widgets.
	 */
	UPROPERTY(meta = (BindWidget))
	UButton* LowButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* MediumButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* HighButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* UltraButton;

	// ゲームの画質に関するSettingsの列挙型変数、default: High。
	EOverallScalabilityLevelState OverallScalabilityLevelState = EOverallScalabilityLevelState::EOSLS_High;
	
};
