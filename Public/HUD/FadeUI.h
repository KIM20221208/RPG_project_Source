// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeUI.generated.h"

/**
 * UIが閉じる時、UIが閉じるFXに関するUI。
 */

UCLASS()
class RPG_PROJECT_API UFadeUI : public UUserWidget
{
	GENERATED_BODY()

	
public:
	void PlayFadeInAnimation();

	
private:
	// UIが閉じる時、UIが閉じるFX：黒いスクリーンの fade in FX。
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* fadeIn;
	
};
