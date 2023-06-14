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

	// P72.“Use Controller Rotation”の初期設定。
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// P74.キャラの向きを移動方向に向う。
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	// P183.キャラモデルの"Collision Preset"に関する初期設定。
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);


	/**
	* Componentの作成及び初期設定
	*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// P75
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	// P75
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrow"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

}

// Called every frame
void ARPG_projectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// P212. フレームごとにスタミナを回復する、default regenerate value is 8.f / frame.
	// Debug: Main Menu UIではRPG_projectOverlayが無い為、スタミナを更新する時にRPG_projectOverlayクラスの存在をcheckすべき。
	if (Attributes && RPG_projectOverlay)
	{
		Attributes->RegenStamina(DeltaTime);
		RPG_projectOverlay->SetStaminaProgressBarPercent(Attributes->GetStaminaPercent());
		
	}
	
}

// Called to bind functionality to input
void ARPG_projectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// P71.プレイヤー操作バインド：前後移動。
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARPG_projectCharacter::MoveForward);
	// P72.プレイヤー操作バインド：カメラ移動。
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ARPG_projectCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ARPG_projectCharacter::LookUp);
	// P73.プレイヤー操作バインド：左右移動。
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARPG_projectCharacter::MoveRight);

	// P80.プレイヤー操作バインド：ジャンプ。
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	// P96.プレイヤー操作バインド：装備。
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &ARPG_projectCharacter::EKeyPressed);
	// P103.プレイヤー操作バインド：攻撃。
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ARPG_projectCharacter::Attack);
	// P211.プレイヤー操作バインド：回避。
	PlayerInputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &ARPG_projectCharacter::Dodge);
	// プレイヤー操作バインド：ゲーム内オプション画面呼び出し。
	PlayerInputComponent->BindAction(TEXT("InGamePause"), IE_Pressed, this, &ARPG_projectCharacter::ESCKeyPressed);
	
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
	// P201.キャラが生きているからどうかを判断しないと、"Dead"に設定されたActionStateが"HitReaction"に再び変更される。
	if (IsAlive())
	{
		// P188.Bug：キャラが攻撃する瞬間に攻撃されると、永遠に攻撃出来ない。
		// Debug：攻撃された時に、キャラの状態を"HitReaction"に設定する。
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
		// P74.カメラ移動後、キャラが移動すべき前方の方向を計算する。
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
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
		// P74.カメラ移動後、キャラが移動すべき右の方向を計算する。
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
		
	}

}

void ARPG_projectCharacter::EKeyPressed()
{ 
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon) 
	{
		// P221.新しい武器を装備する時、元の武器を破壊（キャンセル）する。
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
			
		}
		EquipWeapon(OverlappingWeapon);

	}
	// P110.装備動画をプレイしているかどうかを判断する。
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
	// P105.キャラが攻撃可能な状態にいるからどうかを判断する。
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
	// Debug: Main Menu UIではRPG_projectOverlayが無い為、スタミナを更新する時にRPG_projectOverlayクラスの存在をcheckすべき。
	if (Attributes && RPG_projectOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		RPG_projectOverlay->SetStaminaProgressBarPercent(Attributes->GetStaminaPercent());
		
	}
	
}

void ARPG_projectCharacter::ESCKeyPressed()
{
	if (RPG_projectHUD->GetHUDState() == EHUDState::EHS_InGaming)
	{
		RPG_projectHUD->ShowInGamePauseUI();
		
	}
	else if (RPG_projectHUD->GetHUDState() == EHUDState::EHS_InGamePause)
	{
		RPG_projectHUD->CloseInGamePauseUI();
		
	}
	
}

 void ARPG_projectCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	// P110.キャラが装備している武器を記録。
	EquippedWeapon = Weapon;
	// P110.Debug: From comment. 
	OverlappingItem = nullptr;

}

void ARPG_projectCharacter::ActionEnd()
{
	ActionState = EActionState::EAS_Unoccupied;

}

bool ARPG_projectCharacter::CanAttack()
{
	return (ActionState == EActionState::EAS_Unoccupied
		&& CharacterState != ECharacterState::ECS_Unequipped);
}

void ARPG_projectCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	ActionState = EActionState::EAS_Dead;
	RPG_projectHUD->ShowGameOverUI();
	
}

bool ARPG_projectCharacter::CanDisarm()
{
	return (ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped);
}

bool ARPG_projectCharacter::CanArm()
{
	return (ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped &&
		EquippedWeapon);
	
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
	// Debug: Main Menu UIではRPG_projectOverlayが無い為、スタミナを更新する時にRPG_projectOverlayクラスの存在をcheckすべき。
	if (Attributes && RPG_projectOverlay)
	{
		RPG_projectOverlay->SetHealthProgressBarPercent(Attributes->GetHealthPercent());
		
	}
	
}
