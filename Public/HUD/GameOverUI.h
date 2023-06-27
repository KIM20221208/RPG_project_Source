// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "GameOverUI.generated.h"

class UButton;

/**
 * プレイヤーが死んだ後に表すUI。
 */

UCLASS()
class RPG_PROJECT_API UGameOverUI : public UMyUserWidget
{
	GENERATED_BODY()

	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	
	
private:
	/** 
	 * Bind to blueprint: Button widgets.
	 */
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	
};
