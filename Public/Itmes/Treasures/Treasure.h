// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itmes/Item.h"
#include "Treasure.generated.h"

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API ATreasure : public AItem
{
	GENERATED_BODY()

public:
	/**
	 * Getter & Setter
	 */
	// P208.Getter: Gold
	FORCEINLINE int32 GetGold() const { return Gold; }
	
	
protected:
	// P143.继承自 Item 类的 当与球体开始碰撞成员函数，并覆盖此函数
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
private:
	// P146.声明金币数量的成员变量
	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;

};
