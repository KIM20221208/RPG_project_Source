// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

class AItem;
class ASoul;
class ATreasure;
class APotion;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface class related to pickup items
 */

class RPG_PROJECT_API IPickupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// P206.Setter: ARPG_projectCharacterからoverride。
	// プレイヤーが操作しているキャラの"OverlappingItem"を衝突されたオブジェクトに代入する。
	virtual void SetOverlappingItem(AItem* Item);
	// P206.Setter: キャラのAttributesの"Souls"量を更新する。
	virtual void AddSoul(ASoul* Soul);
	// P208.Setter: キャラのAttributesの"Golds"量を更新する。
	virtual void AddGold(ATreasure* Treasure);
	// TODO: 回復アイテム。
	virtual void AddHealthPoint(APotion* Potion);
	
};
