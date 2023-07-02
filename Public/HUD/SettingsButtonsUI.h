// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MyUserWidget.h"
#include "SettingsButtonsUI.generated.h"

/**
 * 画面効果調整に関するUI。
 */

class UComboBoxString;
class UCheckBox;
class UButton;
class USettingsBackGroundUI;

UCLASS()
class RPG_PROJECT_API USettingsButtonsUI : public UMyUserWidget
{
	GENERATED_BODY()

	
public:
	UFUNCTION()
	void OnBackButtonClicked();

	
protected:
	// equal to BeginPlay Function
	virtual void NativePreConstruct() override;
	void SetScreenResolutionComboBoxStringSelectedOption();
	FString IntOverallScalabilityLevelToString(int32 OverallScalabilityLevel);
	void SetGraphicPresetComboBoxStringSelectedOption();
	void SetFullScreenCheckBoxCheckedState();
	// 一度ボタンを押した後、全てのボタンを押さえない様に設定する。プレイヤーが複数のボタンを早押しする事を防止。
	void DisableButtons();
	// 本UIをcloseする。
	void CloseMe();
	// X:Yより、画面解像度を調整する。
	void SwitchScreenResolution(const int X, const int Y);
	// パラメータToSetより、ゲームの画質を調整する。
	void SwitchOverallScalabilityLevel(int32 ScalabilityLevel);
	
	/**
	 * Generate && Close UI.
	 */
	void GenerateSettingsBackGroundUI();

	
	/**
	 * クリックイベント。
	 */
	UFUNCTION()
	void OnScreenResolutionComboBoxStringSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnGraphicPresetComboBoxStringSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	UFUNCTION()
	void OnFullScreenCheckBoxStateChanged(bool bChange);
	
	
	/**
	 * UI FX.
	 */
	UFUNCTION()
	void OnBackButtonHovered();
	
	UFUNCTION()
	void OnBackButtonUnhovered();
	
	// 本UIが生成される時のFX。
	UFUNCTION()
	void FadeInFX();

	// 本UIがcloseされる時のFX。
	UFUNCTION()
	void FadeOutFX();

	
	// 画像解析度：X軸。
	int XCoordinate;
	// 画像解析度：Y軸。
	int YCoordinate;
	
	
private:
	//　SettingのBackground UI、エディタから代入される。
	UPROPERTY(EditAnywhere, Category=SettingsMenuToOpenUI)
	TSubclassOf<USettingsBackGroundUI> USettingsBackGroundClass;
	
	UPROPERTY()
	USettingsBackGroundUI* SettingsBackGroundUI;
	
	
	/** 
	 * Bind to blueprint: Clickable widgets.
	 */
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ScreenResolutionComboBoxString;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* GraphicPresetComboBoxString;
	
	UPROPERTY(meta = (BindWidget))
	UCheckBox* FullScreenCheckBox;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;


	/** 
	 * Bind to blueprint: Widget animations.
	 */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* BackButtonHover;

	
	// Timer設定に関する構造体、World->GetTimerManager().SetTimerメソッドのパラメータとして使われる。
	FTimerHandle FadeTimerHandle;
	
};
