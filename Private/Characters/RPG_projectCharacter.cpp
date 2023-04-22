 // Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RPG_projectCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Components/AttributeComponent.h"
#include "Itmes/Item.h"
#include "Itmes/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "HUD/RPG_projectHUD.h"
#include "HUD/RPG_projectOverlay.h"
#include "Itmes/Souls/Soul.h"
#include "Itmes/Treasures/Treasure.h"

 // Sets default values
ARPG_projectCharacter::ARPG_projectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// P72.初始化“使用控制器旋转”
	bUseControllerRotationPitch = false; 
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// P74.调用角色移动类中的 “将旋转朝向运动”成员函数，使角色朝向前进方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	// P183.设置角色网格体的碰撞预设
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// P75.使用 factory function 创建Groom组件类的头发
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	// P75.建立连接到Mesh
	Hair->SetupAttachment(GetMesh());
	// P75.把创建的头发插到“head”插件
	Hair->AttachmentName = FString("head");

	// P75.使用 模板函数 创建Groom组件类的眉毛
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrow"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

}

// Called every frame
void ARPG_projectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// P212. regenerate stamina (default regenerate value is 8.f) every frame,
	if (Attributes)
	{
		Attributes->RegenStamina(DeltaTime);
		RPG_projectOverlay->SetStaminaProgressBarPercent(Attributes->GetStaminaPercent());
	}
}

// Called to bind functionality to input
void ARPG_projectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// P71.创建轴映射链接
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARPG_projectCharacter::MoveForward);
	// P72.创建轴映射链接
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ARPG_projectCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ARPG_projectCharacter::LookUp);
	// P73.创建轴映射链接
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARPG_projectCharacter::MoveRight);

	// P80.创建操作映射链接，跳跃
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	// P96.创建操作映射链接，交互
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &ARPG_projectCharacter::EKeyPressed);
	// P103.创建操作映射链接，攻击
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ARPG_projectCharacter::Attack);
	// P211.Bind Dodge action to input
	PlayerInputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &ARPG_projectCharacter::Dodge);
	
}

float ARPG_projectCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;
	
}

void ARPG_projectCharacter::Jump()
{
	if (IsUnoccupied())
	{
		Super::Jump();
	}
	
}

void ARPG_projectCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	// P201.if don't check Is Alive, Action state will be covered by Hit Reaction after setting to Dead In Super Fuction
	if (IsAlive())
	{
		// P188.为了修复角色在攻击的同时受到攻击时产生不能进行攻击动作，在受到攻击的时候角色状态设置为“受到攻击”
		ActionState = EActionState::EAS_HitReaction;
	}

}

void ARPG_projectCharacter::SetOverlappingItem(AItem* Item)
{
	 OverlappingItem = Item;
	
}

void ARPG_projectCharacter::AddSoul(ASoul* Soul)
{
	if (Attributes && RPG_projectOverlay)
	{
		// P208.Refresh the Soul param in Attributes
		Attributes->AddSoul(Soul->GetSouls());
		// P208.Refresh the Soul param in Overlay
		RPG_projectOverlay->SetSouls(Attributes->GetSoul());
		
	}
	
}

void ARPG_projectCharacter::AddGold(ATreasure* Treasure)
{
	if (Attributes&& RPG_projectOverlay)
	{
		// P208.Refresh the Soul param in Attributes
		Attributes->AddGold(Treasure->GetGold());
		// P208.Refresh the Soul param in Overlay
		RPG_projectOverlay->SetGold(Attributes->GetGold());
		
	}
}

 // Called when the game starts or when spawned
void ARPG_projectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// P169.Tag for distinguishing class
	Tags.Add(FName("EngageableTarget"));
	
	InitializeRPG_projectOverlay();
	
}

void ARPG_projectCharacter::MoveForward(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller && (Value != 0.f))
	{
		// P74.判断镜头旋转后的前方
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		// P74.以旋转矩阵，得到旋转后的X坐标
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}

}

void ARPG_projectCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);

}

void ARPG_projectCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);

}

void ARPG_projectCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller && (Value != 0.f))
	{
		// P74.判断镜头旋转后的右方
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		// P74.以旋转矩阵，得到旋转后的Y坐标
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}

}

void ARPG_projectCharacter::EKeyPressed()
{ 
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon) 
	{
		// P221.Destroy old weapon when equipping new weapon
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		EquipWeapon(OverlappingWeapon);

	}
	// P110.判断是否播放装备动画蒙太奇
	else
	{
		if (CanDisarm())
		{
			DisArm();

		}
		else if (CanArm())
		{
			Arm();

		}
	}

}

void ARPG_projectCharacter::Attack()
{
	Super::Attack();
	// P105.判断是否播放攻击动画: 角色没有在播放的动画 且 角色已装备武器
	
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}

}

 bool ARPG_projectCharacter::IsActionOccupied()
 {
	 return ActionState != EActionState::EAS_Unoccupied;
 }

void ARPG_projectCharacter::Dodge()
{
	if (IsActionOccupied() || !HasEnoughStamina()) return;

	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		RPG_projectOverlay->SetStaminaProgressBarPercent(Attributes->GetStaminaPercent());
	}
	
}

 void ARPG_projectCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	// P110.定义装备中的武器
	EquippedWeapon = Weapon;
	// P110.来自评论区的代码: 下面的赋值是为什么？
	OverlappingItem = nullptr;

}

void ARPG_projectCharacter::ActionEnd()
{
	ActionState = EActionState::EAS_Unoccupied;

}

bool ARPG_projectCharacter::CanAttack()
{
	return (ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped);
}

bool ARPG_projectCharacter::CanDisarm()
{
	return (ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped);
}

bool ARPG_projectCharacter::CanArm()
{
	return (ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_Unequipped && EquippedWeapon);
}

void ARPG_projectCharacter::DisArm()
{
	PlayEquipMontage(FName("Unequip"));
	CharacterState = ECharacterState::ECS_Unequipped;
	ActionState = EActionState::EAS_EquippingWeapon;

}

void ARPG_projectCharacter::Arm()
{
	PlayEquipMontage(FName("Equip"));
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	ActionState = EActionState::EAS_EquippingWeapon;

}

void ARPG_projectCharacter::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
	
}

void ARPG_projectCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	ActionState = EActionState::EAS_Dead;
	RPG_projectHUD->GameOver();
	
}

bool ARPG_projectCharacter::HasEnoughStamina()
{
	return Attributes && Attributes->GetStamina() > Attributes->GetDodgeCost();
}

void ARPG_projectCharacter::AttachWeaponToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));

	}

}

void ARPG_projectCharacter::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));

	}

}

void ARPG_projectCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;

}

bool ARPG_projectCharacter::IsUnoccupied()
{
	return CharacterState == ECharacterState::ECS_Unequipped;
}

void ARPG_projectCharacter::InitializeRPG_projectOverlay()
{
	// P198. if the Actor is controlled by player, not AI
	APlayerController* PlayerController = Cast<APlayerController>(GetController()); 
	if (PlayerController)
	{
		RPG_projectHUD = Cast<ARPG_projectHUD>(PlayerController->GetHUD());
		if (RPG_projectHUD )
		{
			RPG_projectOverlay = RPG_projectHUD->GetRPG_ProjectOverlay();
			if (RPG_projectOverlay && Attributes)
			{
				RPG_projectOverlay->SetHealthProgressBarPercent(Attributes->GetHealthPercent());
				RPG_projectOverlay->SetStaminaProgressBarPercent(.1f);
				RPG_projectOverlay->SetGold(0);
				RPG_projectOverlay->SetSouls(0);
				
			}
			
		}
		
	}
}

void ARPG_projectCharacter::SetHUDHealth()
{
	if (Attributes)
	{
		RPG_projectOverlay->SetHealthProgressBarPercent(Attributes->GetHealthPercent());
		
	}
}
