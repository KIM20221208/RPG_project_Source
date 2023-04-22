// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RPG_projectAnimInstance.h"
#include "Characters/RPG_projectCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void URPG_projectAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// 79.在虚幻5中，Cast<> 等同于 dynamic_cast<>，转换 TryGetPawnOwner() 的返回值类型为 ARPG_projectCharacter
	RPG_projectCharacter = Cast<ARPG_projectCharacter>(TryGetPawnOwner());
	if (RPG_projectCharacter)
	{
		RPG_projectCharacterMovement = RPG_projectCharacter->GetCharacterMovement();
	}
	
}

void URPG_projectAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (RPG_projectCharacterMovement)
	{
		// P79.调用UKismetMathLibrary库中的函数，返回角色移动向量的 X & Y 轴的值
		GroundSpeed = UKismetMathLibrary::VSizeXY(RPG_projectCharacterMovement->Velocity);

		// P81.逐帧检查角色是否处在下落状态，以更新动画
		IsFalling = RPG_projectCharacterMovement->IsFalling();

		// P97.逐帧检查角色的武器装备情况，以更新动画
		CharacterState = RPG_projectCharacter->GetCharacterState();
		// P201.Check action state of RPG_projectCharacter every frame
		ActionState = RPG_projectCharacter->GetActionState();
		// P201.Check DeathPose of RPG_projectCharacter every frame
		DeathPose = RPG_projectCharacter->GetDeathPose();
	}

}
