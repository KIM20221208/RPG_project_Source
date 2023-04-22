// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// P61.使用 factory function 创建默认Capsule组件
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));

	// P61.变更Capsule参数
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);

	// P61.设置为根组件，与 RootComponent = Capsule 相等
	SetRootComponent(Capsule);

	// P63.使用 factory function 创建默认骨骼网格体组件
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	// P63.把 BirdMesh 添加到根组件
	BirdMesh->SetupAttachment(GetRootComponent());

	// P66.使用 factory function 创建默认弹簧组件，并添加到Capsule组件下
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Capsule);
	// P66.设定弹簧组件臂长
	CameraBoom->TargetArmLength = 300.f;

	// P66.使用 factory function 创建默认相机组件
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	// P64.设定自动控制玩家
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABird::MoveForward(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

	// P65.添加移动输入: 只有被设定为poccess 且 当按了相应按键时
	if (Controller && (Value != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
}

void ABird::Turn(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Turn Value: %f"), Value);
	AddControllerYawInput(Value);

}

void ABird::LookUp(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("LookUp Value: %f"), Value);
	AddControllerPitchInput(Value);

}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// P64.绑定按键: 前后
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward);
	// P67.绑定按键: 视角转动
	// 注意在UE5中的details pannel中设置 “使用控制器旋转XX”
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABird::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABird::LookUp);

}

