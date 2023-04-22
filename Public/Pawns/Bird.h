// Fill out your copyright notice in the Description page of Project Settings.

// P62.防止重复引用头文件
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

// P62.前向声明: 防止重复/互相引用头文件
class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

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

	// P64.声明移动映射输入函数
	void MoveForward(float Value);

	//P66.声明水平转向映射输入函数
	void Turn(float Value);

	//P66.声明垂直转向映射输入函数
	void LookUp(float Value);

private:
	// P61.声明碰撞体积Capsule指针变量
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	// P63.声明骨骼网格体指针变量
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

	// P66.声明弹簧组件指针
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	// P66.声明相机组件指针
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

};
