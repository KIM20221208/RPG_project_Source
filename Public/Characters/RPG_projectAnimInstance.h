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
 * プレイヤーが操作しているキャラの動画制御に関するクラス
 */
UCLASS()
class RPG_PROJECT_API URPG_projectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	/** <UAnimInstance> */
	// P79.override“事件蓝图开始播放（Event Blueprint Begin Play）”。
	virtual void NativeInitializeAnimation() override;
	// P79.override“事件蓝图更新动画（Event Blueprint Update Animation）”。
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	/** </UAnimInstance> */

	// P79.プレイヤーが操作しているキャラ。
	UPROPERTY(BlueprintReadOnly)
	ARPG_projectCharacter* RPG_projectCharacter;

	// P79.キャラの移動。
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* RPG_projectCharacterMovement;

	// P79.キャラの水平的移動の判断用。
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	// P81.キャラの垂直的移動の判断用。
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;

	// P97.フレームごとにキャラの武器装備状況、エディタで色んな動画（武器あり、なしのランニングポーズ等）をプレイする時の参考。
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECharacterState CharacterState;

	// P201.フレームごとにキャラが取っている行動、エディタで色んな動画（死亡、攻撃等）をプレイする時の参考。
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EActionState ActionState;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	TEnumAsByte<EDeathPose> DeathPose;
	
};
