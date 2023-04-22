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
	// P122.virtual function：called in AWeapon class When get hit，pass impact point and weapon owner 
	// P140.For implement this function both editable in C++ and blueprint, added UFUNCTION(BlueprintNativeEvent) and delete some key words
	// P189.Improving directional hit reaction, when weapon penetrate character's body  
	UFUNCTION(BlueprintNativeEvent)
	void GetHit(const FVector& ImpactPoint, AActor* Hitter);

};
