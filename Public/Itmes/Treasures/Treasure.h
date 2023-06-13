// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itmes/Item.h"
#include "Treasure.generated.h"

/**
 * 宝物のベースクラス。
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
	/** <AItem> */
	// P143.宝物を拾う。
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	/** </AItem> */
	
	
private:
	// P146.宝物のGold量、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;

};
