// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterTypes.h"
#include "Characters/MyCharacter.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;
class AWeapon;
class ASoul;

/**
* 敌人类，P182.函数整理
*/
UCLASS()
class RPG_PROJECT_API AEnemy : public AMyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();


	/** <AActor> */
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// P155.覆盖 AActor 类中的虚函数 TakeDamage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// P177.覆盖 AActor 类中的虚函数 Destroyed，在本类从世界上 Destroy 时会被调用的成员函数
	virtual void Destroyed() override;
	/** </AActor> */


	/** <IHitInterface> */
	// P125.覆盖继承自 IHitInterface 的纯虚函数。P140.
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/** </IHitInterface> */


protected:
	/** <AActor> */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** </AActor> */


	/** <AMyCharacter> */
	// 178.覆盖继承自父类 AMyCharacter 的虚函数: 攻击
	virtual void Attack() override;
	// P179.覆盖继承自父类 AMyCharacter 的虚函数: 是否可以攻击
	virtual bool CanAttack() override;
	// P179.覆盖继承自父类 AMyCharacter 的虚函数: 被攻击时扣血
	virtual void HandleDamage(float DamageAmount) override;
	// P181..覆盖继承自父类 AMyCharacter 的虚函数: 把 ActionState 赋值为 Unoccupied ，可以与动画蒙太奇中的通知一起调用来防止角色在播放动画时平移在角色的ABP事件图标中调用。原 AttackEnd() 成员函数。
	virtual void ActionEnd() override;
	// P158.声明角色死亡成员函数,并播放死亡动画蒙太奇。P175.覆盖 MyCharacter 中的虚函数
	virtual void Die_Implementation() override;
	// P209.Spawn a Soul when enemy dead
	void SpawnSoul();
	/** </AMyCharacter> */
	

	// P169.声明敌人行为模式，初始化为“巡逻”
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;


private:
	/**
	* AI Behavior
	*/
	// P182.在游戏开始时初始化角色
	void InitializeEnemy();
	// P167.移动到相应巡逻节点
	void MoveToTarget(AActor* Target);
	// P167.原P166的改良版：如果到达了一个巡逻节点，则随机选择巡逻节点数组 PatrolTargets 中的新巡逻节点
	void CheckPatrolTarget();
	// P167.原P160的代码提取的成员函数：计算角色和战斗对象的距离，如果角色和战斗对象距离过远，则不显示血条
	void CheckCombatTarget();
	// P167.固定时间以后开始巡逻
	void PatrolTimerFinished();
	// P179.隐藏角色血条
	void HideHealthBar();
	// P179.显示角色血条
	void ShowHealthBar();
	// P179.对原战斗对象失去仇恨
	void LoseInterest();
	// P179.为了使角色进入巡逻模式，设置巡逻模式相关变量
	void StartPatrolling();
	// P179.为了使角色进入追逐模式，设置追逐模式相关变量
	void ChaseTarget();
	// P179.检查战斗对象是否脱离了仇恨范围
	bool IsOutsideCombatRadius();
	// P179.检查战斗对象是否脱离了攻击范围
	bool IsOutsideAttackRadius();
	// P179.检查战斗对象是否进入了攻击范围
	bool IsInsideAttackRadius();
	// P179.检查角色是否为追逐模式
	bool IsChasing();
	// P179.检查角色是否为攻击模式
	bool IsAttacking();
	// P179.检查角色是否死亡
	bool IsDead();
	// P179.检查角色是否在进行攻击
	bool IsEngaged();
	// P179.清除巡逻时的 Idle 计时器
	void ClearPatrolTimer();
	// P179.按攻击间隔进入攻击模式，并进行攻击
	void StartAttackTimer();
	// P179.清除攻击间隔的 计时器
	void ClearAttackTimer();
	// P167.返回到达一个巡逻节点之后选择的下一个巡逻节点
	AActor* ChoosePatrolTarget();
	// P166.检查角色与特定 AActor 类的距离，距离过近返回true。如果 没有到设定的距离 或者 Target 为空指针，返回 false
	bool InTargetRange(AActor* Target, double Radius);
	// P182.生成默认武器
	void SpawnDefaultWeapon();
	// P168.返回 USensingComponent 的成员函数 OnSeePawn delegate的callback，用来接收看到的Pawn类
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	// P165.声明控制角色的AI控制器的指针成员变量
	UPROPERTY()
	AAIController* EnemyController;

	// P165.角色巡逻目标
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	// P165.存储角色巡逻目标的动态数组
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	// P177.声明可以存储武器派生类的成员变量，在蓝图中赋值
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	// P152.声明本地插件组件
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	// P168.声明Pawn传感组件
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	// P160.角色根据战斗对象的距离显示血条的距离，默认为 500.f
	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 500.f;

	// P171.角色切换为攻击状态的距离，默认为 150.f
	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius = 150.f;

	// P191. Radius of circle that let Enemy stop moving
	UPROPERTY(EditAnywhere, Category = Combat)
	float AcceptanceRadius = 60.f;
	
	// P167.声明在巡逻间 Idle 相关的 FTimerHandle 结构体
	FTimerHandle PatrolTimer;

	// P167.巡逻间Idle时长的最值,默认为（5.f, 10,f）
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	// P179.巡逻模式下的角色移动速度
	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	// P179.设置战斗时的攻击间隔用计时器
	FTimerHandle AttackTimer;

	// P179.战斗时的攻击间隔的最值，默认为（0.5f, 1.f）
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	// P179.追踪模式下的角色移动速度
	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	// P180.设置角色死亡时间，默认为8.f
	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	// 209.Declare a param to store ASoul class and classes derived by it
	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<ASoul> SoulClass;
	
};
