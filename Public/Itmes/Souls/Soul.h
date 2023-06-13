// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itmes/Item.h"
#include "Soul.generated.h"

class UNiagaraSystem;

/**
* Soul（経験値）のベースクラス。
*/

UCLASS()
class RPG_PROJECT_API ASoul : public AItem
{
	GENERATED_BODY()

	
public:
	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	/** </AActor> */
	
	/**
	 * Getter & Setter
	 */
	// P208.Getter: Souls
	FORCEINLINE int32 GetSouls() const { return Souls; }
	// P209.Setter: Souls, 敵が死んだ後生成される経験値の量。
	FORCEINLINE void SetSouls(int32 NumberOfSouls) { Souls = NumberOfSouls; }

	
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */
	
	/** <AItem> */
	// P205.Soulsを拾う。
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/** </AItem> */

	// P221.Soulsが生成された後、地面までの移動すべき高さ。
	double DesiredZ;
	// P221.Soulsが地面までの停止すべき高さ、default: 100.f。
	double StopDriftFromLand = 100;
	// P221.Soulsが生成された後、地面までの移動スピード、default value is -15.f、エディタから修正可能。
	UPROPERTY(EditAnywhere)
	float DriftRate = -15.f;

	
private:
	// P208.敵が死んだ後生成されるSoulsの量。
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 Souls;
	
};
