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

	/*
	* 本类 Mesh 相关初始化
	*/
	// P123.定义 Enemy 类的网格体的对象类型为 “WorldDynamic”，用于攻击判定
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	// P123.定义 Enemy 类的网格体的对象类型为 “WorldDynamic”，用于攻击判定
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	// P123.定义 Enemy 类的网格体忽略“摄像机”
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	// P123.定义Enemy 类的网格体的 “生成重叠时间”为 true
	GetMesh()->SetGenerateOverlapEvents(true);
	

	/*
	* 组件相关初始化
	*/
	// P152.使用模板函数初始化 本地组件 UWidgetComponent，并添加到根组件
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
	// P168.使用模板函数初始化
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);

	// P164.调用角色移动类中的 “将旋转朝向运动”成员函数，使角色朝向前进方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P179.如果角色死亡，则不进行任何AI模式
	if (IsDead()) return;
	// P169.敌人行为模式为追逐或者攻击时，判断战斗对象是否脱离了仇恨范围，true 则 隐藏血条。强类型枚举具有默认的值，可以进行比较
	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	// P169.false则进入巡逻状态
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
	// P160.一旦被攻击，则设置发动攻击的角色为战斗对象
	CombatTarget = EventInstigator->GetPawn();
	// P191.control the attack timer, after get hit
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
	/*
	* 在被击中的点上绘制debug 球体
	* DRAW_SPHERE_COLOR(ImpactPoint, FColor::Orange)
	*/
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	// P160.在角色被攻击时显示血条。P188.除非角色没死
	if (!IsDead())
	{
		ShowHealthBar();

	}
	// P188.为了防止角色在攻击时同时触发巡逻，被攻击时取消巡逻计时器
	ClearPatrolTimer();
	// P191.Attack Timer will impede Get hit animation, so clear attack timer when get hit 
	ClearAttackTimer();
	StopAttackMontage();

	// P218.Check if combat target is still inside attack radius after get hit
	if (IsInsideAttackRadius() && !IsDead())
	{
		StartAttackTimer();
	}
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// P168.添加bind关系到 OnseePawn 默认成员函数，使得触发 OnseePawn 时会callback 本类中的 PawnSeen 成员函数
	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
	}
	InitializeEnemy();
	// P183.为了在别的类中进行是否为本类的判断，而加的 Tag
	Tags.Add(FName("Enemy"));

}

void AEnemy::Attack()
{
	Super::Attack();
	if (CombatTarget == nullptr) return;
	// P181.在角色攻击时设定为占用状态
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

	// P155.调用 UArrtributeComponent 类中的 ReceiveDamage 成员函数更新生命值
	if (Attributes && HealthBarWidget)
	{
		// P154.调用 UHealthBarComponent 类中的 SetHealthPercent 成员函数 设置角色血量，调用GetHealthPercent 成员函数 更新角色血量
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
	/*
	// P158.播放死亡动画蒙太奇
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage);
		// P158.按随机数跳转蒙太奇片段的
		const int32 Section = FMath::RandRange(0, 4);
		FName SectionName = FName();
		switch (Section)
		{
		case 0:
			SectionName = FName("Death1");
			DeathPose = EDeathPose::EDP_Death1;
			break;
		case 1:
			SectionName = FName("Death2");
			DeathPose = EDeathPose::EDP_Death2;
			break;
		case 2:
			SectionName = FName("Death3");
			DeathPose = EDeathPose::EDP_Death3;
			break;
		case 3:
			SectionName = FName("Death4");
			DeathPose = EDeathPose::EDP_Death4;
			break;
		case 4:
			SectionName = FName("Death5");
			DeathPose = EDeathPose::EDP_Death5;
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
	}
	*/
	Super::Die_Implementation();
	
	// P180.经过整理
	EnemyState = EEnemyState::EES_Dead;
	ClearAttackTimer();
	DisableCapsule();
	// P160.设置死亡后角色尸体存续时间
	SetLifeSpan(DeathLifeSpan);
	// P160.角色死亡时隐藏血条
	HideHealthBar();
	// P180.角色死亡后的尸体旋转问题，角色死亡后不允许方向旋转
	GetCharacterMovement()->bOrientRotationToMovement = false;
	// P188.为了防止在攻击中死亡时，死亡动作中手中的武器还具有碰撞，角色死亡时取消装备的武器碰撞
	// SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);

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
	// P165.在此类实例化时得到它的控制器，并设置角色的自动巡逻点
	EnemyController = Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);
	HideHealthBar();
	SpawnDefaultWeapon();

}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;
	// P165.通过定义 FAIMoveRequest 结构体来设置目标点
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	// P165.Stop in certain radius circle
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	/*
	// P165.由移动路线的 起始&结束点 组成的数组，通过 AIController 类中的 MoveTo 函数返回
	FNavPathSharedPtr NavPath;
	*/
	EnemyController->MoveTo(MoveRequest);
	/*
	TArray<FNavPathPoint>& PathPoint = NavPath->GetPathPoints();
	// P165.在角色行动路线上画出 DebugSphere
	for (auto& Point : PathPoint)
	{
		const FVector& Location = Point.Location;
		DRAW_SPHERE(Location);

	}
	*/

}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, CombatRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		// P167.调用 FTimerManager 结构体中的 SetTimer 来设置巡逻之间的 Idle 时长，为 5~10秒
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
	// P160.相对距离大于 CombatRadius 则对原战斗对象失去仇恨
	CombatTarget = nullptr;
	HideHealthBar();

}

void AEnemy::StartPatrolling()
{
	// P170.返回巡逻状态，并且恢复移动速度，开始向巡逻节点移动
	EnemyState = EEnemyState::EES_Patrolling;
	GetCharacterMovement()->MaxWalkSpeed = PatrollingSpeed;
	MoveToTarget(PatrolTarget);

}

void AEnemy::ChaseTarget()
{
	// P171.相对距离大于 AttackRadius 小于 CombatRadius 则切换原先的战斗模式到追逐模式
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
	// P169.关闭巡逻时的Idle计时器
	GetWorldTimerManager().ClearTimer(PatrolTimer);

}

void AEnemy::StartAttackTimer()
{
	// P171.相对距离小于 AttackRadius 进入战斗模式
	EnemyState = EEnemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(AttackMin, AttackMax);
	// P179.经过 AttackTime 秒 后 call 本类中的 Attack 成员函数
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime);

}

void AEnemy::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

AActor* AEnemy::ChoosePatrolTarget()
{
	// P166.做一个不包含已经达到的巡逻节点的新数组，防止随机到同一个巡逻节点
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
		/*
		* AActor* Target = PatrolTargets[TargetSelection];
		* PatrolTarget = Target;
		// P165.在此类实例化时得到它的控制器，并设置角色的自动巡逻点
		// P165.通过定义 FAIMoveRequest 结构体来设置目标点
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(PatrolTarget);
		// P165.阻止角色移动的圆
		MoveRequest.SetAcceptanceRadius(15.f);
		EnemyController->MoveTo(MoveRequest);
		*/
		return PatrolTargets[TargetSelection];
	}
	return nullptr;

}

bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	// P160.计算角色和 某个Actor类 的距离
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	/*
	// P166.按照判断半径的 Radius 画出 debug sphere
	DRAW_SPHERE_SINGLEFRAME(Target->GetActorLocation());
	// P166.在角色的位置上画出 debug sphere
	DRAW_SPHERE_SINGLEFRAME(GetActorLocation());
	*/
	return DistanceToTarget <= Radius;

}

void AEnemy::SpawnDefaultWeapon()
{
	// P177.由蓝图中赋值的武器派生类，依附到角色的“右手插口”
	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		// P177.在世界中生成武器实例
		AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		// P177.调用父类 AMyCharacter 的成员函数，依附到角色的“武器插口” P216.modify "Right hand socket" to "Weapon socket"
		DefaultWeapon->Equip(GetMesh(), FName("WeaponSocket"), this, this);
		// P177.对成员变量进行赋值
		EquippedWeapon = DefaultWeapon;

	}
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	// P179.整合在此函数作用域内需要通过的所有判断
	const bool bShouldChaseTarget =
		EnemyState != EEnemyState::EES_Dead &&
		EnemyState != EEnemyState::EES_Chasing &&
		EnemyState < EEnemyState::EES_Attacking &&
		SeenPawn->ActorHasTag(FName("EngageableTarget"));

	if (bShouldChaseTarget)
	{
		// P169.切换战斗对象为看到的角色，并进入追逐模式
		CombatTarget = SeenPawn;
		ClearPatrolTimer();
		ChaseTarget();

	}
	/*
	// P169.为了防止逐帧调用此函数（OnSeePawn 大概每5帧调用一次），浪费资源，预先判断角色是否进入了追逐状态
	if (EnemyState == EEnemyState::EES_Chasing) return;
	// P169.如果看到的角色拥有某种标签，则切换为追逐模式，
	if (SeenPawn->ActorHasTag(FName("EngageableTarget")))
	{
		ClearPatrolTimer();
		// P169.角色移动速度变更
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		// P169.切换战斗对象为看到的角色
		CombatTarget = SeenPawn;

		// P171.如果已经是攻击状态了，那么就不需要切换为追逐状态
		if (EnemyState != EEnemyState::EES_Attacking)
		{
			EnemyState = EEnemyState::EES_Chasing;
			// P169.开始追逐战斗对象
			MoveToTarget(CombatTarget);

		}

	}
	*/

}
