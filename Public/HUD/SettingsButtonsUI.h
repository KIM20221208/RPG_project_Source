// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "SettingsButtonsUI.generated.h"

class UCheckBox;
class UButton;
class UScreenResolutionButtonsUI;
class UGraphicPresetButtonsUI;

/**
 * 画面効果調整に関するUI。
 */

UCLASS()
class RPG_PROJECT_API USettingsButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()


protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;

	//
	void GenerateScreenResolutionButtonsUI();
	void GenerateGraphicPresetButtonsUI();
	void CloseSettingsButtonsUI();
	
	//
	UFUNCTION()
	void OnScreenResolutionButtonClicked();
	UFUNCTION()
	void OnScreenResolutionButtonHovered();
	UFUNCTION()
	void OnScreenResolutionButtonUnhovered();
	UFUNCTION()
	void OnGraphicPresetButtonClicked();
	UFUNCTION()
	void OnGraphicPresetButtonHovered();
	UFUNCTION()
	void OnGraphicPresetButtonUnhovered();
	UFUNCTION()
	void OnFullScreenCheckBoxStateChanged(bool bChange);
	UFUNCTION()
	virtual void OnBackButtonClicked();
	UFUNCTION()
	void OnBackButtonHovered();
	UFUNCTION()
	void OnBackButtonUnhovered();
	UFUNCTION()
	void FadeInFX();
	UFUNCTION()
	void FadeOutFX();
	
	//
	void DisableButtons();
	
	
private:
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* ScreenResolutionButton;
	
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* GraphicPresetButton;
	
	// CheckBox widget: 
	UPROPERTY(meta = (BindWidget))
	UCheckBox* FullScreenCheckBox;
	
	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ScreenResolutionButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* GraphicPresetButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* BackButtonHover;

	
	//
	UPROPERTY(EditAnywhere, Category=SettingsMenuToOpenUI)
	TSubclassOf<UScreenResolutionButtonsUI> UScreenResolutionButtonsClass;
	
	//
	UPROPERTY()
	UScreenResolutionButtonsUI* ScreenResolutionButtonsUI;

	//
	UPROPERTY(EditAnywhere, Category=SettingsMenuToOpenUI)
	TSubclassOf<UGraphicPresetButtonsUI> UGraphicButtonsClass;

	//
	UPROPERTY()
	UGraphicPresetButtonsUI* GraphicPresetButtonsUI;

	
	//
	FTimerHandle FadeInTimerHandle;
	
};
