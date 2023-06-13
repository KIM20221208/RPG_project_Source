// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPG_projectOverlay.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * P196. プレイヤーの各種属性を表示するHUDクラス、エディタのwidget blueprintとbind用。
 */

UCLASS()
class RPG_PROJECT_API URPG_projectOverlay : public UUserWidget
{
	GENERATED_BODY()

	
public:
	/**
	　* Getter & Setter
	　*/
	// P196.Setter: Progress barの値をPercentageよりセットする。
	void SetHealthProgressBarPercent(float Percent);
	void SetStaminaProgressBarPercent(float Percent);
	void SetGold(int32 Gold);
	void SetSouls(int32 Souls);

	
private:
	// P196.UProgressBar typeのポインターを宣言する。
	// C++でのメンバー変数とwidget blueprintでのcomponentと同じ名前でネーミングする必要がある。或はbind出来ない。
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaProgressBar;

	// P196.Text Block typeのポインターを宣言する。
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SoulCountText;
	
};
