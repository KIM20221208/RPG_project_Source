// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDTypes.h"
#include "GameFramework/HUD.h"
#include "RPG_projectHUD.generated.h"

class URPG_projectOverlay;
class UGameOverUI;

/**
 * P197.Default HUD of game mode
 */
UCLASS()
class RPG_PROJECT_API ARPG_projectHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Change the player HUD to game over UI, after player dead
	// Called in RPG_projectCharacter
	void GameOver();
	
	/** 
	 * Getter & Setter
	 */
	FORCEINLINE URPG_projectOverlay* GetRPG_ProjectOverlay() const { return RPG_projectOverlay; }
	
protected:
	// P197.
	virtual void BeginPlay() override;
	
private:
	// P197. A template array that can save URPG_projectOverlay-type classes,
	// which is the default HUD derived from RPG_projectOverlay, i.e. WBP_RPG_projectOverlay from Editor
	UPROPERTY(EditDefaultsOnly, Category = RPG_project)
	TSubclassOf<URPG_projectOverlay> URPG_projectClass;

	// Will be set in RPG_projectCharacter
	UPROPERTY()
	URPG_projectOverlay* RPG_projectOverlay;

	UPROPERTY(EditDefaultsOnly, Category = RPG_project)
	TSubclassOf<UGameOverUI> UGameOverClass;
	
	UPROPERTY()
	UGameOverUI* GameOverUI;
	
	// Declare && Initialize HUDState
	EHUDState HUDState = EHUDState::EHS_InGaming;
	
};
