// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface class related to attack
 */
class RPG_PROJECT_API IHitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// P122.仮想関数宣言：攻撃された時、AWeaponクラスからcallされる, pass impact point and weapon owner 
	// P140.本メソッドをC++とエディタ両方から修正可能にする為、, UFUNCTION(BlueprintNativeEvent)マクロを加える
	// P189.当たり判定が発生した位置が発生した位置がキャラの被ダメージ動画をプレイする事を追加
	UFUNCTION(BlueprintNativeEvent)
	void GetHit(const FVector& ImpactPoint, AActor* Hitter);

};
