// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDTypes.h"
#include "GameFramework/HUD.h"
#include "RPG_projectHUD.generated.h"

class URPG_projectOverlay;
class UGameOverUI;
class UInGamePauseUI;

/**
 * P197.Default HUD of game mode
 */

UCLASS()
class RPG_PROJECT_API ARPG_projectHUD : public AHUD
{
	GENERATED_BODY()

	
public:
	// プレイヤーが死んだ後、UIをゲームオーバーUIに引き換える。
	// RPG_projectCharacterクラスのDie_Implementationメソッドからcallされる。
	void ShowGameOverUI();
	// ゲーム時のオプションUIを表示、閉じる。
	void ShowInGamePauseUI();
	void CloseInGamePauseUI();
	// プレイヤーのインゲームUIを表示する。
	void ShowRPG_projectOverlay();
	
	
	/** 
	 * Getter & Setter
	 */
	FORCEINLINE URPG_projectOverlay* GetRPG_ProjectOverlay() const { return RPG_projectOverlay; }
	FORCEINLINE EHUDState GetHUDState() const { return HUDState; }

	
protected:
	// P197.
	virtual void BeginPlay() override;

	
private:
	// P197. URPG_projectOverlayの派生クラス保存用の動的配列。
	// which is the default HUD derived from RPG_projectOverlay, i.e. WBP_RPG_projectOverlay from Editor
	UPROPERTY(EditDefaultsOnly, Category = RPG_project)
	TSubclassOf<URPG_projectOverlay> URPG_projectClass;

	// RPG_projectCharacterでセットされる。
	UPROPERTY()
	URPG_projectOverlay* RPG_projectOverlay;

	UPROPERTY(EditDefaultsOnly, Category = RPG_project)
	TSubclassOf<UGameOverUI> UGameOverClass;
	
	UPROPERTY()
	UGameOverUI* GameOverUI;

	UPROPERTY(EditDefaultsOnly, Category = RPG_project)
	TSubclassOf<UInGamePauseUI> UInGamePauseClass;
	
	UPROPERTY()
	UInGamePauseUI* InGamePauseUI;
	
	// ゲーム時、viewportに表示されているUIの判断用。default: In Gaming.
	EHUDState HUDState = EHUDState::EHS_InGaming;
	
};
