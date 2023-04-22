// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// P212.If you want to use tick function, make this param ture 
	PrimaryComponentTick.bCanEverTick = false;

}


void UAttributeComponent::ReceiveDamage(float Damage)
{
	// P155.调用 FMath 结构体中的 Clamp 成员函数来设置受到伤害后的生命，好处在于可以设置阈值
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

}

void UAttributeComponent::UseStamina(float StaminaCost)
{
	// P212. make a threshold let the value of stamina always in range of 0 ~ 1 
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

bool UAttributeComponent::IsAlive()
{
	return Health > 0.f;

}


void UAttributeComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0.f, MaxStamina);
}

// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

