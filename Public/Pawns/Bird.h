// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

/**
 * プレイヤー操作キャラテスト用クラス、実際のプロジェクトに使用されていない
 */

UCLASS()
class RPG_PROJECT_API ABird : public APawn
{
	GENERATED_BODY()

	
public:
	// Sets default values for this pawn's properties
	ABird();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// P64.プレイヤー操作：キャラの前後移動：
	// Value > 0: forward, Value < 0: backward
	void MoveForward(float Value);
	// P66.プレイヤー操作：カメラの左右移動
	// Value > 0: right, Value < 0: left
	void Turn(float Value);
	// P66.プレイヤー操作：キャラの上下移動
	// Value > 0: upward, Value < 0: downward
	void LookUp(float Value);

	
private:
	// P61.キャラが環境との衝突判定用ボリューム
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	// P66.キャラのカメラ用SpringArm
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	// P66.キャラのカメラ
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	// P63.キャラのSkeletalMesh、エディタから代入
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

};
