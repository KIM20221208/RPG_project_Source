// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsBackGroundUI.generated.h"

/**
 * SettingのBackground UI。
 */

UCLASS()
class RPG_PROJECT_API USettingsBackGroundUI : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UFUNCTION()
	void CloseMe();

	
	/**
	 * UI FX.
	 */
	UFUNCTION()
	void FadeOutFX();

	
protected:
	virtual void NativePreConstruct() override;

	
	/**
	 * UI FX.
	 */
	UFUNCTION()
	void FadeInFX();
	

private:
	/** 
	 * Bind to blueprint: Widget animations.
	 */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;
	
};
