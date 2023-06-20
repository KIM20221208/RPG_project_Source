// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "SettingsButtonsUI.generated.h"

class UButton;

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
	virtual void OnBackButtonClicked() override;

	//
	UFUNCTION()
	void OnLowButtonHovered();
	UFUNCTION()
	void OnLowButtonUnhovered();
	UFUNCTION()
	void OnMediumButtonHovered();
	UFUNCTION()
	void OnMediumButtonUnhovered();
	UFUNCTION()
	void OnHighButtonHovered();
	UFUNCTION()
	void OnHighButtonUnhovered();
	UFUNCTION()
	void OnUltraButtonHovered();
	UFUNCTION()
	void OnUltraButtonUnhovered();
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

	// Button widget: 
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* LowButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* MediumButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HighButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* UltraButtonHover;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* BackButtonHover;
	
};
