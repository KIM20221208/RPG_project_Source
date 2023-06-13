// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Itmes/Souls/Soul.h"
#include "Perception/PawnSensingComponent.h"
#include "Itmes/Weapons/Weapon.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	/**
	* 敵クラスのMeshに関する初期設定。
	*/
	// P123.被ダメージの衝突判定用。
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	// P123.被ダメージの衝突判定用。
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	// P123.衝突時イベントを生成する。
	GetMesh()->SetGenerateOverlapEvents(true);
	// P123.プレイヤーのカメラをIgnoreする。
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	

	/**
	* Componentの作成及び初期設定
	*/
	// P152.キャラのHealthBar。
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
	// P168.プレイヤーを探知するSensing。
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);

	
	// P164.キャラの向きを前進している方向に向かうようにする。
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P179.キャラが死んだら、AIモードの判断をしない。
	if (IsDead()) return;
	// P169.キャラが攻撃あるいは追いかけ状態にいる時、戦闘相手が自分と離れた範囲がdefaultの値より遠いかを判断する。
	// true: HealthBarをプレイヤーが見えないように隠す、false: パトロール状態に入る。
	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
		
	}
	else
	{
		CheckPatrolTarget();
		
	}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	// P160.攻撃された時、攻撃者を戦闘相手に設定する。
	CombatTarget = EventInstigator->GetPawn();
	// P191.戦闘時の攻撃間隔。
	if (IsInsideAttackRadius())
	{
		EnemyState = EEnemyState::EES_Attacking;
		
	}
	else if (IsOutsideAttackRadius())
	{
		ChaseTarget();
		
	}
	return DamageAmount;
	
}

void AEnemy::Destroyed()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();

	}

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	
	// P160.キャラのHealthBarを表示する。
	// P188.キャラが死んでいないなら。
	if (!IsDead())
	{
		ShowHealthBar();

	}

	// P188.キャラが攻撃された時、同時にパトロールをtriggerする事を防ぐため、攻撃された時パトロールのタイマーをclearする。
	ClearPatrolTimer();
	// P191.キャラの攻撃が被ダメージ動画を妨げる為、攻撃された時に攻撃タイマーをclearする。
	ClearAttackTimer();
	StopAttackMontage();

	// P218.攻撃された後、戦闘相手がまだ攻撃範囲内にいるのかを判断する。
	if (IsInsideAttackRadius() && !IsDead())
	{
		StartAttackTimer();
		
	}
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// P168.本クラスの"PawnSeen"メソッドをPawnSensing componentの"OnSeePawn"にbindする。
	// PawnSensingよりプレイヤーを探知出来た時、"PawnSeen"をcallする。
	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
		
	}
	
	InitializeEnemy();
	// P183.別のクラスで敵かどうかの判断用Tag。
	Tags.Add(FName("Enemy"));

}

void AEnemy::Attack()
{
	Super::Attack();
	if (CombatTarget == nullptr) return;
	// P181.キャラが攻撃時に状態を"Engaged"に設定して、別の動きと衝突されることを防ぐ。
	EnemyState = EEnemyState::EES_Engaged;
	PlayAttackMontage();
	
}

bool AEnemy::CanAttack()
{
	bool bCanAttack = IsInsideAttackRadius() &&
		!IsAttacking() &&
		!IsEngaged() &&
		!IsDead();

	return bCanAttack;

}

void AEnemy::HandleDamage(float DamageAmount)
{
	Super::HandleDamage(DamageAmount);

	// P155.UArrtributeComponentクラスのReceiveDamage methodをcallして体力の値を更新する
	if (Attributes && HealthBarWidget)
	{
		// P154.UHealthBarComponentクラスのSetHealthPercentメソッドでキャラの体力をセットする。
		// AttributesクラスのGetHealthPercentメソッドでキャラの体力の値を更新する。
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());

	}

}

void AEnemy::ActionEnd()
{
	EnemyState = EEnemyState::EES_NoState;
	CheckCombatTarget();

}

void AEnemy::Die_Implementation()
{
	Super::Die_Implementation();
	
	// P180.整理をした。
	EnemyState = EEnemyState::EES_Dead;
	ClearAttackTimer();
	DisableCapsule();
	// P160.キャラが死んだ後、死体の存続時間を設定する。
	SetLifeSpan(DeathLifeSpan);
	// P160.キャラが死んだ後、HealthBarを消す。
	HideHealthBar();
	// P180.Bug: キャラが死んだ後、時々死体が回転する。
	// Debug: キャラが死んだ後、向きの回転をcloseする。
	GetCharacterMovement()->bOrientRotationToMovement = false;
	SpawnSoul();
	
}

void AEnemy::SpawnSoul()
{
	UWorld* World = GetWorld();
	if (World && SoulClass && Attributes)
	{
		// P221.let the location of Spawning Soul a little bit higher than Actor location
		const FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 125.f);
		ASoul* SpawnedSoul = World->SpawnActor<ASoul>(SoulClass, SpawnLocation, GetActorRotation());
		if (SpawnedSoul)
		{
			SpawnedSoul->SetSouls(Attributes->GetSoul());
			// P221.Set Owner when soul is spawned 
			SpawnedSoul->SetOwner(this);
		}
		
	}
	
}

void AEnemy::InitializeEnemy()
{
	// P165.キャラがオブジェクト化する時にControllerをゲット、かつパトロールターゲット（動的配列、エディタで代入）に移動させる。
	EnemyController = Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);
	HideHealthBar();
	SpawnDefaultWeapon();

}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;
	// P165.FAIMoveRequest構造体の"SetGoalActor"メソッドでパトロールターゲットを設定する。
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	// P165.パトロールターゲットを円の中心として、AcceptanceRadiusを半径とした円まで移動させる。
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	// P165.パトロールターゲットに移動させる。
	EnemyController->MoveTo(MoveRequest);

}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, CombatRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		// P167.FTimerManager構造体のSetTimerメソッドでパトロールターゲットにたどり着いた後Idleの長さを設定する：5~10秒。
		float WaitTime = FMath::RandRange(PatrolWaitMin, PatrolWaitMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinished, WaitTime);

	}

}

void AEnemy::CheckCombatTarget()
{
	if (IsOutsideCombatRadius())
	{
		ClearAttackTimer();
		LoseInterest();
		if (!IsEngaged())
		{
			StartPatrolling();

		}

	}
	else if (IsOutsideAttackRadius() && !IsChasing())
	{
		ClearAttackTimer();
		if (!IsEngaged())
		{
			ChaseTarget();

		}

	}
	else if (CanAttack())
	{
		// P179.开始新的计时的时候会重置计时器
		StartAttackTimer();

	}

}

void AEnemy::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget);

}

void AEnemy::HideHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}

}

void AEnemy::ShowHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}

}

void AEnemy::LoseInterest()
{
	// P160.プレイヤーとの相対的距離がCombatRadiusより遠いければ、興味を失う。
	CombatTarget = nullptr;
	HideHealthBar();

}

void AEnemy::StartPatrolling()
{
	// P170.パトロール状態に戻る。移動スピードが元に戻り、本来のパトロールターゲットに移動する。
	EnemyState = EEnemyState::EES_Patrolling;
	GetCharacterMovement()->MaxWalkSpeed = PatrollingSpeed;
	MoveToTarget(PatrolTarget);

}

void AEnemy::ChaseTarget()
{
	// P171.プレイヤーとの相対的距離がAttackRadiusより大きい、かつcombatRadiusより小さい時、追いかけ状態に入る。
	EnemyState = EEnemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;
	MoveToTarget(CombatTarget);

}

bool AEnemy::IsOutsideCombatRadius()
{
	return !InTargetRange(CombatTarget, CombatRadius);
	
}

bool AEnemy::IsOutsideAttackRadius()
{
	return !InTargetRange(CombatTarget, AttackRadius);
	
}

bool AEnemy::IsInsideAttackRadius()
{
	return InTargetRange(CombatTarget, AttackRadius);
	
}

bool AEnemy::IsChasing()
{
	return EnemyState == EEnemyState::EES_Chasing;
	
}

bool AEnemy::IsAttacking()
{
	return EnemyState == EEnemyState::EES_Attacking;
	
}

bool AEnemy::IsDead()
{
	return EnemyState == EEnemyState::EES_Dead;
	
}

bool AEnemy::IsEngaged()
{
	return EnemyState == EEnemyState::EES_Engaged;
	
}

void AEnemy::ClearPatrolTimer()
{
	GetWorldTimerManager().ClearTimer(PatrolTimer);

}

void AEnemy::StartAttackTimer()
{
	// P171.キャラの行動パタンを"Attacking"に設定する。
	EnemyState = EEnemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(AttackMin, AttackMax);
	// P179.AttackTime秒後、本クラスのAttackメソッドをcallする。
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime);

}

void AEnemy::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
	
}

AActor* AEnemy::ChoosePatrolTarget()
{
	// P166.元のパトロールタイマーを含んでいないパトロールターゲット配列を作る。
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target != PatrolTarget)
		{
			ValidTargets.AddUnique(Target);

		}

	}

	const int32 NumPatrolTargets = ValidTargets.Num();
	if (NumPatrolTargets > 0 && EnemyController)
	{
		const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
		return PatrolTargets[TargetSelection];
		
	}
	return nullptr;

}

bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	// P160.キャラとActorクラス間の距離を計算する。
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= Radius;

}

void AEnemy::SpawnDefaultWeapon()
{
	// P177.エディタのBlueprintから武器を代入する。
	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		// P177.Worldに武器をオブジェクト化して生成する。
		AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		// P177.AWeaponクラスの"Equip"メソッドをcallして武器をキャラのsocketに装備する。
		// P216.元の"Right hand socket"を"Weapon socket"に修正。
		DefaultWeapon->Equip(GetMesh(), FName("WeaponSocket"), this, this);
		// P177.キャラが装備している武器を記録する。
		EquippedWeapon = DefaultWeapon;

	}
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	// P179.キャラが追いかけ可能な状態にいる、かつ探知出来たAPawnクラスのオブジェクトが戦闘すべき相手（"EngageableTarget"Tagを持つ）である。
	const bool bShouldChaseTarget =
		EnemyState != EEnemyState::EES_Dead &&
		EnemyState != EEnemyState::EES_Chasing &&
		EnemyState < EEnemyState::EES_Attacking &&
		SeenPawn->ActorHasTag(FName("EngageableTarget"));

	if (bShouldChaseTarget)
	{
		// P169.探知出来たAPawnクラスのオブジェクトを戦闘相手に設定して追いかけ状態にに入る。
		CombatTarget = SeenPawn;
		ClearPatrolTimer();
		ChaseTarget();

	}

}
