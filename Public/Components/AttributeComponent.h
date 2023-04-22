// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

/*
* Related to store character attributes, those attributes will be shown by HUD
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_PROJECT_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// P158.声明角色是否存货的成员变量，如果 Health > 0 则返回 true
	bool IsAlive();
	// P212.Regenerate stamina every frame
	void RegenStamina(float DeltaTime);

	/*
	* Getter & Setter
	*/
	// P155.按照受到的伤害更新生命值
	void ReceiveDamage(float Damage);
	// P212.Cost Stamina when doing action
	void UseStamina(float StaminaCost);
	// P155.取得角色血量百分比
	float GetHealthPercent();
	// P155.get current stamina the character have
	float GetStaminaPercent();
	// P208.Set Gold and Soul
	void AddGold(int32 AmountOfGold);
	void AddSoul(int32 AmountOfSoul);
	// P208.Get Gold and Soul
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSoul() const { return Soul; }
	// P212.Getter: DodgeCost
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	// P212.Getter: Stamina, but not percentage
	FORCEINLINE float GetStamina() const { return Stamina; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// P151.声明现有生命值
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;
	
	// P151.声明最大生命值
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	// P211.Declare left stamina
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Stamina;
	
	// P211.Declare max stamina
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina;

	// P212.The Cost that Dodge needed
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float DodgeCost = 15.f;

	// P212.Stamina regeneration rate
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float StaminaRegenRate = 8.f;
	
	// P208.Save the amount of Golds RPG_project character has
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Gold;

	// P208.Save the amount of Souls RPG_project character has
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Soul;
	
};
