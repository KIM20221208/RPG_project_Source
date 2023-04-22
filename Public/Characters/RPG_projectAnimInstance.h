// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "Characters/CharacterTypes.h"
#include "RPG_projectAnimInstance.generated.h"

class ARPG_projectCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class RPG_PROJECT_API URPG_projectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// P79.覆盖声明父类中的“事件蓝图开始播放（Event Blueprint Begin Play）”函数
	virtual void NativeInitializeAnimation() override;

	// P79.覆盖声明父类中的“事件蓝图更新动画（Event Blueprint Update Animation）”函数
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	// P79.声明角色变量指针，并让他只在蓝图中可见
	UPROPERTY(BlueprintReadOnly)
	ARPG_projectCharacter* RPG_projectCharacter;

	// P79.声明角色移动变量指针，并让他只在蓝图中可见
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* RPG_projectCharacterMovement;

	// P79.声明float型变量，用来判断角色的 X & Y 轴的变化
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	// P81.声明bool型变量，用来判断角色跳跃
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;

	// P97.返回逐帧检查的 uint8型的 角色武器装备状态
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECharacterState CharacterState;

	// P201.
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EActionState ActionState;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	TEnumAsByte<EDeathPose> DeathPose;
	
};
