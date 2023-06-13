// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

/**
 * キャラの色んな属性、HUD等でプレイヤーに見せる。
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_PROJECT_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this component's properties
	UAttributeComponent();

	/** <AActor> */
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** </AActor> */

	// P158.キャラが生きているからどうかを判断する。
	// Health > 0: true, else: false.
	bool IsAlive();
	// P212.フレームごとにスタミナを更新（回復）する。ARPG_projectCharacterのTickメソッドでcallされる。
	void RegenStamina(float DeltaTime);

	/**
	 * Getter & Setter
	 */
	// P155.Setter: 受けたダメージより体力を更新する。
	void ReceiveDamage(float Damage);
	// P212.Setter: 回避をする時、スタミナを消耗する。
	void UseStamina(float StaminaCost);
	// P155.Getter:　キャラの体力のPercentageをゲットする。
	float GetHealthPercent();
	// P155.Getter:　キャラのスタミナのPercentageをゲットする。
	float GetStaminaPercent();
	// P208.Setter: Set Gold and Soul.
	void AddGold(int32 AmountOfGold);
	void AddSoul(int32 AmountOfSoul);
	// P208.Getter:　Get Gold and Soul.
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSoul() const { return Soul; }
	// P212.Getter: DodgeCost.
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	// P212.Getter: Stamina, but not percentage.
	FORCEINLINE float GetStamina() const { return Stamina; }

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
private:
	// P151.キャラの体力、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;
	
	// P151.キャラの体力の最大値、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	// P211.キャラのスタミナ、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Stamina;
	
	// P211.キャラのスタミナの最大値、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina;

	// P212.回避のスタミナコスト、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float DodgeCost = 15.f;

	// P212.スタミナの回復率、エディタから代入。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float StaminaRegenRate = 8.f;
	
	// P208.キャラが持っているGoldの量。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Gold;

	// P208.キャラが持っているSoulの量。
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Soul;
	
};
