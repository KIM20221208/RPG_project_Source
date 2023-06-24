// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "HUD/OverallScalabilityLevelTypes.h"
#include "GraphicPresetButtonsUI.generated.h"

class UButton;

/**
 * ゲームの画質に関するSettings Buttons。
 */

UCLASS()
class RPG_PROJECT_API UGraphicPresetButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()


protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;

	//
	void SwitchOverallScalabilityLevel(EOverallScalabilityLevelState ToSet);
	//
	void CloseGraphicPresetButtonsUI();
	
	UFUNCTION()
	void OnLowButtonClicked();
	
	UFUNCTION()
	void OnMediumButtonClicked();
	
	UFUNCTION()
	void OnHighButtonClicked();
	
	UFUNCTION()
	void OnUltraButtonClicked();
	

private:
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* LowButton;
	
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* MediumButton;
	
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* HighButton;

	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* UltraButton;

	// ゲームの画質に関するSettingsの列挙型変数、default: High。
	EOverallScalabilityLevelState OverallScalabilityLevelState = EOverallScalabilityLevelState::EOSLS_High;
	
};
