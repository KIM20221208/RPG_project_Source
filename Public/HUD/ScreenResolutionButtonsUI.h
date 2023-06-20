// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "ScreenResolutionButtonsUI.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class RPG_PROJECT_API UScreenResolutionButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativePreConstruct() override;


private:
	UPROPERTY(meta=(BindWidget))
	UButton* Button1280_720;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button1920_1080;

	UPROPERTY(meta=(BindWidget))
	UButton* Button2560_1440;
	
};
