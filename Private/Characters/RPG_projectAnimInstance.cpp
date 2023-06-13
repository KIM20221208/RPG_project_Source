// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RPG_projectAnimInstance.h"
#include "Characters/RPG_projectCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void URPG_projectAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// 79.UE5の中、Cast<>はdynamic_cast<>に当てはまる。TryGetPawnOwner()のreturnはARPG_projectCharacterになる。
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
		// P79.キャラのX、Y軸のベクトルの長さをreturnする、キャラが移動しているかどうかを判断出来る。
		GroundSpeed = UKismetMathLibrary::VSizeXY(RPG_projectCharacterMovement->Velocity);
		// P81.フレームごとにキャラが落下状態にいるからどうかを判断する。
		IsFalling = RPG_projectCharacterMovement->IsFalling();
		// P97.フレームごとにキャラの武器装備状況を判断する。
		CharacterState = RPG_projectCharacter->GetCharacterState();
		// P201.Check action state of RPG_projectCharacter every frame
		ActionState = RPG_projectCharacter->GetActionState();
		// P201.Check DeathPose of RPG_projectCharacter every frame
		DeathPose = RPG_projectCharacter->GetDeathPose();
		
	}

}
