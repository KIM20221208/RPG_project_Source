// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// P212.tick functionの使用を禁止する。
	PrimaryComponentTick.bCanEverTick = false;

}

// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

bool UAttributeComponent::IsAlive()
{
	return Health > 0.f;

}

void UAttributeComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0.f, MaxStamina);
	
}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	// P155.FMath構造体のClampで体力を更新する。メリットは閾値（体力の最小、最大値）を設定する事が出来る。
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

}

void UAttributeComponent::UseStamina(float StaminaCost)
{
	// P212.FMath構造体のClampでスタミナを更新する。メリットは閾値（体力の最小、最大値）を設定する事が出来る。
	Stamina = FMath::Clamp(Stamina - StaminaCost, 0.f, MaxStamina);
	
}

float UAttributeComponent::GetHealthPercent()
{
	return Health / MaxHealth;

}

float UAttributeComponent::GetStaminaPercent()
{
	return Stamina / MaxStamina;
	
}

void UAttributeComponent::AddGold(int32 AmountOfGold)
{
	Gold += AmountOfGold;
	
}

void UAttributeComponent::AddSoul(int32 AmountOfSoul)
{
	Soul += AmountOfSoul;
	
}

// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
