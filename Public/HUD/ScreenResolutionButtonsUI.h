// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "ScreenResolutionButtonsUI.generated.h"

/**
 * 画面解像度の調整に関するSettings Buttons。
 * Warning: Abandoned Now!
 */

class UButton;

UCLASS()
class RPG_PROJECT_API UScreenResolutionButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()

public:
	// 本UIをcloseする。解像度調整ブタンを押した後callされれる。
	UFUNCTION()
	void CloseMe();


protected:
	virtual void NativePreConstruct() override;
	
	// X:Yより、画面解像度を調整する。
	void SwitchScreenResolution(const int X, const int Y);

	
	/**
	 * クリックイベント。
	 */
	UFUNCTION()
	void OnButton1280_720Clicked();
	
	UFUNCTION()
	void OnButton1920_1080Clicked();
	
	UFUNCTION()
	void OnButton2560_1440Clicked();


private:
	/** 
	 * Bind to blueprint: Clickable widgets.
	 */
	UPROPERTY(meta=(BindWidget))
	UButton* Button1280_720;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button1920_1080;

	UPROPERTY(meta=(BindWidget))
	UButton* Button2560_1440;
	
};
