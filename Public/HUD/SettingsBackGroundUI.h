// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsBackGroundUI.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API USettingsBackGroundUI : public UUserWidget
{
	GENERATED_BODY()

	
public:
	//
	UFUNCTION()
	void CloseSettingsBackGroundUI();
	
	
protected:
	virtual void NativePreConstruct() override;
	
	//
	UFUNCTION()
	void FadeInFX();
	UFUNCTION()
	void FadeOutFx();

	
private:
	//
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;
	
};
