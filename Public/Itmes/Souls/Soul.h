// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Itmes/Item.h"
#include "Soul.generated.h"

class UNiagaraSystem;
/**
 * Soul Actor generated after enemy dead
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
	// P209.Setter: Souls, when ASoul is spawning after enemy dead
	FORCEINLINE void SetSouls(int32 NumberOfSouls) { Souls = NumberOfSouls; }

	
protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */

	
	/** <AItem> */
	// P205.related to pickup Soul
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/** </AItem> */


	// P221.Stop position of soul moving after spawned
	double DesiredZ;
	// P221.Stop drifting height from the land, default is 50
	double StopDriftFromLand = 100;
	// P221.the moving speed after soul spawned, default value is -15.f
	UPROPERTY(EditAnywhere)
	float DriftRate = -15.f;
	

	
private:
	// P208.Amount of Souls the enemy gonna drop
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 Souls;
	
};
